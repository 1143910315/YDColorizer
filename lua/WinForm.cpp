#include "WinForm.h"
#include <windows.h>
//#include <commctrl.h>
//#include <Richedit.h>
//#include <afxrich.h>
//#pragma comment(lib,"comctl32.lib")
//#include "stdio.h"
#include <corecrt_wstdio.h>
#include "MyRichEditView.h"
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//消息处理函数原形

bool g_btxt = false;

WinForm::WinForm(HWND h, const Language* L)
{
	IsWindow(h);
	LPCWSTR szClassName = TEXT("WndClass");

	WNDCLASSEX wndclass;	//用描述主窗口的参数填充WNDCLASSEX 结构

	wndclass.cbSize = sizeof(wndclass);	//定义结构的大小

	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	//定义窗口样式

	wndclass.lpfnWndProc = WndProc;	//指定本窗口的消息处理函数

	wndclass.cbClsExtra = 0;	//没有额外的类内存

	wndclass.cbWndExtra = 0;	//没有额外的窗口内存

	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//使用默认的图标

	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);	//使用默认的光标

	wndclass.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);	//定义窗口的背景颜色为灰色

	wndclass.hInstance = GetModuleHandle(NULL);	//实例句柄

	wndclass.lpszClassName = szClassName;	//窗口类名称

	wndclass.lpszMenuName = NULL;	//不使用菜单

	wndclass.hIconSm = NULL;	//没有类的小图标

								//注册窗口类

	::RegisterClassEx(&wndclass);

	//创建主窗口

	HWND hwnd = ::CreateWindowEx(0,	 //不定义扩展样式

		szClassName,	 //类名

		TEXT("Hello world"),	 //窗口标题

		WS_OVERLAPPED | 
			WS_CAPTION | 
			WS_SYSMENU 
			  ,	 //窗口风格

		100,	 //默认的窗口X 轴坐标

		100,	 //默认的窗口Y 轴坐标

		300,	 //默认的窗口宽度

		200,	 //默认的窗口高度

		NULL,	 //父窗口句柄

		NULL,	 //没有菜单句柄

		GetModuleHandle(NULL),	 //程序实例句柄

		NULL);	 //没有用户数据

	if (hwnd == NULL)

	{

		::MessageBox(NULL, TEXT("创建窗口出错"), TEXT("error"), MB_ICONHAND);
		return;

	}
	MyRichEditView RichEdit = MyRichEditView(hwnd,L);
	//InitCommonControls();
	//HINSTANCE hinstrich = LoadLibraryW(TEXT("RichEd20.Dll"));
	//if (!hinstrich) {
	//	::MessageBox(NULL, TEXT("缺少RichEd20.Dll"), TEXT("error"), MB_ICONHAND);
	//	return;
	//}
	//HWND hRichEdit = CreateWindowExW(0, RICHEDIT_CLASSW, TEXT(""),
	//	WS_BORDER | WS_CHILD | WS_VISIBLE |
	//	ES_MULTILINE | WS_VSCROLL | ES_AUTOVSCROLL | WS_TABSTOP,
	//	0, 0, 100, 100, hwnd, NULL, GetModuleHandle(NULL), NULL);
	//if (hRichEdit == NULL)
	//{
	//	::MessageBox(NULL, TEXT("创建富文本框出错"), TEXT("error"), MB_ICONHAND);
	//	return;
	//}
	//CREATESTRUCTW h;
	//h.cx = 0;
	//CRichEditView::PreCreateWindow(cs);
	ShowWindow(hwnd, SW_SHOW);	 //显示窗口	 

	UpdateWindow(hwnd);	 //刷新窗口客户区

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))   //从消息队列中取出消息,交给消息处理函数处理,直到GetMessage 函数返回FALSE ,结束消息循环

	{



		::TranslateMessage(&msg);	 //转化键盘消息



		::DispatchMessage(&msg);	 //将消息发送给消息处理函数

	}

	//FreeLibrary(hinstrich);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)

{

	LPCWSTR szText = TEXT("My first window process ");

	HDC hdc;	//声明设备环境句柄

	PAINTSTRUCT ps;

	switch (msg)

	{

	case WM_PAINT:	//窗口客户区需要重画

	{

		if (g_btxt == false)

		{

			hdc = BeginPaint(hwnd, &ps);	//使无效的客户区变得有效,并取得设备环境句柄

			TextOutW(hdc, 0, 0, szText, sizeof(szText) / sizeof(WCHAR));

			EndPaint(hwnd, &ps);

			g_btxt = true;

		}

		return 0;

	}

	case WM_DESTROY:	//正在销毁窗口

	{

		::PostQuitMessage(0);	//向消息队列投递一个WM_QUIT 消息,促使GetMessage 函数返回0,结束消息循环

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

		//UINT x, y;

		//WCHAR* info = new WCHAR[50];

		//x = LOWORD(lParam);

		//y = HIWORD(lParam);

		//swprintf(info, TEXT("%d_%d"), x, y);

		//MessageBox(hwnd, info, TEXT("mouse info"), MB_OK);

		//delete info;

		break;

	}

	return ::DefWindowProc(hwnd, msg, wParam, lParam);	// 将我们不处理的消息交给系统做默认处理

}
