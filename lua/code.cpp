/*************************************************
Author:            |メ破坏者☆
Date:              |2017-02-05
version：          |0.0.0
Description:       |颜色插件主要函数
**************************************************/
#include <windows.h>
#include "Config.h"
#include "Language.h"
#include "WinForm.h"
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
Calls:            |
*************************************************/
DWORD WINAPI task(LPVOID lpParamter) {
	/*WCHAR* path = Path().GetPath();
	MessageBox(NULL, path, TEXT("World"), MB_OK);
	free(path);*/

	//UINT m_nXPos = GetPrivateProfileIntW(TEXT("SECTION 1"), //节名
	//	TEXT("XPos"), //项名
	//	0, //没找到此项时的缺省返回值
	//	TEXT("C:\\test\\debug\\test.ini")); //配置文件的准确路径
	Config C = Config();
	Language L = Language(C.GetLanguage());
	//WinForm WF = WinForm(&L);
	WinFind WF = WinFind(&L);

	ULONGLONG time = GetTickCount64();
	while (loop)
	{
		ULONGLONG now = GetTickCount64();
		if (now - time > 1000)
		{
			time = now;
			WF.Find();
		}
	}
	MessageBox(NULL, TEXT("Hello"), TEXT("World"), MB_OK);
	return 0;
}
/*************************************************
Function:         |start
Description:      |开启颜色插件功能
Calls:            |task
Others:           |此函数供lua脚本调用
*************************************************/
static int start(lua_State* L)
{
	HANDLE hThread = CreateThread(NULL, 0, task, NULL, 0, NULL);
	return 0;
}
/*************************************************
Function:         |stop
Description:      |关闭颜色插件功能
Others:           |此函数供lua脚本调用
*************************************************/
static int stop(lua_State *L)
{
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