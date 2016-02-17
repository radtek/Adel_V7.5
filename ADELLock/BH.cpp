#include "stdafx.h"
//#include <stdio.h>
#include <string.h>


char* _GetBH_Form_RoomNumber(char Room[])
{
	char s[255][20] = { 0 };//存储文件中的字符数组
	char a[255][20] = { 0 };//房号
	char b[255][20] = { 0 };//对应的编号
	int i = 0;
	FILE* fp;
	char* bh = NULL;
	//fp = fopen("D:\\Beyond.ini","r");
	//fopen_s(&fp, "D:\\Bzhang\\SDK\\LockID.ini", "r");
	fopen_s(&fp, "C:\\Windows\\system\\LOCKID.INI", "r");
	for (; i<255; i++)
	{
		fscanf_s(fp, "%s", s[i], 12);
		//printf("s[%d] : %s\n", i, s[i]);

		//sscanf_s(s[i],"%4s",a[i],16);//将数组s[i]中的前四位给数组a[i];法一：
		sscanf_s(s[i], "%[^=]", a[i], 16);//将数组s[i]中的前四位给数组a[i];法二:

		//过滤掉第一个是"1001="字符串，截取后面的10位
		sscanf_s(s[i], "%*5s%s", b[i], 12);//将数组s[i]中的后10位给数组b[i]:
	}
	i = 0;
	while (i<255)
	{
		if (strcmp(Room, a[i]) == 0)
		{
			//printf_s("编号 ： %s\n", b[i]);
			bh = b[i];
			return bh;
		}
		i++;
	}
	if (i >= 255 || i<0)
	{
		return NULL;
	}
	return NULL;
}


char* _GetRoomnumber_From_BH(char BH[])
{
	char s[255][20] = { 0 };//存储文件中的字符数组
	char a[255][20] = { 0 };//房号
	char b[255][20] = { 0 };//对应的编号
	int i = 0;
	FILE* fp;
	char* aa = NULL;
	//fp = fopen("D:\\Beyond.ini","r");
	/*fopen_s(&fp, "D:\\Bzhang\\SDK\\LockID.ini", "r");*/
	fopen_s(&fp, "C:\\Windows\\system\\LOCKID.INI", "r");
	for (; i<255; i++)
	{
		fscanf_s(fp, "%s", s[i], 16);
		//printf("s[%d] : %s\n", i, s[i]);
		//sscanf_s(s[i],"%4s",a[i],16);//将数组s[i]中的前四位给数组a[i];法一：

		sscanf_s(s[i], "%[^=]", a[i], 16);//将数组s[i]中的前四位给数组a[i];法二:

		/*if (atoi(a[i]) == 0) 
			continue;*/
											//过滤掉第一个是"1001="字符串，截取后面的10位
		sscanf_s(s[i], "%*5s%s", b[i], 16);//将数组s[i]中的后10位给数组a[i]:
		//printf_s("b[%d] = %s\n", i, b[i]);
	}
	i = 0;
	while (i<255)
	{
		if (strcmp(BH, b[i]) == 0)
		{
			//printf_s("编号 ： %s\n", a[i]);
			aa = a[i];
			return aa;
		}
		i++;
	}
	if (i >= 255 || i<0)
	{
		return NULL;
	}
	return NULL;
}