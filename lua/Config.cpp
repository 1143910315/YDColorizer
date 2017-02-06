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
	language = GetPrivateProfileIntW(globalSet, //����
		languageSet, //����
		0, //û�ҵ�����ʱ��ȱʡ����ֵ
		fileName); //�����ļ���׼ȷ·��
	free(fileName); 
	free(buffer);
	//char str[10];
	//sprintf(str, "%d", language);
	//MessageBox(NULL, T.ChartoWCHAR(str, 10), TEXT("World"), MB_OK);
}
