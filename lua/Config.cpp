#include "Config.h"
#include "Path.h"
#include "Tool.h"
#include <stdio.h>
/*************************************************
Function:         |GetLanguage
Description:      |获取语言代码，一个DLL只获取一次语言配置
Return:           |0-简体中文，1-繁体中文
*************************************************/
int Config::GetLanguage() {
	WCHAR* fileName = Path().GetConfigFile();
	int language = GetPrivateProfileIntW(globalSet, languageSet, 0, fileName);
	free(fileName);
	return language;
}
/*************************************************
Function:         |WESTRING_COD_TYPE_STRING
Description:      |获取WESTRING_COD_TYPE_STRING配置
Input:            |size    ：target的大小
				   path    ：配置文件路径
Output:           |target  ：将读取的配置写入此地址
*************************************************/
void Config::WESTRING_COD_TYPE_STRING(LPWSTR target, int size, LPSTR path) {
	LPSTR ret = (LPSTR)malloc(size * sizeof(CHAR));
	GetPrivateProfileStringA(lpAppName, WESTRING_COD_TYPE_STRINGstr, NULL, ret, size, path);
	T.UTF8ToGBK(ret, target, size);
	free(ret);
}
/*************************************************
Function:         |WESTRING_UE_DLG_EDITVALUE
Description:      |获取WESTRING_UE_DLG_EDITVALUE配置
Input:            |size    ：target的大小
				   path    ：配置文件路径
Output:           |target  ：将读取的配置写入此地址
*************************************************/
void Config::WESTRING_UE_DLG_EDITVALUE(LPWSTR target, int size, LPSTR path) {
	LPSTR ret = (LPSTR)malloc(size * sizeof(CHAR));
	GetPrivateProfileStringA(lpAppName, WESTRING_UE_DLG_EDITVALUEstr, NULL, ret, size, path);
	T.UTF8ToGBK(ret, target, size);
	free(ret);
}
/*************************************************
Function:         |WESTRING_IE_DLG_EDITVALUE
Description:      |获取WESTRING_IE_DLG_EDITVALUE配置
Input:            |size    ：target的大小
				   path    ：配置文件路径
Output:           |target  ：将读取的配置写入此地址
*************************************************/
void Config::WESTRING_IE_DLG_EDITVALUE(LPWSTR target, int size, LPSTR path) {
	LPSTR ret = (LPSTR)malloc(size * sizeof(CHAR));
	GetPrivateProfileStringA(lpAppName, WESTRING_IE_DLG_EDITVALUEstr, NULL, ret, size, path);
	T.UTF8ToGBK(ret, target, size);
	free(ret);
}
/*************************************************
Function:         |WESTRING_AE_DLG_EDITVALUE
Description:      |获取WESTRING_AE_DLG_EDITVALUE配置
Input:            |size    ：target的大小
				   path    ：配置文件路径
Output:           |target  ：将读取的配置写入此地址
*************************************************/
void Config::WESTRING_AE_DLG_EDITVALUE(LPWSTR target, int size, LPSTR path) {
	LPSTR ret = (LPSTR)malloc(size * sizeof(CHAR));
	GetPrivateProfileStringA(lpAppName, WESTRING_AE_DLG_EDITVALUEstr, NULL, ret, size, path);
	T.UTF8ToGBK(ret, target, size);
	free(ret);
}
/*************************************************
Function:         |WESTRING_FE_DLG_EDITVALUE
Description:      |获取WESTRING_FE_DLG_EDITVALUE配置
Input:            |size    ：target的大小
				   path    ：配置文件路径
Output:           |target  ：将读取的配置写入此地址
*************************************************/
void Config::WESTRING_FE_DLG_EDITVALUE(LPWSTR target, int size, LPSTR path) {
	LPSTR ret = (LPSTR)malloc(size * sizeof(CHAR));
	GetPrivateProfileStringA(lpAppName, WESTRING_FE_DLG_EDITVALUEstr, NULL, ret, size, path);
	T.UTF8ToGBK(ret, target, size);
	free(ret);
}
/*************************************************
Function:         |WESTRING_BE_DLG_EDITVALUE
Description:      |获取WESTRING_BE_DLG_EDITVALUE配置
Input:            |size    ：target的大小
				   path    ：配置文件路径
Output:           |target  ：将读取的配置写入此地址
*************************************************/
void Config::WESTRING_BE_DLG_EDITVALUE(LPWSTR target, int size, LPSTR path) {
	LPSTR ret = (LPSTR)malloc(size * sizeof(CHAR));
	GetPrivateProfileStringA(lpAppName, WESTRING_BE_DLG_EDITVALUEstr, NULL, ret, size, path);
	T.UTF8ToGBK(ret, target, size);
	free(ret);
}
/*************************************************
Function:         |WESTRING_DE_DLG_EDITVALUE
Description:      |获取WESTRING_DE_DLG_EDITVALUE配置
Input:            |size    ：target的大小
				   path    ：配置文件路径
Output:           |target  ：将读取的配置写入此地址
*************************************************/
void Config::WESTRING_DE_DLG_EDITVALUE(LPWSTR target, int size, LPSTR path) {
	LPSTR ret = (LPSTR)malloc(size * sizeof(CHAR));
	GetPrivateProfileStringA(lpAppName, WESTRING_DE_DLG_EDITVALUEstr, NULL, ret, size, path);
	T.UTF8ToGBK(ret, target, size);
	free(ret);
}
/*************************************************
Function:         |WESTRING_GE_DLG_EDITVALUE
Description:      |获取WESTRING_GE_DLG_EDITVALUE配置
Input:            |size    ：target的大小
				   path    ：配置文件路径
Output:           |target  ：将读取的配置写入此地址
*************************************************/
void Config::WESTRING_GE_DLG_EDITVALUE(LPWSTR target, int size, LPSTR path) {
	LPSTR ret = (LPSTR)malloc(size * sizeof(CHAR));
	GetPrivateProfileStringA(lpAppName, WESTRING_GE_DLG_EDITVALUEstr, NULL, ret, size, path);
	T.UTF8ToGBK(ret, target, size);
	free(ret);
}
