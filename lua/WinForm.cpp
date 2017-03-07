#include "WinForm.h"
#include "MyRichEditView.h"
#include "Tool.h"
#include "WinControl.h"
#include <windows.h>
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);//��Ϣ������ԭ��
//������Ϣ�ṹ������ӳ�Ա�����ĩβ��������������������󣡣�
struct Paramter {
	HWND hwnd = NULL;//α���ڣ����Ǽٵģ�
	HWND objectHwnd = NULL;//��൯�����
	HWND objectTextHwnd = NULL;//��൯�����ı���ľ��
	const Language* language = NULL;//���԰���һ��DLLֻ����һ��
	HWND RichEditHwnd = NULL;//���ı��ؼ����
	WinControl* Control = NULL;//�������������ؼ�
};
/*************************************************
Function:         |monitor
Description:      |������൯���Ƿ񱻹رգ�ͬʱ��������ı��ı�
Calls:            |
Input:            |Paramter����������
Others:           |�����ͷŴ����Ĵ���
*************************************************/
DWORD WINAPI monitor(LPVOID lpParamter) {
	Paramter* param = (Paramter*)lpParamter;
	Tool T = Tool();
	//param->Control->update();
	while (IsWindow(param->objectHwnd)) {
		InvalidateRect(param->hwnd, NULL, true);
		UpdateWindow(param->hwnd);
		Sleep(1000);
	}
	SendMessageW(param->hwnd, WM_DESTROY, 0, 0);
	ExitThread(0);
	return 0;
}
DWORD WINAPI winFormTask(LPVOID lpParamter) {
	Paramter* param = (Paramter*)lpParamter;
	LPCWSTR szClassName = TEXT("WndClass");//��������
	//������������
	WNDCLASSEXW wndclass{
		sizeof(wndclass),								//����ṹ�Ĵ�С
		CS_HREDRAW | CS_VREDRAW | CS_OWNDC,				//���崰����ʽ
		WndProc,										//ָ�������ڵ���Ϣ������
		NULL,                                           //û�ж�������ڴ�
		sizeof(Paramter*),								//����Ĵ����ڴ�
		GetModuleHandleW(NULL),							//ʵ�����
		LoadIconW(NULL, IDI_APPLICATION),				//ʹ��Ĭ�ϵ�ͼ��
		LoadCursorW(NULL, IDC_ARROW),					//ʹ��Ĭ�ϵĹ��
		(HBRUSH)(COLOR_3DFACE + 1),						//���崰�ڵı�����ɫΪ��ɫ
		NULL,											//��ʹ�ò˵�
		szClassName,									//����������
		NULL											//û�����Сͼ��
	};
	RegisterClassExW(&wndclass);//ע�ᴰ����
	WINDOWINFO info;
	GetWindowInfo(param->objectHwnd, &info);
	RECT rect = info.rcWindow;
	//�����ڵĴ��ھ��
	HWND hwnd = CreateWindowExW(
		0,												//��������չ��ʽ
		szClassName,									//����
		NULL,											//���ڱ���
		WS_CHILDWINDOW,								//���ڷ�񣬲�����������ʾ
		0, info.rcClient.bottom - info.rcClient.top, 500, 200,								//����X�����꣬Y�����꣬���ڿ�ȣ����ڸ߶�
		param->objectHwnd,											//�����ھ��
		NULL,											//û�в˵����
		GetModuleHandle(NULL),							//����ʵ�����
		NULL									    //û���û�����
	);
	if (hwnd == NULL) {
		MessageBoxW(NULL, param->language->CreateWindowError, param->language->error, MB_ICONERROR);
		delete param;
		return 0;
	}
	SetWindowLongW(hwnd, 0, (LONG)param);
	param->hwnd = hwnd;
	WinControl* Control = new WinControl(hwnd, info.rcClient.bottom - info.rcClient.top, param->language,param->objectTextHwnd);
	param->Control = Control;
	Control->click_But(1);
	//MyRichEditView RichEdit = MyRichEditView(hwnd, info.rcClient.bottom - info.rcClient.top, info.rcClient.right - info.rcClient.left, param->language);
	HWND RichEditHwnd = Control->RichEditHWND();
	if (RichEditHwnd == NULL) {
		delete param;
		return 0;
	}
	param->RichEditHwnd = RichEditHwnd;
	int width = info.rcClient.right - info.rcClient.left + 10;
	MoveWindow(param->objectHwnd, rect.left, rect.top, width > 500 ? width : 500, rect.bottom - rect.top + 200, true);
	UpdateWindow(hwnd);//ˢ�´��ڿͻ���
	ShowWindow(hwnd, SW_SHOW);
	CreateThread(NULL, 0, monitor, param, 0, NULL);//���������߳�
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))//����Ϣ������ȡ����Ϣ,������Ϣ����������,ֱ��GetMessage ��������FALSE ,������Ϣѭ��
	{
		TranslateMessage(&msg);//ת��������Ϣ
		DispatchMessageW(&msg);//����Ϣ���͸���Ϣ������
	}
	delete param;
	delete Control;
	ExitThread(0);
	return 0;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY://�������ٴ���
		PostQuitMessage(0);	//����Ϣ����Ͷ��һ��WM_QUIT ��Ϣ,��ʹGetMessage ��������0,������Ϣѭ��
		break;
	case WM_COMMAND:
		Paramter* param = (Paramter*)GetWindowLongW(hwnd, 0);
		if (HIWORD(wParam) == BN_CLICKED) {
			param->Control->click_But(LOWORD(wParam));
		}
		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);	// �����ǲ��������Ϣ����ϵͳ��Ĭ�ϴ���
}
WinForm::WinForm(HWND h, HWND textH, const Language* L) {
	Paramter* param = new Paramter{ NULL, h, textH, L, NULL };
	CreateThread(NULL, 0, winFormTask, param, 0, NULL);
}