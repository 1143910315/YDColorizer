#include "WinForm.h"
#include "MyRichEditView.h"
#include "Tool.h"
#include "WinControl.h"
#include <windows.h>
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);//消息处理函数原形
//各种信息结构，想添加成员请加至末尾，否则可能引发参数错误！！
struct Paramter {
	HWND hwnd = NULL;//伪窗口，这是假的！
	HWND objectHwnd = NULL;//物编弹窗句柄
	HWND objectTextHwnd = NULL;//物编弹窗里文本框的句柄
	const Language* language = NULL;//语言包，一个DLL只创建一次
	HWND RichEditHwnd = NULL;//富文本控件句柄
	WinControl* Control = NULL;//窗口其它基本控件
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
	LPCWSTR szClassName = TEXT("WndClass");//窗口类名
	//用描述主窗口
	WNDCLASSEXW wndclass{
		sizeof(wndclass),								//定义结构的大小
		CS_HREDRAW | CS_VREDRAW | CS_OWNDC,				//定义窗口样式
		WndProc,										//指定本窗口的消息处理函数
		NULL,                                           //没有额外的类内存
		sizeof(Paramter*),								//额外的窗口内存
		GetModuleHandleW(NULL),							//实例句柄
		LoadIconW(NULL, IDI_APPLICATION),				//使用默认的图标
		LoadCursorW(NULL, IDC_ARROW),					//使用默认的光标
		(HBRUSH)(COLOR_3DFACE + 1),						//定义窗口的背景颜色为灰色
		NULL,											//不使用菜单
		szClassName,									//窗口类名称
		NULL											//没有类的小图标
	};
	RegisterClassExW(&wndclass);//注册窗口类
	WINDOWINFO info;
	GetWindowInfo(param->objectHwnd, &info);
	RECT rect = info.rcWindow;
	//主窗口的窗口句柄
	HWND hwnd = CreateWindowExW(
		0,												//不定义扩展样式
		szClassName,									//类名
		NULL,											//窗口标题
		WS_CHILDWINDOW,								//窗口风格，不在任务栏显示
		0, info.rcClient.bottom - info.rcClient.top, 500, 200,								//窗口X轴坐标，Y轴坐标，窗口宽度，窗口高度
		param->objectHwnd,											//父窗口句柄
		NULL,											//没有菜单句柄
		GetModuleHandle(NULL),							//程序实例句柄
		NULL									    //没有用户数据
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
	UpdateWindow(hwnd);//刷新窗口客户区
	ShowWindow(hwnd, SW_SHOW);
	CreateThread(NULL, 0, monitor, param, 0, NULL);//启动监视线程
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))//从消息队列中取出消息,交给消息处理函数处理,直到GetMessage 函数返回FALSE ,结束消息循环
	{
		TranslateMessage(&msg);//转化键盘消息
		DispatchMessageW(&msg);//将消息发送给消息处理函数
	}
	delete param;
	delete Control;
	ExitThread(0);
	return 0;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY://正在销毁窗口
		PostQuitMessage(0);	//向消息队列投递一个WM_QUIT 消息,促使GetMessage 函数返回0,结束消息循环
		break;
	case WM_COMMAND:
		Paramter* param = (Paramter*)GetWindowLongW(hwnd, 0);
		if (HIWORD(wParam) == BN_CLICKED) {
			param->Control->click_But(LOWORD(wParam));
		}
		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);	// 将我们不处理的消息交给系统做默认处理
}
WinForm::WinForm(HWND h, HWND textH, const Language* L) {
	Paramter* param = new Paramter{ NULL, h, textH, L, NULL };
	CreateThread(NULL, 0, winFormTask, param, 0, NULL);
}