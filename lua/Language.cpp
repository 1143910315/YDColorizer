#include "Language.h"

Language::Language(int language)
{
	switch (language) {
	case 0:
		lessDLL = TEXT("缺少RichEd20.Dll");
		error = TEXT("错误");
		CreateRichEditViewerror=TEXT("创建富文本组件失败！");
		break;
	}

}


