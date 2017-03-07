#include "WinControl.h"
#define button_1 1
#define button_2 2
WinControl::WinControl(HWND hwnd, int top, const Language* L, HWND textHWND) {
	this->top = top;
	this->textHWND = textHWND;
	RichEdit = new MyRichEditView(hwnd, 0, 390, L);
	//this->target = target;
	CreateWindowW(
		TEXT("button"),/*   Builtin   button   class   */
		L->gainText,
		WS_BORDER | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		0, 160, 100, 30,
		hwnd,/*   Parent   is   this   window.   */
		(HMENU)button_1,/*   Control   ID:   1   */
		GetModuleHandle(NULL),
		NULL
	);
	CreateWindowW(
		TEXT("button"),/*   Builtin   button   class   */
		L->applyText,
		WS_BORDER | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		100, 160, 100, 30,
		hwnd,/*   Parent   is   this   window.   */
		(HMENU)button_2,/*   Control   ID:   1   */
		GetModuleHandle(NULL),
		NULL
	);
	//SetParent(getText_but, target);
}
void WinControl::click_But(WORD hwnd_but) {
	switch (hwnd_but) {
	case button_1:{ 
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
		LPWSTR text = (LPWSTR)malloc(100*sizeof(WCHAR));
		int start = 0;
		COLORREF color= 16777215;
		int re = RichEdit->getText(text, 100, &start,&color);
		SendMessageW(textHWND, WM_SETTEXT, 0, (LPARAM)TEXT(""));
		SendMessageW(textHWND, EM_REPLACESEL, false, (LPARAM)text);
		while (re==0) {
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