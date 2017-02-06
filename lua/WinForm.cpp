#include "WinForm.h"
#include <windows.h>

#include "stdio.h"
#include <corecrt_wstdio.h>
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//��Ϣ������ԭ��

bool g_btxt = false;

WinForm::WinForm()
{

	LPCWSTR szClassName = TEXT("WndClass");

	WNDCLASSEX wndclass;	//�����������ڵĲ������WNDCLASSEX �ṹ

	wndclass.cbSize = sizeof(wndclass);	//����ṹ�Ĵ�С

	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	//���崰����ʽ

	wndclass.lpfnWndProc = WndProc;	//ָ�������ڵ���Ϣ������

	wndclass.cbClsExtra = 0;	//û�ж�������ڴ�

	wndclass.cbWndExtra = 0;	//û�ж���Ĵ����ڴ�

	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//ʹ��Ĭ�ϵ�ͼ��

	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);	//ʹ��Ĭ�ϵĹ��

	wndclass.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);	//���崰�ڵı�����ɫΪ��ɫ

	wndclass.hInstance = GetModuleHandle(NULL);	//ʵ�����

	wndclass.lpszClassName = szClassName;	//����������

	wndclass.lpszMenuName = NULL;	//��ʹ�ò˵�

	wndclass.hIconSm = NULL;	//û�����Сͼ��

								//ע�ᴰ����

	::RegisterClassEx(&wndclass);

	//����������

	HWND hwnd = ::CreateWindowEx(0,	 //��������չ��ʽ

		szClassName,	 //����

		TEXT("Hello world"),	 //���ڱ���

		WS_OVERLAPPEDWINDOW,	 //���ڷ��

		CW_USEDEFAULT,	 //Ĭ�ϵĴ���X ������

		CW_USEDEFAULT,	 //Ĭ�ϵĴ���Y ������

		CW_USEDEFAULT,	 //Ĭ�ϵĴ��ڿ��

		CW_USEDEFAULT,	 //Ĭ�ϵĴ��ڸ߶�

		NULL,	 //û�и����ھ��

		NULL,	 //û�в˵����

		GetModuleHandle(NULL),	 //����ʵ�����

		NULL);	 //û���û�����

	if (hwnd == NULL)

	{

		::MessageBox(NULL, TEXT("�������ڳ���"), TEXT("error"), MB_ICONHAND);

	}



	::ShowWindow(hwnd, SW_SHOW);	 //��ʾ����	 

	::UpdateWindow(hwnd);	 //ˢ�´��ڿͻ���

	MSG msg;

	while (::GetMessage(&msg, NULL, 0, 0))   //����Ϣ������ȡ����Ϣ,������Ϣ����������,ֱ��GetMessage ��������FALSE ,������Ϣѭ��

	{



		::TranslateMessage(&msg);	 //ת��������Ϣ



		::DispatchMessage(&msg);	 //����Ϣ���͸���Ϣ������

	}


}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)

{

	LPCWSTR szText = TEXT("My first window process ");

	HDC hdc;	//�����豸�������

	PAINTSTRUCT ps;

	switch (msg)

	{

	case WM_PAINT:	//���ڿͻ�����Ҫ�ػ�

	{

		if (g_btxt == false)

		{

			hdc = ::BeginPaint(hwnd, &ps);	//ʹ��Ч�Ŀͻ��������Ч,��ȡ���豸�������

			::TextOut(hdc, 0, 0, szText, sizeof(szText)/sizeof(WCHAR));

			::EndPaint(hwnd, &ps);

			g_btxt = true;

		}

		return 0;

	}

	case WM_DESTROY:	//�������ٴ���

	{

		::PostQuitMessage(0);	//����Ϣ����Ͷ��һ��WM_QUIT ��Ϣ,��ʹGetMessage ��������0,������Ϣѭ��

		return 0;

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

		UINT x, y;

		WCHAR* info = new WCHAR[50];

		x = LOWORD(lParam);

		y = HIWORD(lParam);

		swprintf(info,TEXT("%d_%d"), x, y);

		MessageBox(hwnd, info, TEXT("mouse info"), MB_OK);

		delete info;

		break;

	}

	return ::DefWindowProc(hwnd, msg, wParam, lParam);	// �����ǲ��������Ϣ����ϵͳ��Ĭ�ϴ���

}
