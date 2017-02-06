/*************************************************
Author:            |メ破坏者☆
Date:              |2017-02-05
version：          |0.0.0
Description:       |获取DLL所在目录
**************************************************/
#pragma once
#include <windows.h>
class Path
{
public:
	char* GetPath();
private:
	char *GetDLLPath();
	const char* DLLpath = "\\plugin\\YDColorizer\\";//相对于YDWE的DLL目录
};