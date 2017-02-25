#include <process.h>
#include <corecrt_wstdio.h>
#include <stdio.h>
//#include <wchar.h>
#include "WinFind.h"
#include "Config.h"
#include "Tool.h"
#include "WinForm.h"
#define ѩ����ȥ�� break
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
	//WESTRING_COD_TYPE_STRINGstr = C.WESTRING_COD_TYPE_STRING();//�ַ���
	//WESTRING_UE_DLG_EDITVALUEstr = C.WESTRING_UE_DLG_EDITVALUE();//�༭��λֵ - %s
	//WESTRING_IE_DLG_EDITVALUEstr = C.WESTRING_IE_DLG_EDITVALUE();//�༭��Ʒֵ - %s
	//WESTRING_AE_DLG_EDITVALUEstr = C.WESTRING_AE_DLG_EDITVALUE();//�༭����ֵ - %s
	//WESTRING_FE_DLG_EDITVALUEstr = C.WESTRING_FE_DLG_EDITVALUE();//�༭Ч��ֵ - %s
	//WESTRING_BE_DLG_EDITVALUEstr = C.WESTRING_BE_DLG_EDITVALUE();//�༭���ƻ���ֵ - %s
	//WESTRING_DE_DLG_EDITVALUEstr = C.WESTRING_DE_DLG_EDITVALUE();//�༭װ����ֵ - %s
	//WESTRING_GE_DLG_EDITVALUEstr = C.WESTRING_GE_DLG_EDITVALUE();//�༭�Ƽ�ֵ - %s
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
							ѩ����ȥ��;
						}
						if (temp->hwnd == hwnd)
						{
							ѩ����ȥ��;
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
					ѩ����ȥ��;
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

/*�ڵõ����ھ�������ǿ���ͨ��GetWindowThreadProcessId�����������ô�����������ID���߳�ID���Ӷ��жϴ������ڵĽ��̺��̡߳�

����ԭ�ͣ�

DWORD GetWindowThreadProcessId(HWND hWnd,LPDWORD lpdwProcessId);

����˵����

hWnd������Ĵ��ھ����lpdwProcessId�����صĽ���ID��ַ��

����ֵ��

�������ص��Ǵ��������߳�ID��

ʹ�����ӣ�

DWORD ProcessID;
DWORD ThreadID;
ThreadID=GetWindowThreadProcessId(hWnd,&ProcessID);*/

/*GetTopWindow
�������ܣ��ú���������ض��������������Ӵ���z��Z�򣺴�ֱ��Ļ�ķ��򣬼����Ŵ��򣩣���������z�򶥲����Ӵ��ڵľ����
����ԭ�ͣ�HWND GetTopWindow��HWND hWnd����
������
����hWnd:������ĸ����ڵľ��������ò���ΪNULL����������Z�򶥲��Ĵ��ھ����
����ֵ��
��������ɹ�������ֵΪ��Z�򶥲����Ӵ��ھ�������ָ���Ĵ������Ӵ��ڣ�����ֵΪNULL�� */