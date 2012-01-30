#include <stdint.h>
#include <string.h>
#include "erl_nif.h"


static int
load(ErlNifEnv* env, void** priv, ERL_NIF_TERM load_info)
{
	return 0;
}

static int
reload(ErlNifEnv* env, void** priv, ERL_NIF_TERM load_info)
{
	return 0;
}

static int
upgrade(ErlNifEnv* env, void** priv, void** old_priv,
				ERL_NIF_TERM load_info)
{
	return 0;
}

static void
unload(ErlNifEnv* env, void* priv)
{
	return;
}

static ERL_NIF_TERM
escape_erl(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
  ERL_NIF_TERM bin = argv[0];
  ErlNifBinary cdata_in;
  ErlNifBinary cdata_out;
  if (!enif_inspect_binary(env, bin, &cdata_in)) {
    return enif_make_badarg(env);
  }
	if (!enif_alloc_binary(cdata_in.size+12, &cdata_out)) {
		return enif_make_badarg(env);
	}
	memcpy(cdata_out.data, "<![CDATA[", 9);
	memcpy(cdata_out.data+9, cdata_in.data, cdata_in.size);
	memcpy(cdata_out.data+9+cdata_in.size, "]]>", 3);
  return enif_make_binary(env, &cdata_out);
}

static ErlNifFunc exmpp_strops_funcs[] =
{
    {"escape", 1, escape_erl}
};

ERL_NIF_INIT(exmpp_strops, exmpp_strops_funcs, load, reload, upgrade, unload)
