#include "Language.h"
/*************************************************
Function:         |Language
Description:      |获取共用语言类，一个DLL只创建一个，
Input:            |0-简体中文，1-繁体中文
*************************************************/
Language::Language(int language) {
	switch (language) {
	case 0:
		lessDLL = TEXT("缺少RichEd20.Dll");
		error = TEXT("错误");
		CreateRichEditViewerror = TEXT("创建富文本组件失败！");
		CreateWindowError = TEXT("创建窗口出错！");
		break;
	case 1:
		lessDLL = TEXT("缺少RichEd20.Dll");
		error = TEXT("錯誤");
		CreateRichEditViewerror = TEXT("創建富文本組件失敗！");
		CreateWindowError = TEXT("創建窗口出錯！");
		break;
	}
}