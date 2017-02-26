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
	//ShowWindow(hRichEdit, SW_SHOW);	 //隐藏窗口	 

	//UpdateWindow(hRichEdit);	 //刷新窗口客户区
	////获取选择区域
	//CHARRANGE d;
	//SendMessage(hRichEdit, EM_EXGETSEL, 0, (LPARAM)&d);
	//d.cpMax;
	//d.cpMin;
	////替换选择文本
	//SendMessage(hRichEdit, EM_REPLACESEL, 0, (LPARAM)TEXT("我有一句妈卖批不知当讲不当讲！"));
	////改变选择区域
	//CHARRANGE a;
	//a.cpMax = 9;
	//a.cpMin = 1;
	//SendMessage(hRichEdit, EM_EXSETSEL, 0, (LPARAM)&a);
	////设置选择区域格式
	//CHARFORMATA cformat;
	//cformat.cbSize = sizeof(cformat);
	//cformat.dwMask = CFM_COLOR;
	//cformat.crTextColor = RGB(233, 33, 100);
	//SendMessageW(hRichEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cformat);
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
	LPWSTR buffer = (LPWSTR)malloc(len);//目前来看，转化为彩色文本不可能超出原来的长度
	int i = -1;
	int bufferLen = 0;
	WCHAR temp;
	GETTEXTLENGTHEX lengthstrust = { GTL_NUMCHARS, 1200 };
	CHARRANGE a{ 0, SendMessageW(hRichEdit, EM_GETTEXTLENGTHEX, (WPARAM)&lengthstrust, (LPARAM)0) /*获取文本长度*/ };
	SendMessageW(hRichEdit, EM_EXSETSEL, 0, (LPARAM)&a);//改变选择区域														
	SendMessageW(hRichEdit, EM_REPLACESEL, 0, (LPARAM)TEXT(""));//清空选择文本
	int selectMin = 0;//颜色替换的起始位置
	int A;//替换的颜色，此色为透明度，忽略
	int R;//替换的颜色
	int G;//替换的颜色
	int B;//替换的颜色
	while (i + 1 < len&&NULL != (temp = text[++i]))//两种结束方式，一种是超出缓冲区大小，一种是字符串以NULL结尾。
	{
		if (TEXT('|') == temp) {
			if (i + 1 < len && text[i + 1] == TEXT('|'))// 字符'|'
			{
				buffer[bufferLen++] = TEXT('|');// 将字符'|'输入到缓冲区
				i++;
				continue;
			}
			if (i + 1 < len && (text[i + 1] == TEXT('n') || text[i + 1] == TEXT('N')))// 换行
			{
				buffer[bufferLen++] = TEXT('\n');// 将字符'\n'输入到缓冲区
				i++;// 跳过n或N
				continue;
			}
			else if (((i + 9) < len) && T.nextNumIsValid(text + i, 10) && ((text[i + 1] == TEXT('c')) || (text[i + 1] == TEXT('C'))))// 颜色开始
			{
				A = T.Wchar2color(text[i + 2], text[i + 3]);//忽略透明度
				R = T.Wchar2color(text[i + 4], text[i + 5]);//忽略透明度
				G = T.Wchar2color(text[i + 6], text[i + 7]);//忽略透明度
				B = T.Wchar2color(text[i + 8], text[i + 9]);//忽略透明度
				if (A != -1 && R != -1 && G != -1 && B != -1)
					//		string strColor = charArray[i + 2].ToString() + charArray[i + 3].ToString()// A
					//			+ charArray[i + 4].ToString() + charArray[i + 5].ToString()// R
					//			+ charArray[i + 6].ToString() + charArray[i + 7].ToString()// G
					//			+ charArray[i + 8].ToString() + charArray[i + 9].ToString()// B
					//			;
					//		if (IsColor(strColor) == true)// 可以转化为颜色
				{
					selectMin += bufferLen;
					buffer[bufferLen++] = NULL;//让缓冲区结束
					int selectEnd = SendMessageW(hRichEdit, EM_GETTEXTLENGTHEX, (WPARAM)&lengthstrust, (LPARAM)0);
					CHARRANGE a{ selectEnd, selectEnd };
					SendMessageW(hRichEdit, EM_EXSETSEL, 0, (LPARAM)&a);//改变选择区域		
					SendMessageW(hRichEdit, EM_REPLACESEL, 0, (LPARAM)buffer);//将缓冲区文本输入
					//			txtPreviewClone.AppendText(buffer.ToString());// 将缓冲字符和换行输出
					bufferLen = 0;// 清空缓冲区
		//			txtPreviewClone.SelectionColor = ConvertToColor(strColor);
					i += 9;// 跳过c或C和8位的颜色值
					continue;
				}
			}
			else if (((i + 1) < len) && ((text[i + 1] == TEXT('r')) || (text[i + 1] == TEXT('R'))))// 颜色结束
			{
				buffer[bufferLen] = NULL;//让缓冲区结束
				int selectEnd = SendMessageW(hRichEdit, EM_GETTEXTLENGTHEX, (WPARAM)&lengthstrust, (LPARAM)0);
				CHARRANGE a{ selectEnd, selectEnd };
				SendMessageW(hRichEdit, EM_EXSETSEL, 0, (LPARAM)&a);//改变选择区域		
				SendMessageW(hRichEdit, EM_REPLACESEL, 0, (LPARAM)buffer);//将缓冲区文本输入
				CHARRANGE b{ selectMin, selectMin + bufferLen };
				//CHARRANGE b{ 1, 3 };
				SendMessageW(hRichEdit, EM_EXSETSEL, 0, (LPARAM)&b);//改变选择区域		
				CHARFORMATA cformat;
				cformat.cbSize = sizeof(cformat);
				cformat.dwMask = CFM_COLOR;
				cformat.crTextColor = RGB(R, G, B);
				SendMessageW(hRichEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cformat);//TODO 设置选择区域格式，有问题，暂时留着
				bufferLen = 0;// 清空缓冲区
				//		txtPreviewClone.AppendText(buffer.ToString());// 将缓冲字符和换行输出
		//		txtPreviewClone.SelectionColor = Color.White;
				i++;// 跳过r或R
				continue;
			}

		}
		buffer[bufferLen++] = temp;// 将字符输入到缓冲区
	}
	if (bufferLen!=0) {
		buffer[bufferLen ++] = NULL;//让缓冲区结束
		int selectEnd = SendMessageW(hRichEdit, EM_GETTEXTLENGTHEX, (WPARAM)&lengthstrust, (LPARAM)0);
		CHARRANGE a{ selectEnd, selectEnd };
		SendMessageW(hRichEdit, EM_EXSETSEL, 0, (LPARAM)&a);//改变选择区域		
		SendMessageW(hRichEdit, EM_REPLACESEL, 0, (LPARAM)buffer);//将缓冲区文本输入
	}
	//public static void ConvertToPreviewTextBox(MyTextBox txtEdit, MyRichTextBox txtPreview)
	//{
	//	int cursorLocation = txtEdit.SelectionStart;
	//	txtEdit.Text = txtEdit.Text.Replace(Environment.NewLine, "|n");// 转换回车换行为|n
	//	txtEdit.SelectionStart = cursorLocation;
	//	char[] charArray = txtEdit.Text.ToCharArray();// 将原来的字符串转为字符数组处理，并转换回车换行为|n
	//	StringBuilder buffer = new StringBuilder();// 用于缓冲还没输出的字符

	//	for (int i = 0; i < charArray.Length; i++)
	//	{
	//		if (charArray[i] == '|')// 转义字符
	//		{
	//			if ((i + 1) < charArray.Length && charArray[i + 1] == '|')// 字符'|'
	//			{
	//				buffer.Append('|');// 将字符'|'输入到缓冲区
	//				i++;
	//				continue;
	//			}
	//			if (((i + 1) < charArray.Length) && ((charArray[i + 1] == 'n') || (charArray[i + 1] == 'N')))// 换行
	//			{
	//				Color currentColor = txtPreviewClone.SelectionColor;// 保存当前颜色
	//				txtPreviewClone.AppendText(buffer.ToString() + Environment.NewLine);// 将缓冲字符和换行输出
	//				buffer = new StringBuilder();// 清空缓冲区
	//				txtPreviewClone.SelectionColor = currentColor;// 恢复颜色
	//				i++;// 跳过n或N
	//				continue;
	//			}
	//			else if (((i + 9) < charArray.Length) && ((charArray[i + 1] == 'c') || (charArray[i + 1] == 'C')))// 颜色开始
	//			{
	//				string strColor = charArray[i + 2].ToString() + charArray[i + 3].ToString()// A
	//					+ charArray[i + 4].ToString() + charArray[i + 5].ToString()// R
	//					+ charArray[i + 6].ToString() + charArray[i + 7].ToString()// G
	//					+ charArray[i + 8].ToString() + charArray[i + 9].ToString()// B
	//					;
	//				if (IsColor(strColor) == true)// 可以转化为颜色
	//				{
	//					txtPreviewClone.AppendText(buffer.ToString());// 将缓冲字符和换行输出
	//					buffer = new StringBuilder();// 清空缓冲区
	//					txtPreviewClone.SelectionColor = ConvertToColor(strColor);
	//					i += 9;// 跳过c或C和8位的颜色值
	//					continue;
	//				}
	//			}
	//			else if (((i + 1) < charArray.Length) && ((charArray[i + 1] == 'r') || (charArray[i + 1] == 'R')))// 颜色结束
	//			{
	//				txtPreviewClone.AppendText(buffer.ToString());// 将缓冲字符和换行输出
	//				buffer = new StringBuilder();// 清空缓冲区
	//				txtPreviewClone.SelectionColor = Color.White;
	//				i++;// 跳过r或R
	//				continue;
	//			}
	//		}
	//		buffer.Append(charArray[i].ToString());// 将字符输入到缓冲区
	//	}
	//	txtPreviewClone.AppendText(buffer.ToString());// 将剩余的字符输出

	//	txtPreview.Rtf = txtPreviewClone.Rtf;
	//	txtPreviewClone.Dispose();
	//	txtEdit.lockTextChange = false;
	//	txtPreview.lockTextChange = false;
	//}

	//public static void ConvertToEditTextBox(MyRichTextBox txtPreview, MyTextBox txtEdit)
	//{
	//	txtEdit.lockTextChange = true;

	//	#region 克隆控件
	//		MyRichTextBox txtPreviewClone = new MyRichTextBox()
	//	{
	//		Rtf = txtPreview.Rtf,
	//		SelectionStart = 0,// 从开头开始处理
	//		SelectionLength = 1,// 每次的处理长度
	//		ignoreRefresh = true// 忽略控件自身的重绘，提高响应速度
	//	};
	//	#endregion

	//		bool isHighLight = false;// 标志是否高亮中
	//	StringBuilder sb = new StringBuilder();// 存储已经处理的文本
	//	Color currentColor = txtPreviewClone.SelectionColor;// 当前颜色

	//	#region 处理第一个字符
	//		if (currentColor != Color.White)
	//		{
	//			sb.Append("|c" + ColorToHex(txtPreviewClone.SelectionColor));
	//			isHighLight = true;
	//		}
	//	#endregion

	//		int length = txtPreviewClone.TextLength;// 处理的总文本长度

	//	while (txtPreviewClone.SelectionStart < length)
	//	{
	//		if (txtPreviewClone.SelectionColor != currentColor)// 改变颜色
	//		{
	//			if (isHighLight)// 结束高亮
	//			{
	//				sb.Append("|r");
	//				isHighLight = false;
	//			}
	//			if (txtPreviewClone.SelectionColor != Color.White)// 不是默认颜色，开始高亮
	//			{
	//				sb.Append("|c" + ColorToHex(txtPreviewClone.SelectionColor));
	//				isHighLight = true;
	//			}
	//			currentColor = txtPreviewClone.SelectionColor;
	//		}
	//		#region 将回车转为 | n
	//			if (txtPreviewClone.SelectedText == "\n")
	//			{
	//				sb.Append("|n");
	//				txtPreviewClone.SelectionStart++;
	//				continue;
	//			}
	//		#endregion
	//			#region 将 | 转为 ||
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

	//	txtPreviewClone.Dispose();// 销毁克隆对象
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
	//	txtEdit.Select();// 激活控件
	//}

	//public static void SetTxtPreviewSingleColor(MyRichTextBox txtPreview, Color color)
	//{
	//	txtPreview.lockTextChange = true;
	//	int cursorLocation = txtPreview.SelectionStart;// 保存编辑位置
	//	int selectLength = txtPreview.SelectionLength;// 保存处理字符串的长度
	//	txtPreview.SelectionColor = color;// 设置颜色
	//	txtPreview.SelectionStart = cursorLocation + selectLength;// 移动光标
	//	txtPreview.SelectionLength = 0;// 清空选择
	//	txtPreview.lockTextChange = false;
	//	txtPreview.Select();// 激活控件
	//}

	//public static void SetTxtEditGradual(MyTextBox txtEdit, Color startColor, Color endColor)
	//{
	//	int processLength = 0;// 去除控制字符外的字符长度
	//	string selectedText = txtEdit.SelectedText;// 选择的文本
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
	//		txtEdit.Select();// 激活控件
	//	}
	//	else
	//	{
	//		SetTxtEditSingleColor(txtEdit, startColor);
	//	}

	//	//int selectLength = txtEdit.SelectionLength;// 需要处理的长度
	//	//if (selectLength > 1)
	//	//{
	//	//    txtEdit.lockTextChange = true;
	//	//    for (int i = 0; i < selectLength; i++)
	//	//    {
	//	//        Color tempColor = Color.FromArgb(startColor.R + (endColor.R - startColor.R) * i / (selectLength - 1), startColor.G + (endColor.G - startColor.G) * i / (selectLength - 1), startColor.B + (endColor.B - startColor.B) * i / (selectLength - 1));// 计算当前字的颜色
	//	//        txtEdit.SelectionLength = 0;
	//	//        txtEdit.SelectedText = "|c" + ColorToHex(tempColor);
	//	//        txtEdit.SelectionStart++;
	//	//        txtEdit.SelectedText = "|r";
	//	//        txtEdit.Select();// 激活控件
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
	//	int selectLength = txtPreview.SelectionLength;// 需要处理的长度
	//	if (selectLength > 1)
	//	{
	//		txtPreview.lockTextChange = true;
	//		for (int i = 0; i < selectLength; i++)
	//		{
	//			txtPreview.SelectionLength = 1;
	//			Color tempColor = Color.FromArgb(startColor.R + (endColor.R - startColor.R) * i / (selectLength - 1), startColor.G + (endColor.G - startColor.G) * i / (selectLength - 1), startColor.B + (endColor.B - startColor.B) * i / (selectLength - 1));// 计算当前字的颜色
	//			txtPreview.SelectionColor = tempColor;
	//			txtPreview.SelectionLength = 0;
	//			txtPreview.SelectionStart++;
	//		}
	//		txtPreview.lockTextChange = false;
	//		txtPreview.Select();// 激活控件
	//	}
	//	else
	//	{
	//		SetTxtPreviewSingleColor(txtPreview, startColor);
	//	}
	//}

	///// <summary>
	///// 判定一个字符串是否可以转化为颜色
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
	///// 将字符串转化为颜色
	///// </summary>
	///// <param name="strColor"></param>
	///// <returns></returns>
	//private static Color ConvertToColor(string strColor)
	//{
	//	string strA = strColor.Substring(0, 2);// A
	//	string strR = strColor.Substring(2, 2);// R
	//	string strG = strColor.Substring(4, 2);// G
	//	string strB = strColor.Substring(6, 2);// B
	//	int colorA = Convert.ToInt32(strA, 16);// 将16进制转化为10进制
	//	int colorR = Convert.ToInt32(strR, 16);
	//	int colorG = Convert.ToInt32(strG, 16);
	//	int colorB = Convert.ToInt32(strB, 16);
	//	return Color.FromArgb(colorR, colorG, colorB);// 好像War3中A用不着
	//}

	///// <summary>
	///// 将颜色转化为16进制字符串
	///// </summary>
	///// <param name="color"></param>
	///// <returns></returns>
	//public static string ColorToHex(Color color)
	//{
	//	string strA = color.A.ToString("x").PadLeft(2, '0');// 转换为16进制并在前面补充0使长度为2
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
