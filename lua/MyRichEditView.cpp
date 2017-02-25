#include <regex>

#include "MyRichEditView.h"
MyRichEditView::MyRichEditView(HWND hwndParent, long top,long width ,const Language* L)
{
	/*InitCommonControls();
	HINSTANCE hinstrich = LoadLibraryW(TEXT("RichEd20.Dll"));
	if (!hinstrich) {
		::MessageBoxW(NULL, L->lessDLL, L->error, MB_ICONHAND);
		return;
	}
	CREATESTRUCTW createstruct;
	createstruct.lpCreateParams = NULL;
	createstruct.hInstance = GetModuleHandle(NULL);
	createstruct.hMenu = NULL;
	createstruct.hwndParent = hwndParent;
	createstruct.cy = 100;
	createstruct.cx = 100;
	createstruct.y = 0;
	createstruct.x = 0;
	createstruct.style = WS_BORDER | WS_CHILD | WS_VISIBLE | ES_MULTILINE | WS_VSCROLL | ES_AUTOVSCROLL | WS_TABSTOP;
	createstruct.lpszName = TEXT("");
	createstruct.lpszClass = RICHEDIT_CLASSW;
	createstruct.dwExStyle = 0;
	if (!CRichEditView::PreCreateWindow(createstruct)) {
		::MessageBoxW(NULL, L->CreateRichEditViewerror, L->error, MB_ICONHAND);
		return;
	}*/
	InitCommonControls();
	HINSTANCE hinstrich = LoadLibraryW(TEXT("RichEd20.Dll"));
	if (!hinstrich) {
		MessageBoxW(NULL, L->lessDLL, L->error, MB_ICONHAND);
		return;
	}
	hRichEdit = CreateWindowExW(0, RICHEDIT_CLASSW, TEXT(""),
		WS_BORDER | WS_CHILD | WS_VISIBLE |
		ES_MULTILINE | WS_VSCROLL|WS_HSCROLL | ES_AUTOVSCROLL | WS_TABSTOP,
		0, top, width, 100, hwndParent, NULL, GetModuleHandle(NULL), NULL);
	if (hRichEdit == NULL)
	{
		MessageBoxW(NULL, L->CreateRichEditViewerror, L->error, MB_ICONHAND);
		return;
	}
	//ShowWindow(hRichEdit, SW_SHOW);	 //隐藏窗口	 

	//UpdateWindow(hRichEdit);	 //刷新窗口客户区
	//获取选择区域
	CHARRANGE d;
	SendMessage(hRichEdit, EM_EXGETSEL, 0, (LPARAM)&d);
	d.cpMax;
	d.cpMin;
	//替换选择文本
	SendMessage(hRichEdit, EM_REPLACESEL, 0, (LPARAM)TEXT("我有一句妈卖批不知当讲不当讲！"));
	//改变选择区域
	CHARRANGE a;
	a.cpMax = 3;
	a.cpMin = 0;
	SendMessage(hRichEdit, EM_EXSETSEL, 0, (LPARAM)&a);
	//设置选择区域格式
	CHARFORMATA cformat;
	cformat.cbSize = sizeof(cformat);
	cformat.dwMask = CFM_COLOR;
	cformat.crTextColor = RGB(233, 33, 100);
	SendMessage(hRichEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cformat);
	//获取文本长度
	/*GETTEXTLENGTHEX lengthstrust={GTL_NUMCHARS,1200};

 SendMessage(hwndrich,EM_GETTEXTLENGTHEX,(WPARAM)&lengthstrust,(LPARAM)0);

EM_GETTEXTLENGTHEX 消息，用于获取richedit组件中的文本长度，消息附带的参数WPARAM是一个GETTEXTLENGTHEX结构类型，该结构用来决定编辑器文本的长度如何计算。

typedef struct _gettextlengthex {   

DWORD flags;

UINT  codepage;

} GETTEXTLENGTHEX;

Flags的值用来标记该如何计算长度。如GTL_NUMCHARS表示返回字符数

Codepage通常就两种值 ANSI代码页 CP_ACP ，Unicode 1200

方法返回计算的长度值*/
	//获取选择文本内容
	WCHAR* buffer[1000];
	SendMessage(hRichEdit, EM_GETSELTEXT, 0, (LPARAM)buffer);
}

bool MyRichEditView::SetColor()
{
	CHARFORMATW cformat;
	cformat.cbSize = sizeof(cformat);
	cformat.dwMask = CFM_COLOR;
	/*dwMask
Value				Meaning
CFM_ALL			:	CFM_EFFECTS | CFM_SIZE | CFM_FACE | CFM_OFFSET | CFM_CHARSET
CFM_BOLD		:	dwEffects is valid.
CFM_CHARSET		:	bCharSet is valid.
CFM_COLOR		:	crTextColor and CFE_AUTOCOLOR are valid.
CFM_EFFECTS		:	CFM_BOLD | CFM_ITALIC | CFM_UNDERLINE | CFM_COLOR | CFM_STRIKEOUT | CFE_PROTECTED | CFM_LINK
CFM_FACE		:	szFaceName is valid.
CFM_ITALIC		:	dwEffects is valid.
CFM_OFFSET		:	yOffset is valid.
CFM_PROTECTED	:	dwEffects is valid.
CFM_SIZE		:	yHeight is valid.
CFM_STRIKEOUT	:	dwEffects is valid.
CFM_UNDERLINE	:	dwEffects is valid.*/
//cformat.dwEffects;
//cformat.yHeight;
//cformat.yOffset;
	cformat.crTextColor = RGB(0, 0, 0);
	//cformat.bCharSet;
	//cformat.bPitchAndFamily;
	//cformat.szFaceName;
	SendMessage(hRichEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cformat);
	return false;
}

void MyRichEditView::setText(LPWSTR text)
{
}

HWND MyRichEditView::getHwnd()
{
	return hRichEdit;
}
