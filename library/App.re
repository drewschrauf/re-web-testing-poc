module Make = (Web: WebFramework.S) => {
  open Web;

  let handleBodyEcho = {};

  let server = (route, request) => {
    switch (route) {
    | (`GET, [""]) => "Hello, world!" |> Response.of_text |> Lwt.return
    | (`GET, ["queryecho"]) =>
      request |> Request.query |> Response.of_text |> Lwt.return
    /* | (`POST, ["bodyecho"]) => */
    /*   Filter.body_json @@ */
    /*   (request => request |> Request.context |> Response.of_json |> Lwt.return) */
    | _ => "Not found" |> Response.of_text(~status=`Not_found) |> Lwt.return
    };
  };
};
