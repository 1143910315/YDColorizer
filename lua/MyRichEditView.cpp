#include "MyRichEditView.h"
#include <commctrl.h>
#pragma comment(lib,"comctl32.lib")
/*************************************************
Function:         |MyRichEditView
Description:      |�������ı��༭���������ʧ�ܣ�getHwnd()����0
Input:            |hwndParent �������ھ��
				   top        ����Ը�����
				   width      �����
				   L          ����Ҫ����������
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
	SendMessageW(hRichEdit, EM_SETBKGNDCOLOR, 0, RGB(0, 0, 55));//������ɫ����
	defaultFormat.cbSize = sizeof(defaultFormat);
	defaultFormat.dwMask = CFM_COLOR | CFM_FACE | CFM_SIZE;//��ɫ�����塢�����С
	defaultFormat.crTextColor = RGB(255, 255, 255);//Ĭ����ɫ�ǰ�ɫ
	defaultFormat.dwEffects = 0;
	defaultFormat.yHeight = 9 * 20;//12px�����С
	lstrcpyW(defaultFormat.szFaceName, TEXT("΢���ź�"));
	SendMessageW(hRichEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&defaultFormat);//����ѡ�������ʽ
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
Description:      |���ø��ı��༭����ı�
Input:            |text ��δ��ʽ�ı�
				   len  ���ı�����
*************************************************/
void MyRichEditView::setText(const LPWSTR text, int len) {
	GETTEXTLENGTHEX lengthstrust = { GTL_NUMCHARS, 1200 };//��ȡ�ı�����
	CHARRANGE chooseScope{ 0, SendMessageW(hRichEdit, EM_GETTEXTLENGTHEX, (WPARAM)&lengthstrust, (LPARAM)0) };
	SendMessageW(hRichEdit, EM_EXSETSEL, 0, (LPARAM)&chooseScope);//�ı�ѡ������
	SendMessageW(hRichEdit, EM_REPLACESEL, 0, (LPARAM)TEXT(""));//���ѡ���ı�
	CHARFORMATW cformat;
	cformat.cbSize = sizeof(cformat);
	cformat.dwMask = CFM_COLOR | CFM_FACE | CFM_SIZE;
	cformat.crTextColor = RGB(255, 255, 255);
	cformat.dwEffects = 0;
	cformat.yHeight = 9 * 20;
	lstrcpyW(cformat.szFaceName, TEXT("΢���ź�"));
	SendMessageW(hRichEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&defaultFormat);//����ѡ�������ʽ
	int selectMin = 0;//��ɫ�滻����ʼλ��
	int selectEnd;//��������ѡ������
	int A;//�滻����ɫ����ɫΪ͸���ȣ�����
	int R;//�滻����ɫ
	int G;//�滻����ɫ
	int B;//�滻����ɫ
	int i = 0;//����ԭ�ı���ָ��λ��
	LPWSTR buffer = (LPWSTR)malloc(len);//Ŀǰ������ת��Ϊ��ɫ�ı������ܳ���ԭ���ĳ���
	int bufferLen = 0;//�����������ж����ַ�
	WCHAR temp;//��ʱ�����ַ���Ӧ���򻯴˱���
	while (i < len&&NULL != (temp = text[i++]))//���ֽ�����ʽ��һ���ǳ�����������С��һ�����ַ�����NULL��β��
	{
		if (TEXT('|') == temp) {
			if (i < len && text[i] == TEXT('|')) {// �ַ�'|'
				buffer[bufferLen++] = TEXT('|');// ���ַ�'|'���뵽������
				i++;
				continue;
			}
			if (i < len && (text[i] == TEXT('n') || text[i] == TEXT('N'))) {// ����
				buffer[bufferLen++] = TEXT('\n');// ���ַ�'\n'���뵽������
				i++;// ����n��N
				continue;
			} else if (((i + 8) < len) && T.nextNumIsValid(text + i, 9) && ((text[i] == TEXT('c')) || (text[i] == TEXT('C')))) {// ��ɫ��ʼ
				A = T.Wchar2color(text[i + 1], text[i + 2]);//����͸����
				R = T.Wchar2color(text[i + 3], text[i + 4]);
				G = T.Wchar2color(text[i + 5], text[i + 6]);
				B = T.Wchar2color(text[i + 7], text[i + 8]);
				if (A != -1 && R != -1 && G != -1 && B != -1) {
					selectMin += bufferLen;
					buffer[bufferLen] = NULL;//�û���������
					SendMessageW(hRichEdit, EM_REPLACESEL, 0, (LPARAM)buffer);//���������ı�����
					bufferLen = 0;// ��ջ�����
					i += 9;// ����c��C��8λ����ɫֵ
					continue;
				}
			} else if ((i < len) && ((text[i] == TEXT('r')) || (text[i] == TEXT('R'))))// ��ɫ����
			{
				buffer[bufferLen] = NULL;//�û���������
				SendMessageW(hRichEdit, EM_REPLACESEL, 0, (LPARAM)buffer);//���������ı�����
				chooseScope.cpMin = selectMin;
				chooseScope.cpMax = selectMin + bufferLen;//��ɫ����
				SendMessageW(hRichEdit, EM_EXSETSEL, 0, (LPARAM)&chooseScope);//�ı�ѡ������		
				cformat.crTextColor = RGB(R, G, B);
				SendMessageW(hRichEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cformat);//����ѡ�������ʽ
				selectEnd = SendMessageW(hRichEdit, EM_GETTEXTLENGTHEX, (WPARAM)&lengthstrust, (LPARAM)0);
				chooseScope.cpMin = chooseScope.cpMax = selectEnd;
				SendMessageW(hRichEdit, EM_EXSETSEL, 0, (LPARAM)&chooseScope);//����ѡ������
				SendMessageW(hRichEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&defaultFormat);//����ѡ�������ʽ
				selectMin += bufferLen;//��ʼѡ��λ��������
				bufferLen = 0;// ��ջ�����
				i++;// ����r��R
				continue;
			}
		}
		buffer[bufferLen++] = temp;// ���ַ����뵽������
	}
	if (bufferLen != 0) {
		buffer[bufferLen] = NULL;//�û���������	
		SendMessageW(hRichEdit, EM_REPLACESEL, 0, (LPARAM)buffer);//���������ı�����
	}
}
/*************************************************
Function:         |getHwnd
Description:      |��ȡ���ı��༭��ľ��
Return:           |����������ı��༭��ʧ�ܣ�����0
*************************************************/
HWND MyRichEditView::getHwnd() {
	return hRichEdit;
}