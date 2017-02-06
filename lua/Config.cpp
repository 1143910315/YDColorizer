#include "Config.h"
#include "Path.h"
#include "Tool.h"
#include <stdio.h>
Config::Config()
{
	char*buffer = Path().GetPath();
	Tool T = Tool();
	T.CharAddChar(buffer, MAX_PATH, fileSet, strlen(fileSet));
	WCHAR* fileName = T.ChartoWCHAR(buffer, MAX_PATH);
	language = GetPrivateProfileIntW(globalSet, //节名
		languageSet, //项名
		0, //没找到此项时的缺省返回值
		fileName); //配置文件的准确路径
	free(fileName); 
	free(buffer);
	//char str[10];
	//sprintf(str, "%d", language);
	//MessageBox(NULL, T.ChartoWCHAR(str, 10), TEXT("World"), MB_OK);
}
