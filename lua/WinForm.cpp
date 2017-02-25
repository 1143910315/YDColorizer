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
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);//消息处理函数原形
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
	LPCWSTR szClassName = TEXT("WndClass");//窗口类名
	//用描述主窗口
	WNDCLASSEXW wndclass{
		sizeof(wndclass),								//定义结构的大小
		CS_HREDRAW | CS_VREDRAW | CS_OWNDC,				//定义窗口样式
		WndProc,										//指定本窗口的消息处理函数
		NULL, NULL,										//没有额外的类内存，没有额外的窗口内存
		GetModuleHandleW(NULL),							//实例句柄
		LoadIconW(NULL, IDI_APPLICATION),				//使用默认的图标
		LoadCursorW(NULL, IDC_ARROW),					//使用默认的光标
		(HBRUSH)(COLOR_3DFACE + 1),						//定义窗口的背景颜色为灰色
		NULL,											//不使用菜单
		szClassName,									//窗口类名称
		NULL											//没有类的小图标
	};
	RegisterClassExW(&wndclass);//注册窗口类
	//主窗口的窗口句柄
	HWND hwnd = CreateWindowExW(
		0,												//不定义扩展样式
		szClassName,									//类名
		NULL,											//窗口标题
		WS_EX_TOOLWINDOW,								//窗口风格，不在任务栏显示
		-100, -100, 0, 0,								//窗口X轴坐标，Y轴坐标，窗口宽度，窗口高度
		NULL,											//父窗口句柄
		NULL,											//没有菜单句柄
		GetModuleHandle(NULL),							//程序实例句柄
		NULL											//没有用户数据
	);
	if (hwnd == NULL)
	{
		MessageBoxW(NULL, TEXT("创建窗口出错"), TEXT("error"), MB_ICONHAND);
		delete param;
		return 0;
	}
	param->hwnd = hwnd;
	WINDOWINFO info;
	GetWindowInfo(param->previousHwnd, &info);
	RECT rect = info.rcWindow;
	MyRichEditView RichEdit = MyRichEditView(hwnd, info.rcClient.bottom - info.rcClient.top, info.rcClient.right - info.rcClient.left, param->language);
	UpdateWindow(hwnd);	 //刷新窗口客户区

	MoveWindow(param->previousHwnd, rect.left, rect.top, rect.right - rect.left + 200, rect.bottom - rect.top + 200, true);
	SetParent(RichEdit.getHwnd(), param->previousHwnd);
	CreateThread(NULL, 0, monitor, NULL, 0, NULL);
	param->RichEditHwnd = RichEdit.getHwnd();
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))   //从消息队列中取出消息,交给消息处理函数处理,直到GetMessage 函数返回FALSE ,结束消息循环
	{
		TranslateMessage(&msg);	 //转化键盘消息
		DispatchMessage(&msg);	 //将消息发送给消息处理函数

	}
	delete param;
	ExitThread(0);
	//FreeLibrary(hinstrich);
	return 0;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)

{

	//LPCWSTR szText = TEXT("My first window process ");

	//HDC hdc;	//声明设备环境句柄

	//PAINTSTRUCT ps;

	switch (msg)

	{

	case WM_PAINT:	//窗口客户区需要重画

	{
		//ShowWindow(hwnd, SW_HIDE);
		//if (g_btxt == false)
		//{
		//	hdc = BeginPaint(hwnd, &ps);	//使无效的客户区变得有效,并取得设备环境句柄
		//	TextOutW(hdc, 0, 0, szText, sizeof(szText) / sizeof(WCHAR));
		//	EndPaint(hwnd, &ps);
		//	g_btxt = true;

		//}
		//return 0;

	}

	case WM_DESTROY:	//正在销毁窗口

	{

		PostQuitMessage(0);	//向消息队列投递一个WM_QUIT 消息,促使GetMessage 函数返回0,结束消息循环

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

	return DefWindowProc(hwnd, msg, wParam, lParam);	// 将我们不处理的消息交给系统做默认处理

}
WinForm::WinForm(HWND h, const Language* L)
{
	Paramter* param = new Paramter{ NULL, h, L, NULL };
	CreateThread(NULL, 0, winFormTask, param, 0, NULL);
}