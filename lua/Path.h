/*************************************************
Author:            |メ破坏者☆
Date:              |2017-02-07
version：          |0.1.1
Description:       |获取目录、文件路径
**************************************************/
#pragma once
#include <windows.h>
class Path
{
public:
	char* GetPath();//获取Dll所在目录，以'\'结尾的路径
	char* GetYDWEPath();//获取Dll所在目录，不以'\'结尾的路径
	LPWSTR GetConfigFile();//获取插件配置文件路径
	LPWSTR GetWorldEditStringsFile();//获取WorldEditStrings配置文件路径
private:
	const char* DLLpath = "\\plugin\\YDColorizer\\";//相对于YDWE的DLL目录
	const char* ConfigFile = "\\plugin\\YDColorizer\\YDColorizerConfig.ini";
	const char* WorldEditStrings = "\\share\\mpq\\units\\ui\\WorldEditStrings.txt";
};