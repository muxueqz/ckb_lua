typedef int (*load_hash_function)(void *, uint64_t *, size_t);
typedef int (*load_single_function)(void *, uint64_t *, size_t);

static int l_ckb_exit(lua_State *L)
{
    int d = luaL_checknumber(L, 1);
    int ret = ckb_exit(d);
    return ret;
}

static int l_ckb_debug(lua_State *L)
{
    const char * d = lua_tostring(L, 1);
    int ret = ckb_debug(d);
    return ret;
}
    
static int l_ckb_load_hash(lua_State *L, load_hash_function f)
{
  uint64_t len = 32;
  uint8_t hash[32];
//  luaL_Buffer p;
//  luaL_prepbuffer
  int ret = f(hash, &len, 0);
  if (len != 32 ) {
    return -1;
  }
//  sprintf
//  lua_pushinteger(L, hash);
//  lua_pushstring(L, hash);
//  lua_pushfstring(L, "%p", hash);
//  29ccaf1efb3e64bd97f35447c85722d7aeff7f1d10f5b2961608db2c6ca05d50
//
//  lua_pushfstring(L, "%d", hash);
//
//  lua_pushlightuserdata(L, hash);

  lua_newtable(L);
  for(int i = 0;i < 32;i++)
  {
    lua_pushinteger(L, hash[i]);
    lua_rawseti(L,-2,i + 1);
  }

  return 1;
}

static int l_ckb_raw_load_single(lua_State *L, load_single_function f)
{
  size_t buffer_size = 0;
  size_t offset = luaL_checkinteger(L, 1);
  uint64_t len = buffer_size;
  uint8_t buffer[buffer_size];
  int ret = f(buffer, &len, offset);

  lua_pushinteger(L, -ret);

  return 1;
}

static int l_ckb_load_single(lua_State *L, load_single_function f)
{
  size_t offset = luaL_checkinteger(L, 1);
  char buffer[LUAL_BUFFERSIZE];
  uint64_t len = LUAL_BUFFERSIZE;
  int ret = f(buffer, &len, offset);

  if (ret != CKB_SUCCESS) {
    return ret;
  }

  lua_pushstring(L, buffer);
  return 1;
}

static int l_ckb_load_tx_hash(lua_State *L) {
  return l_ckb_load_hash(L, ckb_load_tx_hash);
}

static int l_ckb_load_script_hash(lua_State *L) {
  return l_ckb_load_hash(L, ckb_load_script_hash);
}

//todo
static int l_ckb_load_script(lua_State *L) {
  return l_ckb_load_single(L, ckb_load_script);
}

static int l_ckb_load_cell_data(lua_State *L)
{
    int d = luaL_checknumber(L, 1);
#define SCRIPT_SIZE (128 * 1024)
  char script[SCRIPT_SIZE];
  uint64_t len = SCRIPT_SIZE;
  int ret = ckb_load_cell_data(script, &len, 0, 0, d);
  if (ret != CKB_SUCCESS) {
    return ret;
  }
  if (len > SCRIPT_SIZE) {
    return -1;
  }

  lua_pushstring(L, script);
  return 1;
}

void ckb_init(lua_State *L) {
  //注册
  lua_pushcfunction(L, l_ckb_debug);
  lua_setglobal(L, "ckb_debug");
  
  lua_pushcfunction(L, l_ckb_exit);
  lua_setglobal(L, "ckb_exit");
  
  lua_pushcfunction(L, l_ckb_load_tx_hash);
  lua_setglobal(L, "ckb_load_tx_hash");

  lua_pushcfunction(L, l_ckb_load_script_hash);
  lua_setglobal(L, "ckb_load_script_hash");

  lua_pushcfunction(L, l_ckb_load_script);
  lua_setglobal(L, "ckb_load_script");
  
  lua_pushcfunction(L, l_ckb_load_cell_data);
  lua_setglobal(L, "ckb_load_cell_data");
}
