module H = Httpaf;

module ReqdBody = {
  type t(_) = {
    chunks: array(H.IOVec.t(Bigstringaf.t)),
    length: int,
    mutable index: int,
    mutable curr: option(H.IOVec.t(Bigstringaf.t)),
  };
  let schedule_read = (body, ~on_eof, ~on_read) =>
    if (body.index == body.length) {
      on_eof();
    } else {
      body.curr = Some(body.chunks[body.index]);
      body.index = body.index + 1;
      switch (body.curr) {
      | Some({buffer, off, len}) => on_read(buffer, ~off, ~len)
      | None => failwith("Unreachable branch")
      };
    };
};

module Reqd = {
  module Body = ReqdBody;
  type t(_, _) = (H.Request.t, Body.t([ | `read]));

  let request = fst;
  let request_body = snd;
};

module MockReWeb = {
  include ReWeb;
  module Request = ReWeb__Request.Make(ReWeb.Config.Default, ReqdBody, Reqd);
  module Filter = ReWeb__Filter.Make(Request);
  module Service = ReWeb__Service.Make(Request);
};

let makeRequest = (meth: Httpaf.Method.t, url: string) => {
  let iovec = text => {
    let off = 0;
    let len = text |> String.length;
    H.IOVec.{buffer: Bigstringaf.of_string(~off=0, ~len, text), off, len};
  };

  let makeBody = strings => {
    Reqd.Body.chunks: strings |> Array.map(iovec),
    length: strings |> Array.length,
    index: 0,
    curr: None,
  };

  let urlParts = url |> String.split_on_char('?');
  let uri = urlParts |> List.nth(_, 0);
  let query =
    if (urlParts |> List.length === 2) {
      urlParts |> List.nth(_, 1);
    } else {
      "";
    };

  MockReWeb.Request.make(
    query,
    (Httpaf.Request.create(meth, uri), makeBody([||])),
  );
};

let invoke = (server, request: MockReWeb.Request.t(unit)) => {
  let Httpaf.Request.{meth, target} =
    request.reqd |> MockReWeb.Request.Reqd.request;

  let urlParts = target |> String.split_on_char('/') |> List.tl;
  let response = server((meth, urlParts), request);
  Lwt_main.run(response);
};

let bodyAsString = (body: MockReWeb.Body.t) => {
  switch (body) {
  | Bigstring(bs) => bs |> Bigstringaf.to_string
  | String(t) => t
  | _ => failwith("Unable to extract string from body")
  };
};
