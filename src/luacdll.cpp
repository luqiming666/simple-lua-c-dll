//
// How to create a Lua-ready DLL
// http://quik2dde.ru/viewtopic.php?id=18
//

#include <windows.h>
#include <process.h>
#include <tchar.h>

#define LUA_LIB
#define LUA_BUILD_AS_DLL

#include "lua.hpp"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	return TRUE;
}


static int forLua_GetCurrentThreadId(lua_State *L) {
    lua_pushinteger(L, GetCurrentThreadId());
	return(1);
}

static int forLua_MultTwoNumbers(lua_State *L) {
    double d1 = luaL_checknumber(L, 1);
    double d2 = luaL_checknumber(L, 2);

    lua_pushnumber(L, d1 * d2);

    return(1); 
}

static int forLua_ShowMsg(lua_State* L) {
	const int n = lua_gettop(L);
	if (n > 0) {
		int type = lua_type(L, 1); // Ц»ґ¦АнµЪТ»ёцКдИлІОКэ
		char strMsg[100] = {0};

		if (type == LUA_TNUMBER) {
			sprintf(strMsg, "%d", lua_tonumber(L, 1));
			MessageBox(NULL, strMsg, _T("QM"), MB_OK);
		}
		else if (type == LUA_TSTRING) {
			const char* pStr = lua_tostring(L, 1);
			if (pStr) {
				MessageBox(NULL, pStr, _T("QM"), MB_OK);
			}
		}
	}

	return(1);
}
	
static int forLua_MultAllNumbers(lua_State *L) {
	const int n = lua_gettop(L); 
	double res = 1;
	bool isNumberFound = false;
	for (int i = 1; i <= n; ++i)
		if (lua_type(L, i) == LUA_TNUMBER)
		{
			res *= lua_tonumber(L, i);
			isNumberFound = true;
		}

    if (isNumberFound)
		lua_pushnumber(L, res);
	else
		lua_pushnil(L);

    return(1);
}
	
// DLL APIs for Lua
static struct luaL_Reg ls_lib[] = {
    {"GetCurrentThreadId", forLua_GetCurrentThreadId},
    {"MultTwoNumbers", forLua_MultTwoNumbers},
    {"MultAllNumbers", forLua_MultAllNumbers},
	{"ShowMsg", forLua_ShowMsg},
    {nullptr, nullptr}
};

// Entry point for Lua-ready DLL
extern "C" LUALIB_API int luaopen_luacdll(lua_State *L) {
	#if LUA_VERSION_NUM >= 502
		luaL_newlib(L, ls_lib);
	#else
		luaL_openlib(L, "luacdll", ls_lib, 0);
	#endif

	return 1;
}

