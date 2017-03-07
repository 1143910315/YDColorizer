#include "Language.h"
/*************************************************
Function:         |Language
Description:      |获取共用语言类，一个DLL只创建一个，
Input:            |0-简体中文，1-繁体中文
*************************************************/
Language::Language(int language) {
	switch (language) {
	case 0:
		lessDLL = TEXT("缺少Riched20.Dll");
		error = TEXT("错误");
		CreateRichEditViewerror = TEXT("创建富文本组件失败！");
		CreateWindowError = TEXT("创建窗口出错！");
		gainText = TEXT("获取");
		applyText = TEXT("应用");
		colorAlarm = TEXT("请不要在物编使用透明度，因为这是无效的属性！");
		alarm = TEXT("警告");
		break;
	case 1:
		lessDLL = TEXT("缺少Riched20.Dll");
		error = TEXT("錯誤");
		CreateRichEditViewerror = TEXT("創建富文本組件失敗！");
		CreateWindowError = TEXT("創建窗口出錯！");
		gainText = TEXT("獲取");
		applyText = TEXT("應用");
		colorAlarm = TEXT("請不要在物編使用透明度，因為這是無效的屬性！");
		alarm = TEXT("警告");
		break;
	}
}