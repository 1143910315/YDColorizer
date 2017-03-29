#pragma once
#include "Language.h"
#include "MyRichEditView.h"
#include <Windows.h>
class WinControl {
public:
	WinControl(HWND hwnd, int width, int height, const Language* L, HWND textHWND);
	void click_But(WORD hwnd_but);
	HWND RichEditHWND();
	MyRichEditView* RichEditView();
	~WinControl();
private:
	MyRichEditView* RichEdit;
	HWND textHWND;
	int top;
};