#include "MyRichEditView.h"
#include <commctrl.h>
#include <fstream>
#pragma comment(lib,"comctl32.lib")
#define DEFAULTFORMAT(x) /*默认字体样式在这里控制*/\
x.cbSize = sizeof(x);\
x.dwMask = CFM_COLOR | CFM_FACE | CFM_SIZE;/*颜色、字体、字体大小*/\
x.dwEffects = 0;\
x.yHeight = 9 * 20;/*12px字体大小*/\
lstrcpyW(x.szFaceName, TEXT("微软雅黑"))
/*************************************************
Function:         |MyRichEditView
Description:      |创建富文本编辑框，如果创建失败，getHwnd()返回0
Input:            |hwndParent ：父窗口句柄
				   top        ：相对父窗口
				   width      ：宽度
				   L          ：需要传递语言类
*************************************************/
MyRichEditView::MyRichEditView(HWND hwndParent, long left, long top, long width, long height, const Language* L) {
	this->L = L;
	InitCommonControls();
	hRichEdit = CreateWindowExW(0, RICHEDIT_CLASSW, TEXT(""),
		WS_BORDER | WS_CHILD | WS_VISIBLE | ES_MULTILINE | WS_VSCROLL /*| ES_AUTOVSCROLL*/ | WS_TABSTOP,
		left, top, width, height, hwndParent, NULL, GetModuleHandle(NULL), NULL);
	if (hRichEdit == NULL) {
		MessageBoxW(NULL, L->CreateRichEditViewerror, L->error, MB_ICONERROR);
		return;
	}
	//ShowScrollBar(hRichEdit, SB_VERT, true);
	SendMessageW(hRichEdit, EM_SETBKGNDCOLOR, 0, RGB(0, 0, 55));//背景颜色设置
	DEFAULTFORMAT(defaultFormat);
	defaultFormat.crTextColor = RGB(255, 255, 255);//默认颜色是白色
	SendMessageW(hRichEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&defaultFormat);//重置选择区域格式
}

bool MyRichEditView::SetColor(COLORREF color) {
	CHARFORMATW cformat;
	DEFAULTFORMAT(cformat);
	cformat.crTextColor = color;
	SendMessageW(hRichEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cformat);
	return false;
}
/*************************************************
Function:         |setText
Description:      |设置富文本编辑框的文本
Input:            |text ：未格式文本
				   len  ：文本长度
*************************************************/
void MyRichEditView::setText(const LPWSTR text, int len) {
	SendMessageW(hRichEdit, WM_SETTEXT, 0, NULL);//清空文本
	SendMessageW(hRichEdit, EM_SETCHARFORMAT, SCF_ALL, (LPARAM)&defaultFormat);//重置选择区域格式
	CHARFORMATW cformat;
	DEFAULTFORMAT(cformat);//默认样式
	LPWSTR buffer = (LPWSTR)malloc(len * sizeof(WCHAR));//目前来看，转化为彩色文本不可能超出原来的长度
	int bufferLen = 0;//缓冲区内容有多少字符
	int i = 0;//遍历原文本，指代位置
	while (i < len && NULL != text[i++]) {//两种结束方式，一种是超出缓冲区大小，一种是字符串以NULL结尾。
		if (TEXT('|') == text[i - 1]) {//万恶之源
			if (i < len) {
				if (text[i] == TEXT('|')) {
					buffer[bufferLen++] = text[i++];// 将字符'|'输入到缓冲区
					continue;
				}
				if (text[i] == TEXT('n') || text[i] == TEXT('N')) {//换行
					buffer[bufferLen++] = TEXT('\r');//将字符'\r'输入到缓冲区
					i++;//跳过n或N
					continue;
				}
				if (text[i] == TEXT('r') || text[i] == TEXT('R')) {//颜色结束
					buffer[bufferLen] = NULL;//让缓冲区结束
					SendMessageW(hRichEdit, EM_REPLACESEL, false, (LPARAM)buffer);//将缓冲区文本输入
					bufferLen = 0;//清空缓冲区
					SendMessageW(hRichEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&defaultFormat);//重置选择区域格式
					i++;// 跳过r或R
					continue;
				}
			}
			if (i + 8 < len) {
				if ((text[i] == TEXT('c')) || (text[i] == TEXT('C'))) {//颜色开始
					int A = T.Wchar2color(text[i + 1], text[i + 2]);//忽略透明度但不代表不校验
					int R = T.Wchar2color(text[i + 3], text[i + 4]);//颜色
					int G = T.Wchar2color(text[i + 5], text[i + 6]);
					int B = T.Wchar2color(text[i + 7], text[i + 8]);
					if (A != -1 && R != -1 && G != -1 && B != -1) {//颜色有效
						buffer[bufferLen] = NULL;//让缓冲区结束
						SendMessageW(hRichEdit, EM_REPLACESEL, false, (LPARAM)buffer);//将缓冲区文本输入
						bufferLen = 0;//清空缓冲区
						cformat.crTextColor = RGB(R, G, B);
						SendMessageW(hRichEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cformat);//设置选择区域格式
						i += 9;// 跳过c或C和8位的颜色值
						if (A != 255) {
							MessageBoxW(NULL, L->colorAlarm, L->alarm, MB_ICONWARNING);
						}
						continue;
					}
				}
			}
		}
		buffer[bufferLen++] = text[i - 1];//将字符输入到缓冲区
	}
	if (bufferLen != 0) {
		buffer[bufferLen] = NULL;//让缓冲区结束
		SendMessageW(hRichEdit, EM_REPLACESEL, 0, (LPARAM)buffer);//将缓冲区文本输入
	}
	free(buffer);
}
//从富文本编辑框里获取物编格式文本
int MyRichEditView::getText(LPWSTR text, int len, int* start, COLORREF* color) {
	if (text == NULL || len < 2) {//无谓的校验
		return -2;
	}
	GETTEXTLENGTHEX lengthstrust = { GTL_NUMCHARS, 1200 };//获取文本长度
	int allLen = SendMessageW(hRichEdit, EM_GETTEXTLENGTHEX, (WPARAM)&lengthstrust, (LPARAM)0);
	int textLen = 0;//text已存多少字符
	WCHAR buffer[5];//不知道为什么要这么保险用5大小。。。
	while (*start < allLen) {
		CHARRANGE chooseScope{ *start, *start + 1 };
		SendMessageW(hRichEdit, EM_EXSETSEL, 0, (LPARAM)&chooseScope);//改变选择区域
		SendMessageW(hRichEdit, EM_GETSELTEXT, 0, (LPARAM)buffer);//获取选择文本
		int need = 2;//一个字符加NULL
		if (buffer[0] == '\r') {//\r就是富文本编辑框换行
			need++;
		}
		if (textLen + need > len) {
			text[textLen] = NULL;
			return 0;
		}
		CHARFORMATW cformat;
		cformat.cbSize = sizeof(CHARFORMATW);
		SendMessageW(hRichEdit, EM_GETCHARFORMAT, SCF_SELECTION, (LPARAM)&cformat);//获取选择区域格式
		if (cformat.crTextColor != *color) {
			if (*color != 16777215) {//上一个颜色不是白色
				if (cformat.crTextColor == 16777215) {//现在的颜色是白色
					need += 2;//|r
					if (textLen + need > len) {
						text[textLen] = NULL;
						return 0;
					}
					lstrcpyW(text + textLen, TEXT("|r"));
					textLen += 2;
				} else {
					need += 12;//|r|cffaabbcc
					if (textLen + need > len) {
						text[textLen] = NULL;
						return 0;
					}
					lstrcpyW(text + textLen, TEXT("|r|cff"));
					T.color2hex(text + textLen + 6, cformat.crTextColor);
					textLen += 12;
				}
			} else {
				need += 10;//|cffaabbcc
				if (textLen + need > len) {
					text[textLen] = NULL;
					return 0;
				}
				lstrcpyW(text + textLen, TEXT("|cff"));
				T.color2hex(text + textLen + 4, cformat.crTextColor);
				textLen += 10;
			}
			*color = cformat.crTextColor;
		}
		if (buffer[0] == '\r') {
			text[textLen++] = '|';
			text[textLen++] = 'n';
		} else {
			text[textLen++] = buffer[0];
		}
		++*start;
	}
	text[textLen] = NULL;
	return -1;
}
/*************************************************
Function:         |getHwnd
Description:      |获取富文本编辑框的句柄
Return:           |如果创建富文本编辑框失败，返回0
*************************************************/
HWND MyRichEditView::getHwnd() {
	return hRichEdit;
}