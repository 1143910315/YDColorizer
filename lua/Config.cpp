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
	//LPWSTR re = (LPWSTR)malloc(20 * sizeof(WCHAR));
	//memset(re, 0, 20 * sizeof(WCHAR));
	//GetPrivateProfileStringW(lpAppName, WESTRING_COD_TYPE_STRINGstr, NULL, re, 20, Path().GetWorldEditStringsFile());
	//MessageBox(NULL, T.UTF8ToGBK(re), TEXT("World"), MB_OK);
	LPSTR ret = (LPSTR)malloc(40 * sizeof(CHAR));
	memset(ret, 0, 40 * sizeof(CHAR));
	LPSTR p = Path().GetWorldEditStringsFileLPSTR();
	//MessageBoxW(NULL, T.ChartoWCHAR(p, MAX_PATH), TEXT("World"), MB_OK);
	GetPrivateProfileStringA(lpAppName, WESTRING_COD_TYPE_STRINGstr, NULL, ret, 40, p);
	free(p);
	LPWSTR re = T.UTF8ToGBK(ret);
	//MessageBoxW(NULL, re, TEXT("World"), MB_OK);
	free(ret);
	/*LPSTR reaa = (LPSTR)malloc(20 * sizeof(CHAR));
	memset(reaa, 0, 20 * sizeof(CHAR));
	GetPrivateProfileStringA("WorldEditStrings", "WESTRING_COD_TYPE_STRING", NULL, reaa, 20, "D:/Downloads/YDWE1.31.1≤‚ ‘∞Ê/share/mpq/units/ui/WorldEditStrings.txt");
	MessageBoxW(NULL, T.UTF8ToGBK(reaa), TEXT("World"), MB_OK);*/
	return re;
}

LPWSTR Config::WESTRING_UE_DLG_EDITVALUE()
{
	/*LPWSTR re = (LPWSTR)malloc(20 * sizeof(WCHAR));
	memset(re, 0, 20 * sizeof(WCHAR));
	GetPrivateProfileStringW(lpAppName, WESTRING_UE_DLG_EDITVALUEstr, NULL, re, 20, Path().GetWorldEditStringsFile());
	MessageBox(NULL, T.UTF8ToGBK(re), TEXT("World"), MB_OK);
	return re;*/
	LPSTR ret = (LPSTR)malloc(40 * sizeof(CHAR));
	memset(ret, 0, 40 * sizeof(CHAR));
	LPSTR p = Path().GetWorldEditStringsFileLPSTR();
	GetPrivateProfileStringA(lpAppName, WESTRING_UE_DLG_EDITVALUEstr, NULL, ret, 40, p);
	free(p);
	LPWSTR re = T.UTF8ToGBK(ret);
	//MessageBoxW(NULL, re, TEXT("World"), MB_OK);
	free(ret);
	return re;
}

LPWSTR Config::WESTRING_IE_DLG_EDITVALUE()
{
	/*LPWSTR re = (LPWSTR)malloc(20 * sizeof(WCHAR));
	memset(re, 0, 20 * sizeof(WCHAR));
	GetPrivateProfileStringW(lpAppName, WESTRING_IE_DLG_EDITVALUEstr, NULL, re, 20, Path().GetWorldEditStringsFile());
	return re;*/
	LPSTR ret = (LPSTR)malloc(40 * sizeof(CHAR));
	memset(ret, 0, 40 * sizeof(CHAR));
	LPSTR p = Path().GetWorldEditStringsFileLPSTR();
	GetPrivateProfileStringA(lpAppName, WESTRING_IE_DLG_EDITVALUEstr, NULL, ret, 40, p);
	free(p);
	LPWSTR re = T.UTF8ToGBK(ret);
	free(ret);
	return re;
}

LPWSTR Config::WESTRING_AE_DLG_EDITVALUE()
{
	/*LPWSTR re = (LPWSTR)malloc(20 * sizeof(WCHAR));
	memset(re, 0, 20 * sizeof(WCHAR));
	GetPrivateProfileStringW(lpAppName, WESTRING_AE_DLG_EDITVALUEstr, NULL, re, 20, Path().GetWorldEditStringsFile());
	return re;*/
	LPSTR ret = (LPSTR)malloc(40 * sizeof(CHAR));
	memset(ret, 0, 40 * sizeof(CHAR));
	LPSTR p = Path().GetWorldEditStringsFileLPSTR();
	GetPrivateProfileStringA(lpAppName, WESTRING_AE_DLG_EDITVALUEstr, NULL, ret, 40, p);
	free(p);
	LPWSTR re = T.UTF8ToGBK(ret);
	free(ret);
	return re;
}

LPWSTR Config::WESTRING_FE_DLG_EDITVALUE()
{
	/*LPWSTR re = (LPWSTR)malloc(20 * sizeof(WCHAR));
	memset(re, 0, 20 * sizeof(WCHAR));
	GetPrivateProfileStringW(lpAppName, WESTRING_FE_DLG_EDITVALUEstr, NULL, re, 20, Path().GetWorldEditStringsFile());
	return re;*/
	LPSTR ret = (LPSTR)malloc(40 * sizeof(CHAR));
	memset(ret, 0, 40 * sizeof(CHAR));
	LPSTR p = Path().GetWorldEditStringsFileLPSTR();
	GetPrivateProfileStringA(lpAppName, WESTRING_FE_DLG_EDITVALUEstr, NULL, ret, 40, p);
	free(p);
	LPWSTR re = T.UTF8ToGBK(ret);
	free(ret);
	return re;
}

LPWSTR Config::WESTRING_BE_DLG_EDITVALUE()
{
	/*LPWSTR re = (LPWSTR)malloc(20 * sizeof(WCHAR));
	memset(re, 0, 20 * sizeof(WCHAR));
	GetPrivateProfileStringW(lpAppName, WESTRING_BE_DLG_EDITVALUEstr, NULL, re, 20, Path().GetWorldEditStringsFile());
	return re;*/
	LPSTR ret = (LPSTR)malloc(40 * sizeof(CHAR));
	memset(ret, 0, 40 * sizeof(CHAR));
	LPSTR p = Path().GetWorldEditStringsFileLPSTR();
	GetPrivateProfileStringA(lpAppName, WESTRING_BE_DLG_EDITVALUEstr, NULL, ret, 40, p);
	free(p);
	LPWSTR re = T.UTF8ToGBK(ret);
	//MessageBoxW(NULL, re, TEXT("World"), MB_OK);
	free(ret);
	return re;
}

LPWSTR Config::WESTRING_DE_DLG_EDITVALUE()
{
	/*LPWSTR re = (LPWSTR)malloc(20 * sizeof(WCHAR));
	memset(re, 0, 20 * sizeof(WCHAR));
	GetPrivateProfileStringW(lpAppName, WESTRING_DE_DLG_EDITVALUEstr, NULL, re, 20, Path().GetWorldEditStringsFile());
	return re;*/
	LPSTR ret = (LPSTR)malloc(40 * sizeof(CHAR));
	memset(ret, 0, 40 * sizeof(CHAR));
	LPSTR p = Path().GetWorldEditStringsFileLPSTR();
	GetPrivateProfileStringA(lpAppName, WESTRING_DE_DLG_EDITVALUEstr, NULL, ret, 40, p);
	free(p);
	LPWSTR re = T.UTF8ToGBK(ret);
	free(ret);
	return re;
}

LPWSTR Config::WESTRING_GE_DLG_EDITVALUE()
{
	/*LPWSTR re = (LPWSTR)malloc(20 * sizeof(WCHAR));
	memset(re, 0, 20 * sizeof(WCHAR));
	GetPrivateProfileStringW(lpAppName, WESTRING_GE_DLG_EDITVALUEstr, NULL, re, 20, Path().GetWorldEditStringsFile());
	return re;*/
	LPSTR ret = (LPSTR)malloc(40 * sizeof(CHAR));
	memset(ret, 0, 40 * sizeof(CHAR));
	LPSTR p = Path().GetWorldEditStringsFileLPSTR();
	GetPrivateProfileStringA(lpAppName, WESTRING_GE_DLG_EDITVALUEstr, NULL, ret, 40, p);
	free(p);
	LPWSTR re = T.UTF8ToGBK(ret);
	free(ret);
	return re;
}
