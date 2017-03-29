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
	MyRichEditView(HWND hwndParent, long left, long top, long width, long height, const Language* L);
	bool SetColor(COLORREF color);//Ӧ����ɫ��ѡ����ı�
	void setText(const LPWSTR text, int len);//����δ��ʽ�ı������ı��༭��
	int getText(LPWSTR text,int len,int* start,COLORREF* color);//ת�����ı��༭������ı�
	HWND getHwnd();//��ȡ���ı��༭����
private:
	const Language* L;//������
	HWND hRichEdit;//���渻�ı��༭����
	Tool T = Tool();//������
	CHARFORMATW defaultFormat = CHARFORMATW();//Ĭ�ϵ��ı���ʽ
};