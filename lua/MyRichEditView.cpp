#include "MyRichEditView.h"
#include <commctrl.h>
#include <fstream>
#pragma comment(lib,"comctl32.lib")
#define DEFAULTFORMAT(x) /*Ĭ��������ʽ���������*/\
x.cbSize = sizeof(x);\
x.dwMask = CFM_COLOR | CFM_FACE | CFM_SIZE;/*��ɫ�����塢�����С*/\
x.dwEffects = 0;\
x.yHeight = 9 * 20;/*12px�����С*/\
lstrcpyW(x.szFaceName, TEXT("΢���ź�"))
/*************************************************
Function:         |MyRichEditView
Description:      |�������ı��༭���������ʧ�ܣ�getHwnd()����0
Input:            |hwndParent �������ھ��
				   top        ����Ը�����
				   width      �����
				   L          ����Ҫ����������
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
	SendMessageW(hRichEdit, EM_SETBKGNDCOLOR, 0, RGB(0, 0, 55));//������ɫ����
	DEFAULTFORMAT(defaultFormat);
	defaultFormat.crTextColor = RGB(255, 255, 255);//Ĭ����ɫ�ǰ�ɫ
	SendMessageW(hRichEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&defaultFormat);//����ѡ�������ʽ
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
Description:      |���ø��ı��༭����ı�
Input:            |text ��δ��ʽ�ı�
				   len  ���ı�����
*************************************************/
void MyRichEditView::setText(const LPWSTR text, int len) {
	SendMessageW(hRichEdit, WM_SETTEXT, 0, NULL);//����ı�
	SendMessageW(hRichEdit, EM_SETCHARFORMAT, SCF_ALL, (LPARAM)&defaultFormat);//����ѡ�������ʽ
	CHARFORMATW cformat;
	DEFAULTFORMAT(cformat);//Ĭ����ʽ
	LPWSTR buffer = (LPWSTR)malloc(len * sizeof(WCHAR));//Ŀǰ������ת��Ϊ��ɫ�ı������ܳ���ԭ���ĳ���
	int bufferLen = 0;//�����������ж����ַ�
	int i = 0;//����ԭ�ı���ָ��λ��
	while (i < len && NULL != text[i++]) {//���ֽ�����ʽ��һ���ǳ�����������С��һ�����ַ�����NULL��β��
		if (TEXT('|') == text[i - 1]) {//���֮Դ
			if (i < len) {
				if (text[i] == TEXT('|')) {
					buffer[bufferLen++] = text[i++];// ���ַ�'|'���뵽������
					continue;
				}
				if (text[i] == TEXT('n') || text[i] == TEXT('N')) {//����
					buffer[bufferLen++] = TEXT('\r');//���ַ�'\r'���뵽������
					i++;//����n��N
					continue;
				}
				if (text[i] == TEXT('r') || text[i] == TEXT('R')) {//��ɫ����
					buffer[bufferLen] = NULL;//�û���������
					SendMessageW(hRichEdit, EM_REPLACESEL, false, (LPARAM)buffer);//���������ı�����
					bufferLen = 0;//��ջ�����
					SendMessageW(hRichEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&defaultFormat);//����ѡ�������ʽ
					i++;// ����r��R
					continue;
				}
			}
			if (i + 8 < len) {
				if ((text[i] == TEXT('c')) || (text[i] == TEXT('C'))) {//��ɫ��ʼ
					int A = T.Wchar2color(text[i + 1], text[i + 2]);//����͸���ȵ�������У��
					int R = T.Wchar2color(text[i + 3], text[i + 4]);//��ɫ
					int G = T.Wchar2color(text[i + 5], text[i + 6]);
					int B = T.Wchar2color(text[i + 7], text[i + 8]);
					if (A != -1 && R != -1 && G != -1 && B != -1) {//��ɫ��Ч
						buffer[bufferLen] = NULL;//�û���������
						SendMessageW(hRichEdit, EM_REPLACESEL, false, (LPARAM)buffer);//���������ı�����
						bufferLen = 0;//��ջ�����
						cformat.crTextColor = RGB(R, G, B);
						SendMessageW(hRichEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cformat);//����ѡ�������ʽ
						i += 9;// ����c��C��8λ����ɫֵ
						if (A != 255) {
							MessageBoxW(NULL, L->colorAlarm, L->alarm, MB_ICONWARNING);
						}
						continue;
					}
				}
			}
		}
		buffer[bufferLen++] = text[i - 1];//���ַ����뵽������
	}
	if (bufferLen != 0) {
		buffer[bufferLen] = NULL;//�û���������
		SendMessageW(hRichEdit, EM_REPLACESEL, 0, (LPARAM)buffer);//���������ı�����
	}
	free(buffer);
}
//�Ӹ��ı��༭�����ȡ����ʽ�ı�
int MyRichEditView::getText(LPWSTR text, int len, int* start, COLORREF* color) {
	if (text == NULL || len < 2) {//��ν��У��
		return -2;
	}
	GETTEXTLENGTHEX lengthstrust = { GTL_NUMCHARS, 1200 };//��ȡ�ı�����
	int allLen = SendMessageW(hRichEdit, EM_GETTEXTLENGTHEX, (WPARAM)&lengthstrust, (LPARAM)0);
	int textLen = 0;//text�Ѵ�����ַ�
	WCHAR buffer[5];//��֪��ΪʲôҪ��ô������5��С������
	while (*start < allLen) {
		CHARRANGE chooseScope{ *start, *start + 1 };
		SendMessageW(hRichEdit, EM_EXSETSEL, 0, (LPARAM)&chooseScope);//�ı�ѡ������
		SendMessageW(hRichEdit, EM_GETSELTEXT, 0, (LPARAM)buffer);//��ȡѡ���ı�
		int need = 2;//һ���ַ���NULL
		if (buffer[0] == '\r') {//\r���Ǹ��ı��༭����
			need++;
		}
		if (textLen + need > len) {
			text[textLen] = NULL;
			return 0;
		}
		CHARFORMATW cformat;
		cformat.cbSize = sizeof(CHARFORMATW);
		SendMessageW(hRichEdit, EM_GETCHARFORMAT, SCF_SELECTION, (LPARAM)&cformat);//��ȡѡ�������ʽ
		if (cformat.crTextColor != *color) {
			if (*color != 16777215) {//��һ����ɫ���ǰ�ɫ
				if (cformat.crTextColor == 16777215) {//���ڵ���ɫ�ǰ�ɫ
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
Description:      |��ȡ���ı��༭��ľ��
Return:           |����������ı��༭��ʧ�ܣ�����0
*************************************************/
HWND MyRichEditView::getHwnd() {
	return hRichEdit;
}