#include "Language.h"

Language::Language(int language)
{
	switch (language) {
	case 0:
		lessDLL = TEXT("ȱ��RichEd20.Dll");
		error = TEXT("����");
		CreateRichEditViewerror=TEXT("�������ı����ʧ�ܣ�");
		break;
	}

}


