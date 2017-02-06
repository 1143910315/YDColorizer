/*************************************************
Author:            |���ƻ��ߡ�
Date:              |2017-02-07
version��          |0.1.1
Description:       |��ȡĿ¼���ļ�·��
**************************************************/
#pragma once
#include <windows.h>
class Path
{
public:
	char* GetPath();//��ȡDll����Ŀ¼����'\'��β��·��
	char* GetYDWEPath();//��ȡDll����Ŀ¼������'\'��β��·��
	LPWSTR GetConfigFile();//��ȡ��������ļ�·��
	LPWSTR GetWorldEditStringsFile();//��ȡWorldEditStrings�����ļ�·��
private:
	const char* DLLpath = "\\plugin\\YDColorizer\\";//�����YDWE��DLLĿ¼
	const char* ConfigFile = "\\plugin\\YDColorizer\\YDColorizerConfig.ini";
	const char* WorldEditStrings = "\\share\\mpq\\units\\ui\\WorldEditStrings.txt";
};