/*************************************************
Author:            |���ƻ��ߡ�
Date:              |2017-02-28
version��          |0.0.1
Description:       |��ɫ�����Ҫ����
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
bool loop = true;//���ݹرղ���ź�
/*************************************************
Function:         |task
Description:      |��ɫ��������幦��
*************************************************/
DWORD WINAPI task(LPVOID lpParamter) {
	Config C = Config();
	Language L = Language(C.GetLanguage());
	HINSTANCE hinstrich;//RichEdit��DLL
	hinstrich = LoadLibraryW(TEXT("Riched20.Dll"));
	int i = 0;
	while (hinstrich == NULL) {
		if (i++ == 10) {
			MessageBoxW(NULL, L.lessDLL, L.error, MB_ICONERROR);
			return 0;
		}
		Sleep(1000);
		hinstrich = LoadLibraryW(TEXT("Riched20.Dll"));//��ʱ��ò�Ʋ�����������DLL
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
Description:      |������ɫ�������
Calls:            |task
Others:           |�˺�����lua�ű�����
*************************************************/
static int start(lua_State* L) {
	HANDLE hThread = CreateThread(NULL, 0, task, NULL, 0, NULL);
	return 0;
}
/*************************************************
Function:         |stop
Description:      |�ر���ɫ�������
Others:           |�˺�����lua�ű�����
*************************************************/
static int stop(lua_State *L) {
	loop = false;
	return 0;
	///////////////////////////////////////////////////////
	////���´�����Ϊ��ȡlua�����Լ�����lua������ģ��
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