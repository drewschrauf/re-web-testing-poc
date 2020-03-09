open TestFramework;
open ReWebTestUtils;

module App = RewebTestingExample.App.Make(MockReWeb);

describe("Requests", ({test}) => {
  test("/ returns Hello, world!", ({expect}) => {
    let response = makeRequest(`GET, "/") |> invoke(App.server);
    let bodyText = response |> MockReWeb.Response.body |> bodyAsString;

    expect.equal(`OK, response |> MockReWeb.Response.status);
    expect.string(bodyText).toEqual("Hello, world!");
  });

  test("/missing returns Not found", ({expect}) => {
    let response = makeRequest(`GET, "/missing") |> invoke(App.server);
    let bodyText = response |> MockReWeb.Response.body |> bodyAsString;

    expect.equal(`Not_found, response |> MockReWeb.Response.status);
    expect.string(bodyText).toEqual("Not found");
  });

  test("/queryecho should echo query string", ({expect}) => {
    let response =
      makeRequest(`GET, "/queryecho?param=hello") |> invoke(App.server);
    let bodyText = response |> MockReWeb.Response.body |> bodyAsString;

    expect.equal(`OK, response |> MockReWeb.Response.status);
    expect.string(bodyText).toEqual("param=hello");
  });
});
