/*************************************************
Author:            |���ƻ��ߡ�
Date:              |2017-02-28
version��          |0.1.1
Description:       |��ȡ����
**************************************************/
#pragma once
#include <Windows.h>
#include "Tool.h"
//���������
class Config {
public:
	int GetLanguage();//�����û�ȡ����
	LPWSTR WESTRING_COD_TYPE_STRING(); //= �ַ���
	void WESTRING_COD_TYPE_STRING(LPWSTR target, int size, LPSTR path); //= �ַ���
	LPWSTR WESTRING_UE_DLG_EDITVALUE();//= �༭��λֵ - %s
	void WESTRING_UE_DLG_EDITVALUE(LPWSTR target, int size, LPSTR path);//= �༭��λֵ - %s
	LPWSTR WESTRING_IE_DLG_EDITVALUE();//= �༭��Ʒֵ - %s
	void WESTRING_IE_DLG_EDITVALUE(LPWSTR target, int size, LPSTR path);//= �༭��Ʒֵ - %s
	LPWSTR WESTRING_AE_DLG_EDITVALUE();//= �༭����ֵ - %s
	void WESTRING_AE_DLG_EDITVALUE(LPWSTR target, int size, LPSTR path);//= �༭����ֵ - %s
	LPWSTR WESTRING_FE_DLG_EDITVALUE();//= �༭Ч��ֵ - %s
	void WESTRING_FE_DLG_EDITVALUE(LPWSTR target, int size, LPSTR path);//= �༭Ч��ֵ - %s
	LPWSTR WESTRING_BE_DLG_EDITVALUE();//= �༭���ƻ���ֵ - %s
	void WESTRING_BE_DLG_EDITVALUE(LPWSTR target, int size, LPSTR path);//= �༭���ƻ���ֵ - %s
	LPWSTR WESTRING_DE_DLG_EDITVALUE();//= �༭װ����ֵ - %s
	void WESTRING_DE_DLG_EDITVALUE(LPWSTR target, int size, LPSTR path);//= �༭װ����ֵ - %s
	LPWSTR WESTRING_GE_DLG_EDITVALUE();//= �༭�Ƽ�ֵ - %s
	void WESTRING_GE_DLG_EDITVALUE(LPWSTR target, int size, LPSTR path);//= �༭�Ƽ�ֵ - %s
private:
	Tool T = Tool();//������
	const LPCWSTR globalSet = TEXT("Application");//���������_����
	const LPCWSTR languageSet = TEXT("Language");//������԰汾_����
	const char lpAppName[40] = "WorldEditStrings";//WorldEditStrings.txt_����
	//********************************����ΪWorldEditStrings.txt_����
	const char WESTRING_COD_TYPE_STRINGstr[40] = "WESTRING_COD_TYPE_STRING";  //�ַ���
	const char WESTRING_UE_DLG_EDITVALUEstr[40] = "WESTRING_UE_DLG_EDITVALUE";//�༭��λֵ - %s
	const char WESTRING_IE_DLG_EDITVALUEstr[40] = "WESTRING_IE_DLG_EDITVALUE";//�༭��Ʒֵ - %s
	const char WESTRING_AE_DLG_EDITVALUEstr[40] = "WESTRING_AE_DLG_EDITVALUE";//�༭����ֵ - %s
	const char WESTRING_FE_DLG_EDITVALUEstr[40] = "WESTRING_FE_DLG_EDITVALUE";//�༭Ч��ֵ - %s
	const char WESTRING_BE_DLG_EDITVALUEstr[40] = "WESTRING_BE_DLG_EDITVALUE";//�༭���ƻ���ֵ - %s
	const char WESTRING_DE_DLG_EDITVALUEstr[40] = "WESTRING_DE_DLG_EDITVALUE";//�༭װ����ֵ - %s
	const char WESTRING_GE_DLG_EDITVALUEstr[40] = "WESTRING_GE_DLG_EDITVALUE";//�༭�Ƽ�ֵ - %s
};