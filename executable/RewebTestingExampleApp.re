module App = RewebTestingExample.App.Make(ReWeb);

ReWeb.Server.serve(App.server);
