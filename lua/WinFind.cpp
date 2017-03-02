#include "WinFind.h"
#include "Config.h"
#include "WinForm.h"
#include "Path.h"
#include <process.h>
#include <corecrt_wstdio.h>
/*************************************************
Function:         |WinFind
Description:      |初始化数据
Input:            |L：全局唯一的语言类.
*************************************************/
WinFind::WinFind(const Language* L) {
	this->L = L;
	Config C = Config();
	LPSTR p = Path().GetWorldEditStringsFileLPSTR();
	C.WESTRING_COD_TYPE_STRING(westring[0], 50, p);
	CHAO input;
	C.WESTRING_UE_DLG_EDITVALUE(input, 50, p);
	swprintf(westring[1], sizeof(CHAO), input, westring[0]);
	C.WESTRING_IE_DLG_EDITVALUE(input, 50, p);
	swprintf(westring[2], sizeof(CHAO), input, westring[0]);
	C.WESTRING_AE_DLG_EDITVALUE(input, 50, p);
	swprintf(westring[3], sizeof(CHAO), input, westring[0]);
	C.WESTRING_FE_DLG_EDITVALUE(input, 50, p);
	swprintf(westring[4], sizeof(CHAO), input, westring[0]);
	C.WESTRING_BE_DLG_EDITVALUE(input, 50, p);
	swprintf(westring[5], sizeof(CHAO), input, westring[0]);
	C.WESTRING_DE_DLG_EDITVALUE(input, 50, p);
	swprintf(westring[6], sizeof(CHAO), input, westring[0]);
	C.WESTRING_GE_DLG_EDITVALUE(input, 50, p);
	swprintf(westring[7], sizeof(CHAO), input, westring[0]);
	free(p);
}
/*************************************************
Function:         |Find
Description:      |寻找未创建颜色插件的窗口并插件颜色插件
*************************************************/
void WinFind::Find() {
	HWND hwnd = FindWindowExW(0, 0, TEXT("#32770"), NULL);//直接获取物编弹窗句柄
	DWORD pid = _getpid();//当前进程的pid
	DWORD p;//搜索到的窗口进程pid
	int titleSize = 50 * sizeof(WCHAR);
	while (hwnd != 0) {
		GetWindowThreadProcessId(hwnd, &p);
		if (pid == p) {//防止两个颜色插件互相干扰
			LPWSTR str = (LPWSTR)malloc(titleSize);//WARNING 目前来说，应该不存在超50字的窗口标题，如果出现问题，在WinForm.cpp里有类似解决方法
			GetWindowTextW(hwnd, str, 50 );
			//此处跳过的0是触发器的“字符串”，由于改变窗口大小会引发控件的适配，不像物编那样方便，这里保留触发器处的操作。
			for (int i = 1; i < 8; i++) {
				if (Tool().equal(str, westring[i], 50)) {
					HWND textH = FindWindowExW(hwnd, 0, TEXT("edit"), NULL);
					if (textH != NULL) {
						win *temp = &wininfo;
						while (temp != NULL) {
							if (temp->hwnd == 0) {
								temp->hwnd = hwnd;//记录这个句柄已经创建了插件
								temp->next = new win{ NULL, NULL };
								WinForm(hwnd, textH, L);
								break;
							}
							if (temp->hwnd == hwnd) {
								break;
							}
							if (IsWindow(temp->hwnd)) {
								temp = temp->next;
							} else {
								temp->hwnd = temp->next->hwnd;
								win *tempfree = temp->next;
								temp->next = temp->next->next;
								delete tempfree;//清理已销毁窗口句柄
							}
						}
					}
					break;
				}
			}
			free(str);
		}
		hwnd = FindWindowExW(0, hwnd, NULL, NULL);
	}
}