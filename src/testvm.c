#include<stdio.h>
#include </mnt/c/lua5/lua-5.3-annotated-master/src/lua.h>
#include </mnt/c/lua5/lua-5.3-annotated-master/src/lualib.h>
#include </mnt/c/lua5/lua-5.3-annotated-master/src/lauxlib.h>
//   gcc testvm.c -L/usr/local/lib/ -I /usr/local/include -llua -lm -g -W -E -ldl -lreadline
int main(int argc,char *argv[]){
    char *file =NULL;
    if (argc==1){
        file="test.lua";
    }
    else{file=argv[1];}
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    luaL_dofile(L,file);
    return 0;
}