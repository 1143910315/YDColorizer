#include "MyRichEditView.h"
#include <commctrl.h>
#pragma comment(lib,"comctl32.lib")
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
	HINSTANCE hinstrich = LoadLibraryW(TEXT("RichEd20.Dll"));
	if (!hinstrich) {
		MessageBoxW(NULL, L->lessDLL, L->error, MB_ICONERROR);
		return;
	}
	hRichEdit = CreateWindowExW(0, RICHEDIT_CLASSW, TEXT(""),
		WS_BORDER | WS_CHILD | WS_VISIBLE | ES_MULTILINE | WS_VSCROLL | WS_HSCROLL | ES_AUTOVSCROLL | WS_TABSTOP,
		5, top, width, 100, hwndParent, NULL, GetModuleHandle(NULL), NULL);
	if (hRichEdit == NULL) {
		MessageBoxW(NULL, L->CreateRichEditViewerror, L->error, MB_ICONERROR);
		return;
	}
	SendMessageW(hRichEdit, EM_SETBKGNDCOLOR, 0, RGB(0, 0, 55));//背景颜色设置
	defaultFormat.cbSize = sizeof(defaultFormat);
	defaultFormat.dwMask = CFM_COLOR | CFM_FACE | CFM_SIZE;//颜色、字体、字体大小
	defaultFormat.crTextColor = RGB(255, 255, 255);//默认颜色是白色
	defaultFormat.dwEffects = 0;
	defaultFormat.yHeight = 9 * 20;//12px字体大小
	lstrcpyW(defaultFormat.szFaceName, TEXT("微软雅黑"));
	SendMessageW(hRichEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&defaultFormat);//重置选择区域格式
}

bool MyRichEditView::SetColor() {
	CHARFORMATW cformat;
	cformat.cbSize = sizeof(cformat);
	cformat.dwMask = CFM_COLOR;
	cformat.crTextColor = RGB(0, 0, 0);
	SendMessage(hRichEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cformat);
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
	cformat.cbSize = sizeof(cformat);
	cformat.dwMask = CFM_COLOR | CFM_FACE | CFM_SIZE;
	cformat.crTextColor = RGB(255, 255, 255);
	cformat.dwEffects = 0;
	cformat.yHeight = 9 * 20;
	lstrcpyW(cformat.szFaceName, TEXT("微软雅黑"));
	SendMessageW(hRichEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&defaultFormat);//重置选择区域格式
	int selectMin = 0;//颜色替换的起始位置
	int selectEnd;//用于重置选择区域
	int A;//替换的颜色，此色为透明度，忽略
	int R;//替换的颜色
	int G;//替换的颜色
	int B;//替换的颜色
	int i = 0;//遍历原文本，指代位置
	LPWSTR buffer = (LPWSTR)malloc(len);//目前来看，转化为彩色文本不可能超出原来的长度
	int bufferLen = 0;//缓冲区内容有多少字符
	WCHAR temp;//临时储存字符，应当简化此变量
	while (i < len&&NULL != (temp = text[i++]))//两种结束方式，一种是超出缓冲区大小，一种是字符串以NULL结尾。
	{
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
				A = T.Wchar2color(text[i + 1], text[i + 2]);//忽略透明度
				R = T.Wchar2color(text[i + 3], text[i + 4]);
				G = T.Wchar2color(text[i + 5], text[i + 6]);
				B = T.Wchar2color(text[i + 7], text[i + 8]);
				if (A != -1 && R != -1 && G != -1 && B != -1) {
					selectMin += bufferLen;
					buffer[bufferLen] = NULL;//让缓冲区结束
					SendMessageW(hRichEdit, EM_REPLACESEL, 0, (LPARAM)buffer);//将缓冲区文本输入
					bufferLen = 0;// 清空缓冲区
					i += 9;// 跳过c或C和8位的颜色值
					continue;
				}
			} else if ((i < len) && ((text[i] == TEXT('r')) || (text[i] == TEXT('R'))))// 颜色结束
			{
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
				i++;// 跳过r或R
				continue;
			}
		}
		buffer[bufferLen++] = temp;// 将字符输入到缓冲区
	}
	if (bufferLen != 0) {
		buffer[bufferLen] = NULL;//让缓冲区结束	
		SendMessageW(hRichEdit, EM_REPLACESEL, 0, (LPARAM)buffer);//将缓冲区文本输入
	}
}
/*************************************************
Function:         |getHwnd
Description:      |获取富文本编辑框的句柄
Return:           |如果创建富文本编辑框失败，返回0
*************************************************/
HWND MyRichEditView::getHwnd() {
	return hRichEdit;
}