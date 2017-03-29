#include "WinControl.h"
#include <commctrl.h>
#pragma comment(lib,"comctl32.lib")
/*CreatePopupMenu() https://msdn.microsoft.com/en-us/library/windows/desktop/ms647626(v=vs.85).aspx */
#define button_1 1
#define button_2 2
HWND CreateToolTip(HWND hwndTool, HWND hDlg, LPWSTR pszText);
WinControl::WinControl(HWND hwnd, int width, int height, const Language* L, HWND textHWND) {
	this->top = top;
	this->textHWND = textHWND;
	RichEdit = new MyRichEditView(hwnd, 5, 0, width - 10, height * 7 / 10, L);
	//this->target = target;
	HWND but1 = CreateWindowW(
		TEXT("button"),/*   Builtin   button   class   */
		L->gainText,
		WS_BORDER | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		10, 160, 80, height * 3 / 20,
		hwnd,/*   Parent   is   this   window.   */
		(HMENU)button_1,/*   Control   ID:   1   */
		GetModuleHandle(NULL),
		NULL
	);
	HWND but2 = CreateWindowW(
		TEXT("button"),/*   Builtin   button   class   */
		L->applyText,
		WS_BORDER | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		100, 160, 80, height * 3 / 20,
		hwnd,/*   Parent   is   this   window.   */
		(HMENU)button_2,/*   Control   ID:   1   */
		GetModuleHandle(NULL),
		NULL
	);
	CreateToolTip(but1, hwnd, L->gainTipText);
	CreateToolTip(but2, hwnd, L->applyTipText);
}
void WinControl::click_But(WORD hwnd_but) {
	switch (hwnd_but) {
	case button_1:
	{
		int size = 100;//成员数
		int len = size * sizeof(WCHAR);//缓冲区大小
		LPWSTR text = (LPWSTR)malloc(len);
		int reInt = GetWindowTextW(textHWND, text, size);
		while (reInt >= size) {
			free(text);
			size = reInt + 1;
			len = size * sizeof(WCHAR);
			text = (LPWSTR)malloc(len);
			reInt = GetWindowTextW(textHWND, text, size);
		}
		RichEdit->setText(text, size);
		free(text);
		break;
	}
	case button_2:
		LPWSTR text = (LPWSTR)malloc(100 * sizeof(WCHAR));
		int start = 0;
		COLORREF color = 16777215;
		int re = RichEdit->getText(text, 100, &start, &color);
		SendMessageW(textHWND, WM_SETTEXT, 0, (LPARAM)TEXT(""));
		SendMessageW(textHWND, EM_REPLACESEL, false, (LPARAM)text);
		while (re == 0) {
			re = RichEdit->getText(text, 100, &start, &color);
			SendMessageW(textHWND, EM_REPLACESEL, false, (LPARAM)text);
		}
		free(text);
		if (color != 16777215) {
			SendMessageW(textHWND, EM_REPLACESEL, false, (LPARAM)TEXT("|r"));
		}
		break;
	}
}
HWND WinControl::RichEditHWND() {
	return RichEdit->getHwnd();
}
MyRichEditView* WinControl::RichEditView() {
	return RichEdit;
}
WinControl::~WinControl() {
}
HWND CreateToolTip(HWND hwndTool, HWND hDlg, LPWSTR pszText) {
	if (!hwndTool || !hDlg || !pszText) {
		return FALSE;
	}

	// Create the tooltip. g_hInst is the global instance handle.
	HWND hwndTip = CreateWindowExW(NULL, TOOLTIPS_CLASSW, NULL,
		WS_POPUP | TTS_ALWAYSTIP | TTS_BALLOON,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		hDlg, NULL,
		GetModuleHandle(NULL), NULL);

	if (!hwndTool || !hwndTip) {
		return (HWND)NULL;
	}

	// Associate the tooltip with the tool.
	TTTOOLINFOW toolInfo = { 0 };
	toolInfo.cbSize = sizeof(toolInfo) - sizeof(void*);
	toolInfo.hwnd = hDlg;
	toolInfo.uFlags = TTF_IDISHWND | TTF_SUBCLASS;
	toolInfo.uId = (UINT_PTR)hwndTool;
	toolInfo.lpszText = pszText;
	SendMessage(hwndTip, TTM_ADDTOOL, 0, (LPARAM)&toolInfo);
	return hwndTip;
}