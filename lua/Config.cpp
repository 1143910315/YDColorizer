#include "Config.h"
#include "Path.h"
#include "Tool.h"
#include <stdio.h>
/*************************************************
Function:         |GetLanguage
Description:      |��ȡ���Դ��룬һ��DLLֻ��ȡһ����������
Return:           |0-�������ģ�1-��������
*************************************************/
int Config::GetLanguage() {
	WCHAR* fileName = Path().GetConfigFile();
	int language = GetPrivateProfileIntW(globalSet, languageSet, 0, fileName);
	free(fileName);
	return language;
}
/*************************************************
Function:         |WESTRING_COD_TYPE_STRING
Description:      |��ȡWESTRING_COD_TYPE_STRING����
Input:            |size    ��target�Ĵ�С
				   path    �������ļ�·��
Output:           |target  ������ȡ������д��˵�ַ
*************************************************/
void Config::WESTRING_COD_TYPE_STRING(LPWSTR target, int size, LPSTR path) {
	LPSTR ret = (LPSTR)malloc(size * sizeof(CHAR));
	GetPrivateProfileStringA(lpAppName, WESTRING_COD_TYPE_STRINGstr, NULL, ret, size, path);
	T.UTF8ToGBK(ret, target, size);
	free(ret);
}
/*************************************************
Function:         |WESTRING_UE_DLG_EDITVALUE
Description:      |��ȡWESTRING_UE_DLG_EDITVALUE����
Input:            |size    ��target�Ĵ�С
				   path    �������ļ�·��
Output:           |target  ������ȡ������д��˵�ַ
*************************************************/
void Config::WESTRING_UE_DLG_EDITVALUE(LPWSTR target, int size, LPSTR path) {
	LPSTR ret = (LPSTR)malloc(size * sizeof(CHAR));
	GetPrivateProfileStringA(lpAppName, WESTRING_UE_DLG_EDITVALUEstr, NULL, ret, size, path);
	T.UTF8ToGBK(ret, target, size);
	free(ret);
}
/*************************************************
Function:         |WESTRING_IE_DLG_EDITVALUE
Description:      |��ȡWESTRING_IE_DLG_EDITVALUE����
Input:            |size    ��target�Ĵ�С
				   path    �������ļ�·��
Output:           |target  ������ȡ������д��˵�ַ
*************************************************/
void Config::WESTRING_IE_DLG_EDITVALUE(LPWSTR target, int size, LPSTR path) {
	LPSTR ret = (LPSTR)malloc(size * sizeof(CHAR));
	GetPrivateProfileStringA(lpAppName, WESTRING_IE_DLG_EDITVALUEstr, NULL, ret, size, path);
	T.UTF8ToGBK(ret, target, size);
	free(ret);
}
/*************************************************
Function:         |WESTRING_AE_DLG_EDITVALUE
Description:      |��ȡWESTRING_AE_DLG_EDITVALUE����
Input:            |size    ��target�Ĵ�С
				   path    �������ļ�·��
Output:           |target  ������ȡ������д��˵�ַ
*************************************************/
void Config::WESTRING_AE_DLG_EDITVALUE(LPWSTR target, int size, LPSTR path) {
	LPSTR ret = (LPSTR)malloc(size * sizeof(CHAR));
	GetPrivateProfileStringA(lpAppName, WESTRING_AE_DLG_EDITVALUEstr, NULL, ret, size, path);
	T.UTF8ToGBK(ret, target, size);
	free(ret);
}
/*************************************************
Function:         |WESTRING_FE_DLG_EDITVALUE
Description:      |��ȡWESTRING_FE_DLG_EDITVALUE����
Input:            |size    ��target�Ĵ�С
				   path    �������ļ�·��
Output:           |target  ������ȡ������д��˵�ַ
*************************************************/
void Config::WESTRING_FE_DLG_EDITVALUE(LPWSTR target, int size, LPSTR path) {
	LPSTR ret = (LPSTR)malloc(size * sizeof(CHAR));
	GetPrivateProfileStringA(lpAppName, WESTRING_FE_DLG_EDITVALUEstr, NULL, ret, size, path);
	T.UTF8ToGBK(ret, target, size);
	free(ret);
}
/*************************************************
Function:         |WESTRING_BE_DLG_EDITVALUE
Description:      |��ȡWESTRING_BE_DLG_EDITVALUE����
Input:            |size    ��target�Ĵ�С
				   path    �������ļ�·��
Output:           |target  ������ȡ������д��˵�ַ
*************************************************/
void Config::WESTRING_BE_DLG_EDITVALUE(LPWSTR target, int size, LPSTR path) {
	LPSTR ret = (LPSTR)malloc(size * sizeof(CHAR));
	GetPrivateProfileStringA(lpAppName, WESTRING_BE_DLG_EDITVALUEstr, NULL, ret, size, path);
	T.UTF8ToGBK(ret, target, size);
	free(ret);
}
/*************************************************
Function:         |WESTRING_DE_DLG_EDITVALUE
Description:      |��ȡWESTRING_DE_DLG_EDITVALUE����
Input:            |size    ��target�Ĵ�С
				   path    �������ļ�·��
Output:           |target  ������ȡ������д��˵�ַ
*************************************************/
void Config::WESTRING_DE_DLG_EDITVALUE(LPWSTR target, int size, LPSTR path) {
	LPSTR ret = (LPSTR)malloc(size * sizeof(CHAR));
	GetPrivateProfileStringA(lpAppName, WESTRING_DE_DLG_EDITVALUEstr, NULL, ret, size, path);
	T.UTF8ToGBK(ret, target, size);
	free(ret);
}
/*************************************************
Function:         |WESTRING_GE_DLG_EDITVALUE
Description:      |��ȡWESTRING_GE_DLG_EDITVALUE����
Input:            |size    ��target�Ĵ�С
				   path    �������ļ�·��
Output:           |target  ������ȡ������д��˵�ַ
*************************************************/
void Config::WESTRING_GE_DLG_EDITVALUE(LPWSTR target, int size, LPSTR path) {
	LPSTR ret = (LPSTR)malloc(size * sizeof(CHAR));
	GetPrivateProfileStringA(lpAppName, WESTRING_GE_DLG_EDITVALUEstr, NULL, ret, size, path);
	T.UTF8ToGBK(ret, target, size);
	free(ret);
}
