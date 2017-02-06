#include "Tool.h"
bool Tool::CharAddChar(char* target, int targetSize, const char* source, int sourceSize)
{
	for (int i = 0; i < targetSize; i++) {
		if (target[i] == '\0') {
			int j = 0;
			for (; i < targetSize - 1 && j < sourceSize; i++, j++) {
				target[i] = source[j];
			}
			target[i] = '\0';//保证字符串收尾。
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
/*************************************************
Function:         |ChartoWCHAR
Description:      |将字节数组转化为宽字符数组
Input:            |source     ： 欲被转化的字节数组
                   sourceSize ： 字节数组容量（非占用空间）
Return:           |WCHAR数组的指针
Others:           |source如果不以'\0'结尾可能导致返回的数组同样没有'\0'结尾
                   此方法比另一重载更加安全可靠，返回的WCHAR数组大小也是刚好足够的，缺点就是没有返回WCHAR数组的大小
*************************************************/
WCHAR* Tool::ChartoWCHAR(const char * source, int sourceSize)
{
	int need = MultiByteToWideChar(CP_ACP, 0, source, sourceSize, NULL, 0);
	WCHAR* target = (WCHAR*)malloc(need * sizeof(WCHAR));
	MultiByteToWideChar(CP_ACP, 0, source, sourceSize, target, need);
	return target;
}