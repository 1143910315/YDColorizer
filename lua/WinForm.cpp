#include "WinForm.h"
#include <windows.h>
//#include <commctrl.h>
//#include <Richedit.h>
//#include <afxrich.h>
//#pragma comment(lib,"comctl32.lib")
#include <stdio.h>
#include <corecrt_wstdio.h>
#include "MyRichEditView.h"
#include "Tool.h"
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);//��Ϣ������ԭ��
struct Paramter
{
	HWND hwnd = NULL;
	HWND previousHwnd = NULL;
	const Language* language = NULL;
	HWND RichEditHwnd = NULL;
};
DWORD WINAPI monitor(LPVOID lpParamter) {
	Paramter* param = (Paramter*)lpParamter;
	while (IsWindow(param->previousHwnd))
	{
		WINDOWINFO info;
		GetWindowInfo(param->RichEditHwnd, &info);
		RECT rect = info.rcWindow;
		WINDOWINFO info1;
		GetWindowInfo(param->previousHwnd, &info1);
		RECT rect1 = info1.rcClient;
		MoveWindow(param->RichEditHwnd, rect.left - rect1.left, rect.top - rect1.top, rect.right - rect.left, rect.bottom - rect.top, true);
		Sleep(1000);
	};
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
		NULL, NULL,										//û�ж�������ڴ棬û�ж���Ĵ����ڴ�
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
		NULL											//û���û�����
	);
	if (hwnd == NULL)
	{
		MessageBoxW(NULL, TEXT("�������ڳ���"), TEXT("error"), MB_ICONHAND);
		delete param;
		return 0;
	}
	param->hwnd = hwnd;
	WINDOWINFO info;
	GetWindowInfo(param->previousHwnd, &info);
	RECT rect = info.rcWindow;
	MyRichEditView RichEdit = MyRichEditView(hwnd, info.rcClient.bottom - info.rcClient.top, info.rcClient.right - info.rcClient.left, param->language);
	UpdateWindow(hwnd);	 //ˢ�´��ڿͻ���

	MoveWindow(param->previousHwnd, rect.left, rect.top, rect.right - rect.left + 200, rect.bottom - rect.top + 200, true);
	SetParent(RichEdit.getHwnd(), param->previousHwnd);
	CreateThread(NULL, 0, monitor, NULL, 0, NULL);
	param->RichEditHwnd = RichEdit.getHwnd();
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))   //����Ϣ������ȡ����Ϣ,������Ϣ����������,ֱ��GetMessage ��������FALSE ,������Ϣѭ��
	{
		TranslateMessage(&msg);	 //ת��������Ϣ
		DispatchMessage(&msg);	 //����Ϣ���͸���Ϣ������

	}
	delete param;
	ExitThread(0);
	//FreeLibrary(hinstrich);
	return 0;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)

{

	//LPCWSTR szText = TEXT("My first window process ");

	//HDC hdc;	//�����豸�������

	//PAINTSTRUCT ps;

	switch (msg)

	{

	case WM_PAINT:	//���ڿͻ�����Ҫ�ػ�

	{
		//ShowWindow(hwnd, SW_HIDE);
		//if (g_btxt == false)
		//{
		//	hdc = BeginPaint(hwnd, &ps);	//ʹ��Ч�Ŀͻ��������Ч,��ȡ���豸�������
		//	TextOutW(hdc, 0, 0, szText, sizeof(szText) / sizeof(WCHAR));
		//	EndPaint(hwnd, &ps);
		//	g_btxt = true;

		//}
		//return 0;

	}

	case WM_DESTROY:	//�������ٴ���

	{

		PostQuitMessage(0);	//����Ϣ����Ͷ��һ��WM_QUIT ��Ϣ,��ʹGetMessage ��������0,������Ϣѭ��

		//return 0;

	}

	case WM_KEYDOWN:

		switch (wParam)

		{

		case VK_ESCAPE:

			PostMessage(hwnd, WM_QUIT, 0, 0);

			break;

		}

		break;

	case WM_LBUTTONDOWN:

		//UINT x, y;

		//WCHAR* info = new WCHAR[50];

		//x = LOWORD(lParam);

		//y = HIWORD(lParam);

		//swprintf(info, TEXT("%d_%d"), x, y);

		//MessageBox(hwnd, info, TEXT("mouse info"), MB_OK);

		//delete info;

		break;

	}

	return DefWindowProc(hwnd, msg, wParam, lParam);	// �����ǲ��������Ϣ����ϵͳ��Ĭ�ϴ���

}
WinForm::WinForm(HWND h, const Language* L)
{
	Paramter* param = new Paramter{ NULL, h, L, NULL };
	CreateThread(NULL, 0, winFormTask, param, 0, NULL);
}