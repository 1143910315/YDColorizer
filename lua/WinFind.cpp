#include "WinFind.h"
#include "Config.h"
#include "WinForm.h"
#include "Path.h"
#include <process.h>
#include <corecrt_wstdio.h>
/*************************************************
Function:         |WinFind
Description:      |��ʼ������
Input:            |L��ȫ��Ψһ��������.
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
Description:      |Ѱ��δ������ɫ����Ĵ��ڲ������ɫ���
*************************************************/
void WinFind::Find() {
	HWND hwnd = FindWindowExW(0, 0, TEXT("#32770"), NULL);//ֱ�ӻ�ȡ��൯�����
	DWORD pid = _getpid();//��ǰ���̵�pid
	DWORD p;//�������Ĵ��ڽ���pid
	int titleSize = 50 * sizeof(WCHAR);
	while (hwnd != 0) {
		GetWindowThreadProcessId(hwnd, &p);
		if (pid == p) {//��ֹ������ɫ����������
			LPWSTR str = (LPWSTR)malloc(titleSize);//WARNING Ŀǰ��˵��Ӧ�ò����ڳ�50�ֵĴ��ڱ��⣬����������⣬��WinForm.cpp�������ƽ������
			GetWindowTextW(hwnd, str, 50 );
			//�˴�������0�Ǵ������ġ��ַ����������ڸı䴰�ڴ�С�������ؼ������䣬��������������㣬���ﱣ�����������Ĳ�����
			for (int i = 1; i < 8; i++) {
				if (Tool().equal(str, westring[i], 50)) {
					HWND textH = FindWindowExW(hwnd, 0, TEXT("edit"), NULL);
					if (textH != NULL) {
						win *temp = &wininfo;
						while (temp != NULL) {
							if (temp->hwnd == 0) {
								temp->hwnd = hwnd;//��¼�������Ѿ������˲��
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
								delete tempfree;//���������ٴ��ھ��
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