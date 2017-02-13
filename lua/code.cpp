/*************************************************
Author:            |���ƻ��ߡ�
Date:              |2017-02-05
version��          |0.0.0
Description:       |��ɫ�����Ҫ����
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
bool loop = true;//���ݹرղ���ź�
/*************************************************
Function:         |task
Description:      |��ɫ��������幦��
Calls:            |
*************************************************/
DWORD WINAPI task(LPVOID lpParamter) {
	/*WCHAR* path = Path().GetPath();
	MessageBox(NULL, path, TEXT("World"), MB_OK);
	free(path);*/

	//UINT m_nXPos = GetPrivateProfileIntW(TEXT("SECTION 1"), //����
	//	TEXT("XPos"), //����
	//	0, //û�ҵ�����ʱ��ȱʡ����ֵ
	//	TEXT("C:\\test\\debug\\test.ini")); //�����ļ���׼ȷ·��
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
Description:      |������ɫ�������
Calls:            |task
Others:           |�˺�����lua�ű�����
*************************************************/
static int start(lua_State* L)
{
	HANDLE hThread = CreateThread(NULL, 0, task, NULL, 0, NULL);
	return 0;
}
/*************************************************
Function:         |stop
Description:      |�ر���ɫ�������
Others:           |�˺�����lua�ű�����
*************************************************/
static int stop(lua_State *L)
{
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