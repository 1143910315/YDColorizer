#include "Language.h"
/*************************************************
Function:         |Language
Description:      |��ȡ���������࣬һ��DLLֻ����һ����
Input:            |0-�������ģ�1-��������
*************************************************/
Language::Language(int language) {
	switch (language) {
	case 0:
		lessDLL = TEXT("ȱ��RichEd20.Dll");
		error = TEXT("����");
		CreateRichEditViewerror = TEXT("�������ı����ʧ�ܣ�");
		CreateWindowError = TEXT("�������ڳ���");
		break;
	case 1:
		lessDLL = TEXT("ȱ��RichEd20.Dll");
		error = TEXT("�e�`");
		CreateRichEditViewerror = TEXT("�������ı��M��ʧ����");
		CreateWindowError = TEXT("�������ڳ��e��");
		break;
	}
}