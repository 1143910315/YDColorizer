/*************************************************
Author:            |���ƻ��ߡ�
Date:              |2017-02-28
version��          |0.2.1
Description:       |��ȡĿ¼���ļ�·��
**************************************************/
#pragma once
#include <Windows.h>
//��Ŀ¼�������
class Path {
public:
	char* GetPath();//��ȡDll����Ŀ¼����'\'��β��·��
	char* GetYDWEPath();//��ȡDll����Ŀ¼������'\'��β��·��
	LPWSTR GetConfigFile();//��ȡ��������ļ�·��
	LPWSTR GetWorldEditStringsFile();//��ȡWorldEditStrings�����ļ�·��
	LPSTR GetWorldEditStringsFileLPSTR();//��ȡWorldEditStrings�����ļ�·��
private:
	const char* DLLpath = "\\plugin\\YDColorizer\\";//�����YDWE��DLLĿ¼
	const char* ConfigFile = "\\plugin\\YDColorizer\\YDColorizerConfig.ini";
	const char* WorldEditStrings = "\\share\\mpq\\units\\ui\\WorldEditStrings.txt";
};