module type S = {
  include (module type of ReWeb);
  module Request: ReWeb__Request.S;
  module Filter: ReWeb__Filter.S;
  module Service: ReWeb__Service.S;
};
