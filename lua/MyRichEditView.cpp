#include "MyRichEditView.h"
#include <commctrl.h>
#pragma comment(lib,"comctl32.lib")
#define DEFAULTFORMAT(x) \
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
MyRichEditView::MyRichEditView(HWND hwndParent, long top, long width, const Language* L) {
	InitCommonControls();
	hRichEdit = CreateWindowExW(0, RICHEDIT_CLASSW, TEXT(""),
		WS_BORDER | WS_CHILD | WS_VISIBLE | ES_MULTILINE | WS_VSCROLL | WS_TABSTOP,
		5, top, width, 100, hwndParent, NULL, GetModuleHandle(NULL), NULL);
	if (hRichEdit == NULL) {
		MessageBoxW(NULL, L->CreateRichEditViewerror, L->error, MB_ICONERROR);
		return;
	}
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
	GETTEXTLENGTHEX lengthstrust = { GTL_NUMCHARS, 1200 };//获取文本长度
	CHARRANGE chooseScope{ 0, SendMessageW(hRichEdit, EM_GETTEXTLENGTHEX, (WPARAM)&lengthstrust, (LPARAM)0) };
	SendMessageW(hRichEdit, EM_EXSETSEL, 0, (LPARAM)&chooseScope);//改变选择区域
	SendMessageW(hRichEdit, EM_REPLACESEL, 0, (LPARAM)TEXT(""));//清空选择文本
	CHARFORMATW cformat;
	DEFAULTFORMAT(cformat);
	SendMessageW(hRichEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&defaultFormat);//重置选择区域格式
	int selectMin = 0;//颜色替换的起始位置
	int selectEnd;//用于重置选择区域
	int A = -1;//替换的颜色，此色为透明度，-1代表无储存颜色
	int R;//替换的颜色
	int G;//替换的颜色
	int B;//替换的颜色
	int i = 0;//遍历原文本，指代位置
	LPWSTR buffer = (LPWSTR)malloc(len * sizeof(WCHAR));//目前来看，转化为彩色文本不可能超出原来的长度
	int bufferLen = 0;//缓冲区内容有多少字符
	WCHAR temp;//临时储存字符，应当简化此变量
	while (i < len&&NULL != (temp = text[i++])) {//两种结束方式，一种是超出缓冲区大小，一种是字符串以NULL结尾。
		if (TEXT('|') == temp) {
			if (i < len && text[i] == TEXT('|')) {// 字符'|'
				buffer[bufferLen++] = TEXT('|');// 将字符'|'输入到缓冲区
				i++;
				continue;
			}
			if (i < len && (text[i] == TEXT('n') || text[i] == TEXT('N'))) {// 换行
				buffer[bufferLen++] = TEXT('\n');// 将字符'\n'输入到缓冲区
				i++;// 跳过n或N
				continue;
			} else if (((i + 8) < len) && T.nextNumIsValid(text + i, 9) && ((text[i] == TEXT('c')) || (text[i] == TEXT('C')))) {// 颜色开始
				if (A != -1) {//上一次的颜色代码没有|r结束
					A = 257;//通过判断这个再跳回来
					goto color;
				}
			newcolor:
				int Ac = T.Wchar2color(text[i + 1], text[i + 2]);//忽略透明度
				int Rc = T.Wchar2color(text[i + 3], text[i + 4]);
				int Gc = T.Wchar2color(text[i + 5], text[i + 6]);
				int Bc = T.Wchar2color(text[i + 7], text[i + 8]);
				if (Ac != -1 && Rc != -1 && Gc != -1 && Bc != -1) {
					A = Ac;
					R = Rc;
					G = Gc;
					B = Bc;
					selectMin += bufferLen;
					buffer[bufferLen] = NULL;//让缓冲区结束
					SendMessageW(hRichEdit, EM_REPLACESEL, 0, (LPARAM)buffer);//将缓冲区文本输入
					bufferLen = 0;// 清空缓冲区
					i += 9;// 跳过c或C和8位的颜色值
					continue;
				}
			} else if ((i < len) && ((text[i] == TEXT('r')) || (text[i] == TEXT('R')))) {//颜色结束
				if (A != -1) {
				color:
					buffer[bufferLen] = NULL;//让缓冲区结束
					SendMessageW(hRichEdit, EM_REPLACESEL, 0, (LPARAM)buffer);//将缓冲区文本输入
					chooseScope.cpMin = selectMin;
					chooseScope.cpMax = selectMin + bufferLen;//变色区间
					SendMessageW(hRichEdit, EM_EXSETSEL, 0, (LPARAM)&chooseScope);//改变选择区域		
					cformat.crTextColor = RGB(R, G, B);
					SendMessageW(hRichEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cformat);//设置选择区域格式
					selectEnd = SendMessageW(hRichEdit, EM_GETTEXTLENGTHEX, (WPARAM)&lengthstrust, (LPARAM)0);
					chooseScope.cpMin = chooseScope.cpMax = selectEnd;
					SendMessageW(hRichEdit, EM_EXSETSEL, 0, (LPARAM)&chooseScope);//重置选择区域
					SendMessageW(hRichEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&defaultFormat);//重置选择区域格式
					selectMin += bufferLen;//起始选择位置往后移
					bufferLen = 0;// 清空缓冲区
					if (A == 257) {
						goto newcolor;
					}
					A = -1;//清除保存的颜色
				}
				i++;// 跳过r或R
				continue;
			}
		}
		buffer[bufferLen++] = temp;//将字符输入到缓冲区
	}
	if (bufferLen != 0) {
		buffer[bufferLen] = NULL;//让缓冲区结束	
		SendMessageW(hRichEdit, EM_REPLACESEL, 0, (LPARAM)buffer);//将缓冲区文本输入
	}
	free(buffer);
}
/*************************************************
Function:         |getHwnd
Description:      |获取富文本编辑框的句柄
Return:           |如果创建富文本编辑框失败，返回0
*************************************************/
HWND MyRichEditView::getHwnd() {
	return hRichEdit;
}