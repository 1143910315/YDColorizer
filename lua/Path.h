/*************************************************
Author:            |���ƻ��ߡ�
Date:              |2017-02-05
version��          |0.0.0
Description:       |��ȡDLL����Ŀ¼
**************************************************/
#pragma once
#include <windows.h>
class Path
{
public:
	char* GetPath();
private:
	char *GetDLLPath();
	const char* DLLpath = "\\plugin\\YDColorizer\\";//�����YDWE��DLLĿ¼
};