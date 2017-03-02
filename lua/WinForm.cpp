#include "WinForm.h"
#include "MyRichEditView.h"
#include "Tool.h"
#include <windows.h>
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);//��Ϣ������ԭ��
//������Ϣ�ṹ������ӳ�Ա�����ĩβ��������������������󣡣�
struct Paramter {
	HWND hwnd = NULL;//α���ڣ����Ǽٵģ�
	HWND objectHwnd = NULL;//��൯�����
	HWND objectTextHwnd = NULL;//��൯�����ı���ľ��
	const Language* language = NULL;//���԰���һ��DLLֻ����һ��
	HWND RichEditHwnd = NULL;//���ı��ؼ����
	MyRichEditView* RichEditView = NULL;//���ı���ָ��
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
	while (IsWindow(param->objectHwnd)) {
		WINDOWINFO info;
		GetWindowInfo(param->RichEditHwnd, &info);
		RECT rect = info.rcWindow;
		WINDOWINFO info1;
		GetWindowInfo(param->objectHwnd, &info1);
		RECT rect1 = info1.rcClient;
		MoveWindow(param->RichEditHwnd, rect.left - rect1.left, rect.top - rect1.top, rect.right - rect.left, rect.bottom - rect.top, true);
		int size = 100;//��Ա��
		int len = size * sizeof(WCHAR);//��������С
		LPWSTR text = (LPWSTR)malloc(len);
		int reInt = GetWindowTextW(param->objectTextHwnd, text, size);
		while (reInt >= size) {
			free(text);
			size = reInt + 1;
			len = size * sizeof(WCHAR);
			text = (LPWSTR)malloc(len);
			reInt = GetWindowTextW(param->objectTextHwnd, text, size);
		}
		param->RichEditView->setText(text, size);
		free(text);
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
		NULL,										    //����Ĵ����ڴ�
		GetModuleHandleW(NULL),							//ʵ�����
		LoadIconW(NULL, IDI_APPLICATION),				//ʹ��Ĭ�ϵ�ͼ��
		LoadCursorW(NULL, IDC_ARROW),					//ʹ��Ĭ�ϵĹ��
		(HBRUSH)(COLOR_3DFACE + 1),						//���崰�ڵı�����ɫΪ��ɫ
		NULL,											//��ʹ�ò˵�
		szClassName,									//����������
		NULL											//û�����Сͼ��
	};
	RegisterClassExW(&wndclass);//ע�ᴰ����
	//�����ڵĴ��ھ��
	HWND hwnd = CreateWindowExW(
		0,												//��������չ��ʽ
		szClassName,									//����
		NULL,											//���ڱ���
		WS_EX_TOOLWINDOW,								//���ڷ�񣬲�����������ʾ
		-100, -100, 0, 0,								//����X�����꣬Y�����꣬���ڿ�ȣ����ڸ߶�
		NULL,											//�����ھ��
		NULL,											//û�в˵����
		GetModuleHandle(NULL),							//����ʵ�����
		lpParamter									    //û���û�����
	);
	if (hwnd == NULL) {
		MessageBoxW(NULL, param->language->CreateWindowError, param->language->error, MB_ICONERROR);
		delete param;
		return 0;
	}
	param->hwnd = hwnd;
	WINDOWINFO info;
	GetWindowInfo(param->objectHwnd, &info);
	RECT rect = info.rcWindow;
	MyRichEditView RichEdit = MyRichEditView(hwnd, info.rcClient.bottom - info.rcClient.top, info.rcClient.right - info.rcClient.left, param->language);
	HWND RichEditHwnd = RichEdit.getHwnd();
	if (RichEditHwnd == NULL) {
		delete param;
		return 0;
	}
	param->RichEditView = &RichEdit;
	param->RichEditHwnd = RichEditHwnd;
	UpdateWindow(hwnd);//ˢ�´��ڿͻ���
	MoveWindow(param->objectHwnd, rect.left, rect.top, rect.right - rect.left + 10, rect.bottom - rect.top + 150, true);
	SetParent(RichEditHwnd, param->objectHwnd);
	CreateThread(NULL, 0, monitor, param, 0, NULL);//���������߳�
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))//����Ϣ������ȡ����Ϣ,������Ϣ����������,ֱ��GetMessage ��������FALSE ,������Ϣѭ��
	{
		TranslateMessage(&msg);//ת��������Ϣ
		DispatchMessageW(&msg);//����Ϣ���͸���Ϣ������
	}
	delete param;
	ExitThread(0);
	return 0;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY://�������ٴ���
	{
		PostQuitMessage(0);	//����Ϣ����Ͷ��һ��WM_QUIT ��Ϣ,��ʹGetMessage ��������0,������Ϣѭ��
	}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);	// �����ǲ��������Ϣ����ϵͳ��Ĭ�ϴ���
}
WinForm::WinForm(HWND h, HWND textH, const Language* L) {
	Paramter* param = new Paramter{ NULL, h, textH, L, NULL };
	CreateThread(NULL, 0, winFormTask, param, 0, NULL);
}