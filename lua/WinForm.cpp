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
//各种信息结构，想添加成员请加至末尾，否则可能引发参数错误！！
struct Paramter
{
	HWND hwnd = NULL;//伪窗口，这是假的！
	HWND objectHwnd = NULL;//物编弹窗句柄
	HWND objectTextHwnd = NULL;//物编弹窗里文本框的句柄
	const Language* language = NULL;//语言包，一个DLL只创建一次
	HWND RichEditHwnd = NULL;//富文本控件句柄
	MyRichEditView* RichEditView = NULL;//富文本类指针
};
/*************************************************
Function:         |monitor
Description:      |监视物编弹窗是否被关闭，同时监视物编文本改变
Calls:            |
Input:            |Paramter：额外数据
Others:           |用于释放创建的窗口
*************************************************/
DWORD WINAPI monitor(LPVOID lpParamter) {
	Paramter* param = (Paramter*)lpParamter;
	Tool T = Tool();
	while (IsWindow(param->objectHwnd))
	{
		WINDOWINFO info;
		GetWindowInfo(param->RichEditHwnd, &info);
		RECT rect = info.rcWindow;
		WINDOWINFO info1;
		GetWindowInfo(param->objectHwnd, &info1);
		RECT rect1 = info1.rcClient;
		MoveWindow(param->RichEditHwnd, rect.left - rect1.left, rect.top - rect1.top, rect.right - rect.left, rect.bottom - rect.top, true);
		int len = 100 * sizeof(WCHAR);//缓冲区大小
		LPWSTR text = (LPWSTR)malloc(len);
		/*int reInt =*/ GetWindowTextW(param->objectTextHwnd, text, len);//TODO 如果缓存不够，reInt等于缓存区大小，以后处理
		text[len / sizeof(len) - 1] = NULL;//临时策略，防止溢出，当适配了内存后将不再需要
		//param->RichEditView->setText(text,len);
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
	GetWindowInfo(param->objectHwnd, &info);
	RECT rect = info.rcWindow;
	MyRichEditView RichEdit = MyRichEditView(hwnd, info.rcClient.bottom - info.rcClient.top, info.rcClient.right - info.rcClient.left, param->language);
	param->RichEditView = &RichEdit;
	UpdateWindow(hwnd);	 //刷新窗口客户区

	MoveWindow(param->objectHwnd, rect.left, rect.top, rect.right - rect.left + 200, rect.bottom - rect.top + 200, true);
	SetParent(RichEdit.getHwnd(), param->objectHwnd);
	CreateThread(NULL, 0, monitor, param, 0, NULL);
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
WinForm::WinForm(HWND h, HWND textH, const Language* L)
{
	Paramter* param = new Paramter{ NULL, h, textH, L, NULL };
	CreateThread(NULL, 0, winFormTask, param, 0, NULL);
}