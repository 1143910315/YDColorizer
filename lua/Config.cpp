#include "Config.h"
#include "Path.h"
#include "Tool.h"
#include <stdio.h>

int Config::GetLanguage()
{
	WCHAR* fileName = Path().GetConfigFile();
	int language = GetPrivateProfileIntW(globalSet, languageSet, 0, fileName);
	free(fileName);
	return language;
	//char str[10];
	//sprintf(str, "%d", language);
	//MessageBox(NULL, T.ChartoWCHAR(str, 10), TEXT("World"), MB_OK);
}

LPWSTR Config::WESTRING_COD_TYPE_STRING()
{
	LPWSTR re = (LPWSTR)malloc(20 * sizeof(WCHAR));
	GetPrivateProfileStringW(lpAppName, WESTRING_COD_TYPE_STRINGstr, NULL, re, 20, Path().GetWorldEditStringsFile());
	return re;
}

LPWSTR Config::WESTRING_UE_DLG_EDITVALUE()
{
	LPWSTR re = (LPWSTR)malloc(20 * sizeof(WCHAR));
	GetPrivateProfileStringW(lpAppName, WESTRING_UE_DLG_EDITVALUEstr, NULL, re, 20, Path().GetWorldEditStringsFile());
	return re;
}

LPWSTR Config::WESTRING_IE_DLG_EDITVALUE()
{
	LPWSTR re = (LPWSTR)malloc(20 * sizeof(WCHAR));
	GetPrivateProfileStringW(lpAppName, WESTRING_IE_DLG_EDITVALUEstr, NULL, re, 20, Path().GetWorldEditStringsFile());
	return re;
}

LPWSTR Config::WESTRING_AE_DLG_EDITVALUE()
{
	LPWSTR re = (LPWSTR)malloc(20 * sizeof(WCHAR));
	GetPrivateProfileStringW(lpAppName, WESTRING_AE_DLG_EDITVALUEstr, NULL, re, 20, Path().GetWorldEditStringsFile());
	return re;
}

LPWSTR Config::WESTRING_FE_DLG_EDITVALUE()
{
	LPWSTR re = (LPWSTR)malloc(20 * sizeof(WCHAR));
	GetPrivateProfileStringW(lpAppName, WESTRING_FE_DLG_EDITVALUEstr, NULL, re, 20, Path().GetWorldEditStringsFile());
	return re;
}

LPWSTR Config::WESTRING_BE_DLG_EDITVALUE()
{
	LPWSTR re = (LPWSTR)malloc(20 * sizeof(WCHAR));
	GetPrivateProfileStringW(lpAppName, WESTRING_BE_DLG_EDITVALUEstr, NULL, re, 20, Path().GetWorldEditStringsFile());
	return re;
}

LPWSTR Config::WESTRING_DE_DLG_EDITVALUE()
{
	LPWSTR re = (LPWSTR)malloc(20 * sizeof(WCHAR));
	GetPrivateProfileStringW(lpAppName, WESTRING_DE_DLG_EDITVALUEstr, NULL, re, 20, Path().GetWorldEditStringsFile());
	return re;
}

LPWSTR Config::WESTRING_GE_DLG_EDITVALUE()
{
	LPWSTR re = (LPWSTR)malloc(20 * sizeof(WCHAR));
	GetPrivateProfileStringW(lpAppName, WESTRING_GE_DLG_EDITVALUEstr, NULL, re, 20, Path().GetWorldEditStringsFile());
	return re;
}
