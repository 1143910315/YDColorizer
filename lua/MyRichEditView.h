/*************************************************
Author:            |���ƻ��ߡ�
Date:              |2017-02-28
version��          |0.0.2
Description:       |���ı��ؼ�
**************************************************/
#pragma once
#include "Language.h"
#include "Tool.h"
#include <Windows.h>
#include <Richedit.h>
//���ı����
class MyRichEditView {
public:
	MyRichEditView(HWND hwndParent, long top, long width, const Language* L);
	bool SetColor();//Ӧ����ɫ��ѡ����ı�
	void setText(const LPWSTR text, int len);//����δ��ʽ�ı������ı��༭��
	HWND getHwnd();//��ȡ���ı��༭����
private:
	HWND hRichEdit;//���渻�ı��༭����
	Tool T = Tool();//������
	CHARFORMATW defaultFormat = CHARFORMATW();//Ĭ�ϵ��ı���ʽ
};