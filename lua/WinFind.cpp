#include <process.h>
#include <corecrt_wstdio.h>
#include <stdio.h>
//#include <wchar.h>
#include "WinFind.h"
#include "Config.h"
#include "Tool.h"
#include "WinForm.h"
#define 雪花快去死 break
WinFind::WinFind(const Language* L)
{
	this->L = L;
	Config C = Config();
	//Tool T = Tool();
	//LPWSTR temp = C.WESTRING_COD_TYPE_STRING();
	//LPWSTR utfStra = T.UTF8ToGBK(temp);
	//free(temp);
	LPWSTR temp = C.WESTRING_COD_TYPE_STRING();
	swprintf(westring[0], sizeof(CHAO), temp);
	free(temp);
	temp = C.WESTRING_UE_DLG_EDITVALUE();
	swprintf(westring[1], sizeof(CHAO), temp, westring[0]);
	free(temp);
	temp = C.WESTRING_IE_DLG_EDITVALUE();
	swprintf(westring[2], sizeof(CHAO), temp, westring[0]);
	free(temp);
	temp = C.WESTRING_AE_DLG_EDITVALUE();
	swprintf(westring[3], sizeof(CHAO), temp, westring[0]);
	free(temp);
	temp = C.WESTRING_FE_DLG_EDITVALUE();
	swprintf(westring[4], sizeof(CHAO), temp, westring[0]);
	free(temp);
	temp = C.WESTRING_BE_DLG_EDITVALUE();
	swprintf(westring[5], sizeof(CHAO), temp, westring[0]);
	free(temp);
	temp = C.WESTRING_DE_DLG_EDITVALUE();
	swprintf(westring[6], sizeof(CHAO), temp, westring[0]);
	free(temp);
	temp = C.WESTRING_GE_DLG_EDITVALUE();
	swprintf(westring[7], sizeof(CHAO), temp, westring[0]);
	free(temp);
	//swprintf_s((wchar_t*)westring[0], sizeof(CHAO), C.WESTRING_COD_TYPE_STRING());
	//temp = C.WESTRING_UE_DLG_EDITVALUE();
	//LPWSTR utfStr = T.UTF8ToGBK(temp);
	//swprintf_s((wchar_t*)westring + sizeof(CHAO) * 1, sizeof(CHAO),  C.WESTRING_UE_DLG_EDITVALUE(), C.WESTRING_COD_TYPE_STRING());
	//free(utfStr);
	//swprintf_s((wchar_t*)westring + sizeof(CHAO) * 2, sizeof(CHAO), C.WESTRING_IE_DLG_EDITVALUE(), C.WESTRING_COD_TYPE_STRING());
	//swprintf_s((wchar_t*)westring + sizeof(CHAO) * 3, sizeof(CHAO), C.WESTRING_AE_DLG_EDITVALUE(), C.WESTRING_COD_TYPE_STRING());
	//swprintf_s((wchar_t*)westring + sizeof(CHAO) * 4, sizeof(CHAO), C.WESTRING_FE_DLG_EDITVALUE(), C.WESTRING_COD_TYPE_STRING());
	//swprintf_s((wchar_t*)westring + sizeof(CHAO) * 5, sizeof(CHAO), C.WESTRING_BE_DLG_EDITVALUE(), C.WESTRING_COD_TYPE_STRING());
	//swprintf_s((wchar_t*)westring + sizeof(CHAO) * 6, sizeof(CHAO), C.WESTRING_DE_DLG_EDITVALUE(), C.WESTRING_COD_TYPE_STRING());
	//swprintf_s((wchar_t*)westring + sizeof(CHAO) * 7, sizeof(CHAO), C.WESTRING_GE_DLG_EDITVALUE(), C.WESTRING_COD_TYPE_STRING());
	//MessageBoxW(NULL, westring[0], TEXT("World"), MB_OK);
	//MessageBoxW(NULL, westring[1], TEXT("World"), MB_OK);
	//MessageBoxW(NULL, westring[2], TEXT("World"), MB_OK);
	//MessageBoxW(NULL, westring[3], TEXT("World"), MB_OK);
	//MessageBoxW(NULL, westring[4], TEXT("World"), MB_OK);
	//MessageBoxW(NULL, westring[5], TEXT("World"), MB_OK);
	//MessageBoxW(NULL, westring[6], TEXT("World"), MB_OK);
	//MessageBoxW(NULL, westring[7], TEXT("World"), MB_OK);
	////swprintf_s();
	//WESTRING_COD_TYPE_STRINGstr = C.WESTRING_COD_TYPE_STRING();//字符串
	//WESTRING_UE_DLG_EDITVALUEstr = C.WESTRING_UE_DLG_EDITVALUE();//编辑单位值 - %s
	//WESTRING_IE_DLG_EDITVALUEstr = C.WESTRING_IE_DLG_EDITVALUE();//编辑物品值 - %s
	//WESTRING_AE_DLG_EDITVALUEstr = C.WESTRING_AE_DLG_EDITVALUE();//编辑技能值 - %s
	//WESTRING_FE_DLG_EDITVALUEstr = C.WESTRING_FE_DLG_EDITVALUE();//编辑效果值 - %s
	//WESTRING_BE_DLG_EDITVALUEstr = C.WESTRING_BE_DLG_EDITVALUE();//编辑可破坏物值 - %s
	//WESTRING_DE_DLG_EDITVALUEstr = C.WESTRING_DE_DLG_EDITVALUE();//编辑装饰物值 - %s
	//WESTRING_GE_DLG_EDITVALUEstr = C.WESTRING_GE_DLG_EDITVALUE();//编辑科技值 - %s
}
void WinFind::Find()
{
	//EnumWindows(EnumWindowsProc, (LPARAM)&westring);
	HWND hwnd = 0;
	hwnd = FindWindowExW(0, 0, TEXT("#32770"), NULL);
	DWORD pid = _getpid();
	while (hwnd != 0)
	{
		DWORD p = 0;
		GetWindowThreadProcessId(hwnd, &p);
		if (pid == p)
		{
			LPWSTR str = (LPWSTR)malloc(50 * sizeof(WCHAR));
			memset(str, 0, 50 * sizeof(WCHAR));
			GetWindowTextW(hwnd, str, 50 * sizeof(WCHAR));
			/*if (str[0] != '\0') {
				MessageBoxW(NULL, str, TEXT("World"), MB_OK);
			}*/
			for (int i = 1; i < 8; i++) {
				if (Tool().equal(str, westring[i], 50 * sizeof(WCHAR))) {
					win *temp = &wininfo;
					while (temp != NULL)
					{
						if (temp->hwnd == 0) {
							temp->hwnd = hwnd;
							temp->next = new win{ NULL, NULL };
							new WinForm(hwnd, L);
							雪花快去死;
						}
						if (temp->hwnd == hwnd)
						{
							雪花快去死;
						}
						if (IsWindow(temp->hwnd))
						{
							temp = temp->next;
						}
						else 
						{
							temp->hwnd = temp->next->hwnd;
							win *tempfree = temp->next;
							temp->next = temp->next->next;
							free(tempfree);
						}
					}
					//MessageBoxW(NULL, str, TEXT("World"), MB_OK);
					雪花快去死;
				}
			}
			free(str);
			//EnumChildWindows(hwnd, EnumWindowsProc, (LPARAM)&westring);
		}
		hwnd = FindWindowExW(0, hwnd, NULL, NULL);
	}
	//char str[10];
	//sprintf(str, "%d", pid);
	//MessageBox(NULL, Tool().ChartoWCHAR(str, 10), TEXT("World"), MB_OK);
}

//void WinFind::NextFind(HWND hwnd)
//{
//	//HWND h = 0;
//	//h = FindWindowExW(hwnd, 0, NULL, NULL);
//	//while (h != 0)
//	//{
//	//	LPWSTR str = (LPWSTR)malloc(50 * sizeof(WCHAR));
//	//	memset(str, 0, 50 * sizeof(WCHAR));
//	//	GetWindowTextW(h, str, 50 * sizeof(WCHAR));
//	//	//MessageBoxW(NULL, str, TEXT("World"), MB_OK);
//	//	for (int i = 0; i < 8; i++) {
//	//		if (Tool().equal(str, westring[i], 50 * sizeof(WCHAR))) {
//	//			MessageBoxW(NULL, str, TEXT("World"), MB_OK);
//	//			break;
//	//		}
//	//	}
//	//	free(str);
//	//	NextFind(h);
//	//	h = FindWindowExW(hwnd, h, TEXT("#32770"), NULL);
//	//}
//
//
//
//}

/*在得到窗口句柄后我们可以通过GetWindowThreadProcessId这个函数来获得窗口所属进程ID和线程ID，从而判断创建窗口的进程和线程。

函数原型：

DWORD GetWindowThreadProcessId(HWND hWnd,LPDWORD lpdwProcessId);

参数说明：

hWnd：传入的窗口句柄；lpdwProcessId：返回的进程ID地址。

返回值：

函数返回的是窗口所属线程ID。

使用例子：

DWORD ProcessID;
DWORD ThreadID;
ThreadID=GetWindowThreadProcessId(hWnd,&ProcessID);*/

/*GetTopWindow
函数功能：该函数检查与特定父窗口相联的子窗口z序（Z序：垂直屏幕的方向，即叠放次序），并返回在z序顶部的子窗口的句柄。
函数原型：HWND GetTopWindow（HWND hWnd）；
参数：
　　hWnd:被查序的父窗口的句柄。如果该参数为NULL，函数返回Z序顶部的窗口句柄。
返回值：
如果函数成功，返回值为在Z序顶部的子窗口句柄。如果指定的窗口无子窗口，返回值为NULL。 */