#include "Language.h"
/*************************************************
Function:         |Language
Description:      |��ȡ���������࣬һ��DLLֻ����һ����
Input:            |0-�������ģ�1-��������
*************************************************/
Language::Language(int language) {
	switch (language) {
	case 0:
		lessDLL = TEXT("ȱ��Riched20.Dll");
		error = TEXT("����");
		CreateRichEditViewerror = TEXT("�������ı����ʧ�ܣ�");
		CreateWindowError = TEXT("�������ڳ���");
		gainText = TEXT("��ȡ");
		applyText = TEXT("Ӧ��");
		colorAlarm = TEXT("�벻Ҫ�����ʹ��͸���ȣ���Ϊ������Ч�����ԣ�");
		alarm = TEXT("����");
		break;
	case 1:
		lessDLL = TEXT("ȱ��Riched20.Dll");
		error = TEXT("�e�`");
		CreateRichEditViewerror = TEXT("�������ı��M��ʧ����");
		CreateWindowError = TEXT("�������ڳ��e��");
		gainText = TEXT("�@ȡ");
		applyText = TEXT("����");
		colorAlarm = TEXT("Ո��Ҫ���ﾎʹ��͸���ȣ�����@�ǟoЧ�Č��ԣ�");
		alarm = TEXT("����");
		break;
	}
}