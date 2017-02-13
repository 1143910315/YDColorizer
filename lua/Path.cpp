#include "Path.h"
#include "Tool.h"
#include <direct.h>
/*************************************************
Function:         |GetPath
Description:      |获取DLL所在目录
Calls:            |GetYDWEPath()
Return:           |DLL所在目录，以\结尾的路径
Others:           |如果修改颜色插件的目录，需要修改DLLpath，否则路径将出错
*************************************************/
char* Path::GetPath()
{
	char* buffer = GetYDWEPath();
	Tool().CharAddChar(buffer, MAX_PATH, DLLpath, strlen(DLLpath));
	//for (int i = 0; i < MAX_PATH; i++) {
	//	if (buffer[i] == '\0') {
	//		for (int j = 0; i < MAX_PATH - 1 && j < strlen(DLLpath); i++, j++) {
	//			buffer[i] = DLLpath[j];
	//		}
	//		buffer[i] = '\0';//防止路径过长。
	//		break;
	//	}
	//}
	/*size_t size = sizeof(WCHAR)*MAX_PATH;
	WCHAR* path = (WCHAR*)malloc(size);
	memset(path, 0, size);
	MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer) + 1, path,
		size / sizeof(WCHAR));
	free(buffer);*/
	return buffer;
}
/*************************************************
Function:         |GetYDWEPath
Description:      |获取工作目录
Return:           |YDWE的目录，不以\结尾的路径
*************************************************/
char * Path::GetYDWEPath()
{
	char*buffer = (char*)malloc(MAX_PATH * sizeof(char));
	_getcwd(buffer, MAX_PATH);
	return buffer;
}
/*************************************************
Function:         |GetConfigFile
Description:      |获取配置文件的绝对路径
Calls:            |Tool().ChartoWCHAR()、Tool().CharAddChar()、GetYDWEPath()
Return:           |配置文件的绝对路径
Others:           |ConfigFile指定了配置文件相对YDWE路径
*************************************************/
LPWSTR Path::GetConfigFile()
{
	Tool T = Tool();
	char* buffer = GetYDWEPath();
	T.CharAddChar(buffer, MAX_PATH, ConfigFile, strlen(ConfigFile));
	WCHAR* fileName = T.ChartoWCHAR(buffer, MAX_PATH);
	free(buffer);
	return fileName;
}

LPWSTR Path::GetWorldEditStringsFile()
{
	Tool T = Tool();
	char* buffer = GetYDWEPath();
	T.CharAddChar(buffer, MAX_PATH, WorldEditStrings, strlen(WorldEditStrings));
	WCHAR* fileName = T.ChartoWCHAR(buffer, MAX_PATH);
	free(buffer);
	return fileName;
}

LPSTR Path::GetWorldEditStringsFileLPSTR()
{
	Tool T = Tool();
	LPSTR buffer = GetYDWEPath();
	T.CharAddChar(buffer, MAX_PATH, WorldEditStrings, strlen(WorldEditStrings));
	return buffer;
}
