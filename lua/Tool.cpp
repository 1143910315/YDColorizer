#include "Tool.h"
bool Tool::CharAddChar(char* target, int targetSize, const char* source, int sourceSize)
{
	for (int i = 0; i < targetSize; i++) {
		if (target[i] == '\0') {
			int j = 0;
			for (; i < targetSize - 1 && j < sourceSize; i++, j++) {
				target[i] = source[j];
			}
			target[i] = '\0';//×Ö·û´®ÊÕÎ²¡£
			if (j == sourceSize) {
				return true;
			}
			break;
		}
	}
	return false;
}

bool Tool::ChartoWCHAR(WCHAR* target, int targetSize, const char* source, int sourceSize)
{
	int need = MultiByteToWideChar(CP_ACP, 0, source, sourceSize, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, source, sourceSize, target, targetSize);
	if (need <= targetSize)
	{
		return true;
	}
	return false;
}

WCHAR* Tool::ChartoWCHAR(const char * source, int sourceSize)
{
	int need = MultiByteToWideChar(CP_ACP, 0, source, sourceSize, NULL, 0);
	WCHAR* target = (WCHAR*)malloc(need * sizeof(WCHAR));
	MultiByteToWideChar(CP_ACP, 0, source, sourceSize, target, need);
	return target;
}
