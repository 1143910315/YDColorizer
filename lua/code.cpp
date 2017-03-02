/*************************************************
Author:            |メ破坏者☆
Date:              |2017-02-28
version：          |0.0.1
Description:       |颜色插件主要函数
**************************************************/
#include <windows.h>
#include "Config.h"
#include "Language.h"
#include "WinFind.h"
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
};
bool loop = true;//传递关闭插件信号
/*************************************************
Function:         |task
Description:      |颜色插件的主体功能
*************************************************/
DWORD WINAPI task(LPVOID lpParamter) {
	Config C = Config();
	Language L = Language(C.GetLanguage());
	HINSTANCE hinstrich;//RichEdit的DLL
	hinstrich = LoadLibraryW(TEXT("Riched20.Dll"));
	int i = 0;
	while (hinstrich == NULL) {
		if (i++ == 10) {
			MessageBoxW(NULL, L.lessDLL, L.error, MB_ICONERROR);
			return 0;
		}
		Sleep(1000);
		hinstrich = LoadLibraryW(TEXT("Riched20.Dll"));//有时候貌似不能立即加载DLL
	}
	WinFind WF = WinFind(&L);
	while (loop) {
		WF.Find();
		Sleep(1000);
	}
	FreeLibrary(hinstrich);
	return 0;
}
/*************************************************
Function:         |start
Description:      |开启颜色插件功能
Calls:            |task
Others:           |此函数供lua脚本调用
*************************************************/
static int start(lua_State* L) {
	HANDLE hThread = CreateThread(NULL, 0, task, NULL, 0, NULL);
	return 0;
}
/*************************************************
Function:         |stop
Description:      |关闭颜色插件功能
Others:           |此函数供lua脚本调用
*************************************************/
static int stop(lua_State *L) {
	loop = false;
	return 0;
	///////////////////////////////////////////////////////
	////以下代码作为获取lua参数以及返回lua参数的模板
	///////////////////////////////////////////////////////
	/////* get number of arguments */
	////int n = lua_gettop(L);
	////double sum = 0;
	////int i;
	/////* loop through each argument */
	////for (i = 1; i <= n; i++)
	////{
	////	/* total the arguments */
	////	sum += lua_tonumber(L, i);
	////}
	/////* push the average */
	////lua_pushnumber(L, sum / n);
	/////* push the sum */
	////lua_pushnumber(L, sum);
	/////* return the number of results */
	////return 2;
	///////////////////////////////////////////////////////
}
static const luaL_Reg MyLuaDLLFunctions[] =
{
	{ "start", start },
	{ "stop", stop },
	{ NULL, NULL }
};
#ifdef _WIN32  
extern "C" __declspec(dllexport) int luaopen_luadlllib(lua_State* L)
#else  
extern "C"  int luaopen_luadlllib(lua_State* L)
#endif
{
	lua_newtable(L);
	luaL_setfuncs(L, MyLuaDLLFunctions, 0);
	return 1;
}