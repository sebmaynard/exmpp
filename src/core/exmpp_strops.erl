-module(exmpp_strops).
-export([escape/1]).
-on_load(init/0).
init() ->
  ok = erlang:load_nif(filename:join([code:priv_dir(exmpp), "lib", "exmpp_strops"]), 0).
escape(_X) ->
  exit(nif_library_not_loaded).
