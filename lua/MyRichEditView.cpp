//#include <regex>

#include "MyRichEditView.h"
MyRichEditView::MyRichEditView(HWND hwndParent, long top, long width, const Language* L)
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
		ES_MULTILINE | WS_VSCROLL | WS_HSCROLL | ES_AUTOVSCROLL | WS_TABSTOP,
		0, top, width, 100, hwndParent, NULL, GetModuleHandle(NULL), NULL);
	if (hRichEdit == NULL)
	{
		MessageBoxW(NULL, L->CreateRichEditViewerror, L->error, MB_ICONHAND);
		return;
	}
	//ShowWindow(hRichEdit, SW_SHOW);	 //���ش���	 

	//UpdateWindow(hRichEdit);	 //ˢ�´��ڿͻ���
	////��ȡѡ������
	//CHARRANGE d;
	//SendMessage(hRichEdit, EM_EXGETSEL, 0, (LPARAM)&d);
	//d.cpMax;
	//d.cpMin;
	////�滻ѡ���ı�
	//SendMessage(hRichEdit, EM_REPLACESEL, 0, (LPARAM)TEXT("����һ����������֪������������"));
	////�ı�ѡ������
	//CHARRANGE a;
	//a.cpMax = 9;
	//a.cpMin = 1;
	//SendMessage(hRichEdit, EM_EXSETSEL, 0, (LPARAM)&a);
	////����ѡ�������ʽ
	//CHARFORMATA cformat;
	//cformat.cbSize = sizeof(cformat);
	//cformat.dwMask = CFM_COLOR;
	//cformat.crTextColor = RGB(233, 33, 100);
	//SendMessageW(hRichEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cformat);
	//��ȡ�ı�����
	/*GETTEXTLENGTHEX lengthstrust={GTL_NUMCHARS,1200};
 SendMessage(hwndrich,EM_GETTEXTLENGTHEX,(WPARAM)&lengthstrust,(LPARAM)0);
EM_GETTEXTLENGTHEX ��Ϣ�����ڻ�ȡrichedit����е��ı����ȣ���Ϣ�����Ĳ���WPARAM��һ��GETTEXTLENGTHEX�ṹ���ͣ��ýṹ���������༭���ı��ĳ�����μ��㡣
typedef struct _gettextlengthex {
DWORD flags;
UINT  codepage;
} GETTEXTLENGTHEX;
Flags��ֵ������Ǹ���μ��㳤�ȡ���GTL_NUMCHARS��ʾ�����ַ���
Codepageͨ��������ֵ ANSI����ҳ CP_ACP ��Unicode 1200
�������ؼ���ĳ���ֵ*/
//��ȡѡ���ı�����
//WCHAR* buffer[1000];
//SendMessage(hRichEdit, EM_GETSELTEXT, 0, (LPARAM)buffer);
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

void MyRichEditView::setText(const LPWSTR text, int len)
{
	LPWSTR buffer = (LPWSTR)malloc(len);//Ŀǰ������ת��Ϊ��ɫ�ı������ܳ���ԭ���ĳ���
	int i = -1;
	int bufferLen = 0;
	WCHAR temp;
	GETTEXTLENGTHEX lengthstrust = { GTL_NUMCHARS, 1200 };
	CHARRANGE a{ 0, SendMessageW(hRichEdit, EM_GETTEXTLENGTHEX, (WPARAM)&lengthstrust, (LPARAM)0) /*��ȡ�ı�����*/ };
	SendMessageW(hRichEdit, EM_EXSETSEL, 0, (LPARAM)&a);//�ı�ѡ������														
	SendMessageW(hRichEdit, EM_REPLACESEL, 0, (LPARAM)TEXT(""));//���ѡ���ı�
	int selectMin = 0;//��ɫ�滻����ʼλ��
	int A;//�滻����ɫ����ɫΪ͸���ȣ�����
	int R;//�滻����ɫ
	int G;//�滻����ɫ
	int B;//�滻����ɫ
	while (i + 1 < len&&NULL != (temp = text[++i]))//���ֽ�����ʽ��һ���ǳ�����������С��һ�����ַ�����NULL��β��
	{
		if (TEXT('|') == temp) {
			if (i + 1 < len && text[i + 1] == TEXT('|'))// �ַ�'|'
			{
				buffer[bufferLen++] = TEXT('|');// ���ַ�'|'���뵽������
				i++;
				continue;
			}
			if (i + 1 < len && (text[i + 1] == TEXT('n') || text[i + 1] == TEXT('N')))// ����
			{
				buffer[bufferLen++] = TEXT('\n');// ���ַ�'\n'���뵽������
				i++;// ����n��N
				continue;
			}
			else if (((i + 9) < len) && T.nextNumIsValid(text + i, 10) && ((text[i + 1] == TEXT('c')) || (text[i + 1] == TEXT('C'))))// ��ɫ��ʼ
			{
				A = T.Wchar2color(text[i + 2], text[i + 3]);//����͸����
				R = T.Wchar2color(text[i + 4], text[i + 5]);//����͸����
				G = T.Wchar2color(text[i + 6], text[i + 7]);//����͸����
				B = T.Wchar2color(text[i + 8], text[i + 9]);//����͸����
				if (A != -1 && R != -1 && G != -1 && B != -1)
					//		string strColor = charArray[i + 2].ToString() + charArray[i + 3].ToString()// A
					//			+ charArray[i + 4].ToString() + charArray[i + 5].ToString()// R
					//			+ charArray[i + 6].ToString() + charArray[i + 7].ToString()// G
					//			+ charArray[i + 8].ToString() + charArray[i + 9].ToString()// B
					//			;
					//		if (IsColor(strColor) == true)// ����ת��Ϊ��ɫ
				{
					selectMin += bufferLen;
					buffer[bufferLen++] = NULL;//�û���������
					int selectEnd = SendMessageW(hRichEdit, EM_GETTEXTLENGTHEX, (WPARAM)&lengthstrust, (LPARAM)0);
					CHARRANGE a{ selectEnd, selectEnd };
					SendMessageW(hRichEdit, EM_EXSETSEL, 0, (LPARAM)&a);//�ı�ѡ������		
					SendMessageW(hRichEdit, EM_REPLACESEL, 0, (LPARAM)buffer);//���������ı�����
					//			txtPreviewClone.AppendText(buffer.ToString());// �������ַ��ͻ������
					bufferLen = 0;// ��ջ�����
		//			txtPreviewClone.SelectionColor = ConvertToColor(strColor);
					i += 9;// ����c��C��8λ����ɫֵ
					continue;
				}
			}
			else if (((i + 1) < len) && ((text[i + 1] == TEXT('r')) || (text[i + 1] == TEXT('R'))))// ��ɫ����
			{
				buffer[bufferLen] = NULL;//�û���������
				int selectEnd = SendMessageW(hRichEdit, EM_GETTEXTLENGTHEX, (WPARAM)&lengthstrust, (LPARAM)0);
				CHARRANGE a{ selectEnd, selectEnd };
				SendMessageW(hRichEdit, EM_EXSETSEL, 0, (LPARAM)&a);//�ı�ѡ������		
				SendMessageW(hRichEdit, EM_REPLACESEL, 0, (LPARAM)buffer);//���������ı�����
				CHARRANGE b{ selectMin, selectMin + bufferLen };
				//CHARRANGE b{ 1, 3 };
				SendMessageW(hRichEdit, EM_EXSETSEL, 0, (LPARAM)&b);//�ı�ѡ������		
				CHARFORMATA cformat;
				cformat.cbSize = sizeof(cformat);
				cformat.dwMask = CFM_COLOR;
				cformat.crTextColor = RGB(R, G, B);
				SendMessageW(hRichEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cformat);//TODO ����ѡ�������ʽ�������⣬��ʱ����
				bufferLen = 0;// ��ջ�����
				//		txtPreviewClone.AppendText(buffer.ToString());// �������ַ��ͻ������
		//		txtPreviewClone.SelectionColor = Color.White;
				i++;// ����r��R
				continue;
			}

		}
		buffer[bufferLen++] = temp;// ���ַ����뵽������
	}
	if (bufferLen!=0) {
		buffer[bufferLen ++] = NULL;//�û���������
		int selectEnd = SendMessageW(hRichEdit, EM_GETTEXTLENGTHEX, (WPARAM)&lengthstrust, (LPARAM)0);
		CHARRANGE a{ selectEnd, selectEnd };
		SendMessageW(hRichEdit, EM_EXSETSEL, 0, (LPARAM)&a);//�ı�ѡ������		
		SendMessageW(hRichEdit, EM_REPLACESEL, 0, (LPARAM)buffer);//���������ı�����
	}
	//public static void ConvertToPreviewTextBox(MyTextBox txtEdit, MyRichTextBox txtPreview)
	//{
	//	int cursorLocation = txtEdit.SelectionStart;
	//	txtEdit.Text = txtEdit.Text.Replace(Environment.NewLine, "|n");// ת���س�����Ϊ|n
	//	txtEdit.SelectionStart = cursorLocation;
	//	char[] charArray = txtEdit.Text.ToCharArray();// ��ԭ�����ַ���תΪ�ַ����鴦����ת���س�����Ϊ|n
	//	StringBuilder buffer = new StringBuilder();// ���ڻ��廹û������ַ�

	//	for (int i = 0; i < charArray.Length; i++)
	//	{
	//		if (charArray[i] == '|')// ת���ַ�
	//		{
	//			if ((i + 1) < charArray.Length && charArray[i + 1] == '|')// �ַ�'|'
	//			{
	//				buffer.Append('|');// ���ַ�'|'���뵽������
	//				i++;
	//				continue;
	//			}
	//			if (((i + 1) < charArray.Length) && ((charArray[i + 1] == 'n') || (charArray[i + 1] == 'N')))// ����
	//			{
	//				Color currentColor = txtPreviewClone.SelectionColor;// ���浱ǰ��ɫ
	//				txtPreviewClone.AppendText(buffer.ToString() + Environment.NewLine);// �������ַ��ͻ������
	//				buffer = new StringBuilder();// ��ջ�����
	//				txtPreviewClone.SelectionColor = currentColor;// �ָ���ɫ
	//				i++;// ����n��N
	//				continue;
	//			}
	//			else if (((i + 9) < charArray.Length) && ((charArray[i + 1] == 'c') || (charArray[i + 1] == 'C')))// ��ɫ��ʼ
	//			{
	//				string strColor = charArray[i + 2].ToString() + charArray[i + 3].ToString()// A
	//					+ charArray[i + 4].ToString() + charArray[i + 5].ToString()// R
	//					+ charArray[i + 6].ToString() + charArray[i + 7].ToString()// G
	//					+ charArray[i + 8].ToString() + charArray[i + 9].ToString()// B
	//					;
	//				if (IsColor(strColor) == true)// ����ת��Ϊ��ɫ
	//				{
	//					txtPreviewClone.AppendText(buffer.ToString());// �������ַ��ͻ������
	//					buffer = new StringBuilder();// ��ջ�����
	//					txtPreviewClone.SelectionColor = ConvertToColor(strColor);
	//					i += 9;// ����c��C��8λ����ɫֵ
	//					continue;
	//				}
	//			}
	//			else if (((i + 1) < charArray.Length) && ((charArray[i + 1] == 'r') || (charArray[i + 1] == 'R')))// ��ɫ����
	//			{
	//				txtPreviewClone.AppendText(buffer.ToString());// �������ַ��ͻ������
	//				buffer = new StringBuilder();// ��ջ�����
	//				txtPreviewClone.SelectionColor = Color.White;
	//				i++;// ����r��R
	//				continue;
	//			}
	//		}
	//		buffer.Append(charArray[i].ToString());// ���ַ����뵽������
	//	}
	//	txtPreviewClone.AppendText(buffer.ToString());// ��ʣ����ַ����

	//	txtPreview.Rtf = txtPreviewClone.Rtf;
	//	txtPreviewClone.Dispose();
	//	txtEdit.lockTextChange = false;
	//	txtPreview.lockTextChange = false;
	//}

	//public static void ConvertToEditTextBox(MyRichTextBox txtPreview, MyTextBox txtEdit)
	//{
	//	txtEdit.lockTextChange = true;

	//	#region ��¡�ؼ�
	//		MyRichTextBox txtPreviewClone = new MyRichTextBox()
	//	{
	//		Rtf = txtPreview.Rtf,
	//		SelectionStart = 0,// �ӿ�ͷ��ʼ����
	//		SelectionLength = 1,// ÿ�εĴ�����
	//		ignoreRefresh = true// ���Կؼ�������ػ棬�����Ӧ�ٶ�
	//	};
	//	#endregion

	//		bool isHighLight = false;// ��־�Ƿ������
	//	StringBuilder sb = new StringBuilder();// �洢�Ѿ�������ı�
	//	Color currentColor = txtPreviewClone.SelectionColor;// ��ǰ��ɫ

	//	#region �����һ���ַ�
	//		if (currentColor != Color.White)
	//		{
	//			sb.Append("|c" + ColorToHex(txtPreviewClone.SelectionColor));
	//			isHighLight = true;
	//		}
	//	#endregion

	//		int length = txtPreviewClone.TextLength;// ��������ı�����

	//	while (txtPreviewClone.SelectionStart < length)
	//	{
	//		if (txtPreviewClone.SelectionColor != currentColor)// �ı���ɫ
	//		{
	//			if (isHighLight)// ��������
	//			{
	//				sb.Append("|r");
	//				isHighLight = false;
	//			}
	//			if (txtPreviewClone.SelectionColor != Color.White)// ����Ĭ����ɫ����ʼ����
	//			{
	//				sb.Append("|c" + ColorToHex(txtPreviewClone.SelectionColor));
	//				isHighLight = true;
	//			}
	//			currentColor = txtPreviewClone.SelectionColor;
	//		}
	//		#region ���س�תΪ | n
	//			if (txtPreviewClone.SelectedText == "\n")
	//			{
	//				sb.Append("|n");
	//				txtPreviewClone.SelectionStart++;
	//				continue;
	//			}
	//		#endregion
	//			#region �� | תΪ ||
	//			else if (txtPreviewClone.SelectedText == "|")
	//		{
	//			sb.Append("||");
	//			txtPreviewClone.SelectionStart++;
	//			continue;
	//		}
	//		#endregion
	//			sb.Append(txtPreviewClone.SelectedText);
	//		txtPreviewClone.SelectionStart++;
	//	}
	//	if (isHighLight)
	//	{
	//		sb.Append("|r");
	//	}

	//	txtEdit.Text = sb.ToString();
	//	txtEdit.AddToUndoStack(sb.ToString());

	//	txtPreviewClone.Dispose();// ���ٿ�¡����
	//	txtEdit.lockTextChange = false;
	//}
	//private static int EncodingConvert(char char1, char char2)
	//{
	//	int a = 0, b = 0;
	//	if (char1 >= '0' && char1 <= '9')
	//	{
	//		a = char1 - '0';
	//	}
	//	else if (char1 >= 'a' && char1 <= 'f')
	//	{
	//		a = char1 - 'a' + 10;
	//	}
	//	if (char2 >= '0' && char2 <= '9')
	//	{
	//		b = char2 - '0';
	//	}
	//	else if (char2 >= 'a' && char2 <= 'f')
	//	{
	//		b = char2 - 'a' + 10;
	//	}
	//	return a * 16 + b;
	//}

	//public static void SetTxtEditSingleColor(MyTextBox txtEdit, Color color)
	//{
	//	txtEdit.lockTextChange = true;
	//	txtEdit.SelectedText = "|c" + ColorToHex(color) + txtEdit.SelectedText + "|r";
	//	txtEdit.lockTextChange = false;
	//	txtEdit.Select();// ����ؼ�
	//}

	//public static void SetTxtPreviewSingleColor(MyRichTextBox txtPreview, Color color)
	//{
	//	txtPreview.lockTextChange = true;
	//	int cursorLocation = txtPreview.SelectionStart;// ����༭λ��
	//	int selectLength = txtPreview.SelectionLength;// ���洦���ַ����ĳ���
	//	txtPreview.SelectionColor = color;// ������ɫ
	//	txtPreview.SelectionStart = cursorLocation + selectLength;// �ƶ����
	//	txtPreview.SelectionLength = 0;// ���ѡ��
	//	txtPreview.lockTextChange = false;
	//	txtPreview.Select();// ����ؼ�
	//}

	//public static void SetTxtEditGradual(MyTextBox txtEdit, Color startColor, Color endColor)
	//{
	//	int processLength = 0;// ȥ�������ַ�����ַ�����
	//	string selectedText = txtEdit.SelectedText;// ѡ����ı�
	//	for (int i = 0; i < selectedText.Length; i++)
	//	{
	//		if (i + 1 < selectedText.Length && selectedText[i] == '|' && selectedText[i + 1] == '|')
	//		{
	//			processLength++;
	//			i++;
	//			continue;
	//		}
	//		if (i + 1 < selectedText.Length && selectedText[i] == '|' && selectedText[i + 1] == 'n')
	//		{
	//			i++;
	//			continue;
	//		}
	//		if (i + 1 < selectedText.Length && selectedText[i] == '|' && selectedText[i + 1] == 'r')
	//		{
	//			i++;
	//			continue;
	//		}
	//		if (i + 1 < selectedText.Length && selectedText[i] == '|' && selectedText[i + 1] == 'c')
	//		{
	//			if (i + 9 < selectedText.Length)
	//			{
	//				string strColor = selectedText[i + 2].ToString() + selectedText[i + 3].ToString()// A
	//					+ selectedText[i + 4].ToString() + selectedText[i + 5].ToString()// R
	//					+ selectedText[i + 6].ToString() + selectedText[i + 7].ToString()// G
	//					+ selectedText[i + 8].ToString() + selectedText[i + 9].ToString()// B
	//					;
	//				if (IsColor(strColor) == true)
	//				{
	//					i += 9;
	//					continue;
	//				}
	//			}
	//		}
	//		processLength++;
	//	}
	//	if (processLength > 1)
	//	{
	//		txtEdit.lockTextChange = true;
	//		int j = 0;
	//		for (int i = 0; i < selectedText.Length; i++)
	//		{
	//			int r, g, b;
	//			Color tempColor;
	//			if (i + 1 < selectedText.Length && selectedText[i] == '|' && selectedText[i + 1] == '|')
	//			{
	//				r = startColor.R + (endColor.R - startColor.R) * j / (processLength - 1);
	//				g = startColor.G + (endColor.G - startColor.G) * j / (processLength - 1);
	//				b = startColor.B + (endColor.B - startColor.B) * j / (processLength - 1);
	//				tempColor = Color.FromArgb(r, g, b);
	//				j++;

	//				txtEdit.SelectionLength = 0;
	//				txtEdit.SelectedText = "|c" + ColorToHex(tempColor);
	//				txtEdit.SelectionStart += 2;
	//				txtEdit.SelectedText = "|r";
	//				i++;
	//				continue;
	//			}
	//			if (i + 1 < selectedText.Length && selectedText[i] == '|' && selectedText[i + 1] == 'n')
	//			{
	//				txtEdit.SelectionStart += 2;
	//				i++;
	//				continue;
	//			}
	//			if (i + 1 < selectedText.Length && selectedText[i] == '|' && selectedText[i + 1] == 'r')
	//			{
	//				txtEdit.SelectionStart += 2;
	//				i++;
	//				continue;
	//			}
	//			if (i + 1 < selectedText.Length && selectedText[i] == '|' && selectedText[i + 1] == 'c')
	//			{
	//				if (i + 9 < selectedText.Length)
	//				{
	//					string strColor = selectedText[i + 2].ToString() + selectedText[i + 3].ToString()// A
	//						+ selectedText[i + 4].ToString() + selectedText[i + 5].ToString()// R
	//						+ selectedText[i + 6].ToString() + selectedText[i + 7].ToString()// G
	//						+ selectedText[i + 8].ToString() + selectedText[i + 9].ToString()// B
	//						;
	//					if (IsColor(strColor) == true)
	//					{
	//						txtEdit.SelectionStart += 9;
	//						i += 9;
	//						continue;
	//					}
	//				}
	//			}
	//			r = startColor.R + (endColor.R - startColor.R) * j / (processLength - 1);
	//			g = startColor.G + (endColor.G - startColor.G) * j / (processLength - 1);
	//			b = startColor.B + (endColor.B - startColor.B) * j / (processLength - 1);
	//			tempColor = Color.FromArgb(r, g, b);
	//			j++;

	//			txtEdit.SelectionLength = 0;
	//			txtEdit.SelectedText = "|c" + ColorToHex(tempColor);
	//			txtEdit.SelectionStart++;
	//			txtEdit.SelectedText = "|r";
	//		}
	//		txtEdit.lockTextChange = false;
	//		txtEdit.Select();// ����ؼ�
	//	}
	//	else
	//	{
	//		SetTxtEditSingleColor(txtEdit, startColor);
	//	}

	//	//int selectLength = txtEdit.SelectionLength;// ��Ҫ����ĳ���
	//	//if (selectLength > 1)
	//	//{
	//	//    txtEdit.lockTextChange = true;
	//	//    for (int i = 0; i < selectLength; i++)
	//	//    {
	//	//        Color tempColor = Color.FromArgb(startColor.R + (endColor.R - startColor.R) * i / (selectLength - 1), startColor.G + (endColor.G - startColor.G) * i / (selectLength - 1), startColor.B + (endColor.B - startColor.B) * i / (selectLength - 1));// ���㵱ǰ�ֵ���ɫ
	//	//        txtEdit.SelectionLength = 0;
	//	//        txtEdit.SelectedText = "|c" + ColorToHex(tempColor);
	//	//        txtEdit.SelectionStart++;
	//	//        txtEdit.SelectedText = "|r";
	//	//        txtEdit.Select();// ����ؼ�
	//	//    }
	//	//    txtEdit.lockTextChange = false;
	//	//}
	//	//else
	//	//{
	//	//    SetTxtEditSingleColor(txtEdit, startColor);
	//	//}
	//}

	//public static void SetTxtPreviewGradual(MyRichTextBox txtPreview, Color startColor, Color endColor)
	//{
	//	int selectLength = txtPreview.SelectionLength;// ��Ҫ����ĳ���
	//	if (selectLength > 1)
	//	{
	//		txtPreview.lockTextChange = true;
	//		for (int i = 0; i < selectLength; i++)
	//		{
	//			txtPreview.SelectionLength = 1;
	//			Color tempColor = Color.FromArgb(startColor.R + (endColor.R - startColor.R) * i / (selectLength - 1), startColor.G + (endColor.G - startColor.G) * i / (selectLength - 1), startColor.B + (endColor.B - startColor.B) * i / (selectLength - 1));// ���㵱ǰ�ֵ���ɫ
	//			txtPreview.SelectionColor = tempColor;
	//			txtPreview.SelectionLength = 0;
	//			txtPreview.SelectionStart++;
	//		}
	//		txtPreview.lockTextChange = false;
	//		txtPreview.Select();// ����ؼ�
	//	}
	//	else
	//	{
	//		SetTxtPreviewSingleColor(txtPreview, startColor);
	//	}
	//}

	///// <summary>
	///// �ж�һ���ַ����Ƿ����ת��Ϊ��ɫ
	///// </summary>
	///// <param name="strColor"></param>
	///// <returns></returns>
	//private static bool IsColor(string strColor)
	//{
	//	foreach(var ch in strColor)
	//	{
	//		if (((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F')) == false)
	//		{
	//			return false;
	//		}
	//	}
	//	return true;
	//}

	///// <summary>
	///// ���ַ���ת��Ϊ��ɫ
	///// </summary>
	///// <param name="strColor"></param>
	///// <returns></returns>
	//private static Color ConvertToColor(string strColor)
	//{
	//	string strA = strColor.Substring(0, 2);// A
	//	string strR = strColor.Substring(2, 2);// R
	//	string strG = strColor.Substring(4, 2);// G
	//	string strB = strColor.Substring(6, 2);// B
	//	int colorA = Convert.ToInt32(strA, 16);// ��16����ת��Ϊ10����
	//	int colorR = Convert.ToInt32(strR, 16);
	//	int colorG = Convert.ToInt32(strG, 16);
	//	int colorB = Convert.ToInt32(strB, 16);
	//	return Color.FromArgb(colorR, colorG, colorB);// ����War3��A�ò���
	//}

	///// <summary>
	///// ����ɫת��Ϊ16�����ַ���
	///// </summary>
	///// <param name="color"></param>
	///// <returns></returns>
	//public static string ColorToHex(Color color)
	//{
	//	string strA = color.A.ToString("x").PadLeft(2, '0');// ת��Ϊ16���Ʋ���ǰ�油��0ʹ����Ϊ2
	//	string strR = color.R.ToString("x").PadLeft(2, '0');
	//	string strG = color.G.ToString("x").PadLeft(2, '0');
	//	string strB = color.B.ToString("x").PadLeft(2, '0');
	//	return strA + strR + strG + strB;
	//}
}

HWND MyRichEditView::getHwnd()
{
	return hRichEdit;
}
