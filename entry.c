//typedef unsigned long ptrdiff_t;
//#define      BUFSIZ          1024

#include <stdio.h>
#include "ckb_syscalls.h"
#include "molecule/blockchain.h"

#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <ckb_lua.h>

#define SCRIPT_SIZE (128 * 1024)
    
int main () {
  unsigned char script[SCRIPT_SIZE];
//  uint64_t len = SCRIPT_SIZE;
  uint64_t len = SCRIPT_SIZE;
  int ret = ckb_load_cell_data(script, &len, 0, 0, CKB_SOURCE_CELL_DEP);
  if (ret != CKB_SUCCESS) {
    return ret;
  }
  if (len > SCRIPT_SIZE) {
    return -1;
  }

      int error;
      lua_State *L = lua_open();   /* opens Lua */
      luaL_openlibs(L);             /* opens the basic library */
//      luaopen_base(L);             /* opens the basic library */
//      luaopen_table(L);            /* opens the table library */
//      luaopen_io(L);               /* opens the I/O library */
//      luaopen_string(L);           /* opens the string lib. */
//      luaopen_math(L);             /* opens the math lib. */
//
lua_gc(L, LUA_GCSTOP, 1);

ckb_init(L);

//  const char * lua_code = "ckb_debug('hello from lua')";
//  const char * lua_code = "ckb_exit(1)";
  error = luaL_dostring(L, script);
  if (error) {
//     fprintf(stderr, "%s", lua_tostring(L, -1));
     ckb_debug(lua_tostring(L, -1));
     lua_pop(L, 1);  /* pop error message from the stack */
     return -2;
  }
//  char len_result[50]; 
//  sprintf(len_result, "%d", error); 


//  ckb_exit(0);
//  ckb_debug(len_result);
//      while (fgets(buff, sizeof(buff), stdin) != NULL) {
//        error = luaL_loadbuffer(L, buff, strlen(buff), "line") ||
//                lua_pcall(L, 0, 0, 0);
////        ckb_debug(error);
//        if (error) {
//          fprintf(stderr, "%s", lua_tostring(L, -1));
//          lua_pop(L, 1);  /* pop error message from the stack */
//        }
//      }
    
//      lua_close(L);
//      return 0;
    }

