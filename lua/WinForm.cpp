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
		text[size - 1] = NULL;//��ֹ���
		param->RichEditView->setText(text, size);
		free(text);
		/*char str[10];
		sprintf(str, "%d", reInt);
		MessageBox(NULL, text, T.ChartoWCHAR(str, 10), MB_OK);*/
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
		MessageBoxW(NULL, TEXT("�������ڳ���"), TEXT("error"), MB_ICONHAND);
		delete param;
		return 0;
	}
	param->hwnd = hwnd;
	//SetWindowLongW(hwnd, 0, (LONG)param);
	//Paramter* param1 = (Paramter*)GetWindowLongW(hwnd, 0);
	WINDOWINFO info;
	GetWindowInfo(param->objectHwnd, &info);
	RECT rect = info.rcWindow;
	MyRichEditView RichEdit = MyRichEditView(hwnd, info.rcClient.bottom - info.rcClient.top, info.rcClient.right - info.rcClient.left, param->language);
	param->RichEditView = &RichEdit;
	UpdateWindow(hwnd);	 //ˢ�´��ڿͻ���

	MoveWindow(param->objectHwnd, rect.left, rect.top, rect.right - rect.left + 10, rect.bottom - rect.top + 150, true);
	SetParent(RichEdit.getHwnd(), param->objectHwnd);
	CreateThread(NULL, 0, monitor, param, 0, NULL);
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

	HDC hdc;	//�����豸�������
	static HWND hwndButton;
	//PAINTSTRUCT ps;
	static Paramter* param;
	switch (msg)

	{
	case   WM_CREATE:
	{
		/*   The   window   is   being   created.   Create   our   button
		*   window   now.   */
		//TEXTMETRIC   tm;

		/*   First   we   use   the   system   fixed   font   size   to   choose
		*   a   nice   button   size.   */
		//hdc = GetDC(hwnd);
		//SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
		//GetTextMetrics(hdc, &tm);
		//long cx = tm.tmAveCharWidth * 30;
		//long cy = (tm.tmHeight + tm.tmExternalLeading) * 2;
		//ReleaseDC(hwnd, hdc);

		/*   Now   create   the   button   */
		//param = (Paramter*)lParam;
		//param = (Paramter*)param->hwnd;//����ָ��ָ���ڴ��������Ϊָ�롣����Ȼ���Ҳ�֪����ô��������
		//hwndButton = CreateWindowW(
		//	TEXT("button"),/*   Builtin   button   class   */
		//	TEXT("Click   Here "),
		//	WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		//	200, 100, 100,300,
		//	hwnd,/*   Parent   is   this   window.   */
		//	(HMENU)1,/*   Control   ID:   1   */
		//	GetModuleHandle(NULL),
		//	NULL
		//);
		//SetParent(hwndButton, param->objectHwnd);
		//int i=GetLastError();
		return   0;
	}
	//case   WM_COMMAND:
	//	/*   Check   the   control   ID,   notification   code   and
	//	*   control   handle   to   see   if   this   is   a   button   click
	//	*   message   from   our   child   button.   */
	//	if (LOWORD(wParam) == 1 && HIWORD(wParam) == BN_CLICKED && (HWND)lParam == hwndButton) {
	//		/*   Our   button   was   clicked.   Close   the   window.   */
	//		//Paramter* param = (Paramter*)GetWindowLong(hwnd, 0);
	//		int size = 100;//��Ա��
	//		int len = size * sizeof(WCHAR);//��������С
	//		LPWSTR text = (LPWSTR)malloc(len);
	//		int reInt = GetWindowTextW(param->objectTextHwnd, text, size);
	//		while (reInt >= size) {
	//			free(text);
	//			size = reInt + 1;
	//			len = size * sizeof(WCHAR);
	//			text = (LPWSTR)malloc(len);
	//			reInt = GetWindowTextW(param->objectTextHwnd, text, size);
	//		}
	//		text[size - 1] = NULL;//��ֹ���
	//		param->RichEditView->setText(text, size);
	//		free(text);
	//	}
	case WM_PAINT:	//���ڿͻ�����Ҫ�ػ�

	{
		//HWND hwnd = (HWND)lParam;
		//if (IsWindow(hwnd)) {
		//	PAINTSTRUCT ps;
		//	HDC hdc = BeginPaint(hwnd, &ps);
		//	//SetBkMode(hdc, OPAQUE);
		//	//SetTextColor(hdc, RGB(255, 0, 0));
		//	SetBkColor(hdc, RGB(0, 0, 0));
		//	//TextOut(hdc, 0, 0, msg, sizeof(msg) - 1);
		//	//ValidateRect(hwnd,NULL);
		//	EndPaint(hwnd, &ps);
		//	break;
		//}

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
	case WM_CTLCOLOREDIT:
	{
		/*HDC hdc = (HDC)wParam;
		SetBkMode(hdc, OPAQUE);
		SetBkColor(hdc, RGB(255, 0, 0));
		ReleaseDC(hwnd, hdc);

		return (LRESULT)NULL;*/

		//COLORREF c=SetBkColor((HDC)wParam, RGB(255, 0, 0));
		//break;

		//HWND hwnd = (HWND)lParam;
		//if (IsWindow(hwnd)) {
		//	HDC hdc2 = (HDC)wParam;
		//	//SetTextColor(hdc2, RGB(255, 0, 0));
		//	SetBkColor(hdc2, RGB(0, 0, 0));
		//	//SetBkMode(hdc2, OPAQUE);
		//	break;
		//}
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
WinForm::WinForm(HWND h, HWND textH, const Language* L) {
	Paramter* param = new Paramter{ NULL, h, textH, L, NULL };
	CreateThread(NULL, 0, winFormTask, param, 0, NULL);
}