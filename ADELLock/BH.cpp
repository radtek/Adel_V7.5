#include "stdafx.h"
//#include <stdio.h>
#include <string.h>


char* _GetBH_Form_RoomNumber(char Room[])
{
	char s[255][20] = { 0 };//�洢�ļ��е��ַ�����
	char a[255][20] = { 0 };//����
	char b[255][20] = { 0 };//��Ӧ�ı��
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

		//sscanf_s(s[i],"%4s",a[i],16);//������s[i]�е�ǰ��λ������a[i];��һ��
		sscanf_s(s[i], "%[^=]", a[i], 16);//������s[i]�е�ǰ��λ������a[i];����:

		//���˵���һ����"1001="�ַ�������ȡ�����10λ
		sscanf_s(s[i], "%*5s%s", b[i], 12);//������s[i]�еĺ�10λ������b[i]:
	}
	i = 0;
	while (i<255)
	{
		if (strcmp(Room, a[i]) == 0)
		{
			//printf_s("��� �� %s\n", b[i]);
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
	char s[255][20] = { 0 };//�洢�ļ��е��ַ�����
	char a[255][20] = { 0 };//����
	char b[255][20] = { 0 };//��Ӧ�ı��
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
		//sscanf_s(s[i],"%4s",a[i],16);//������s[i]�е�ǰ��λ������a[i];��һ��

		sscanf_s(s[i], "%[^=]", a[i], 16);//������s[i]�е�ǰ��λ������a[i];����:

		/*if (atoi(a[i]) == 0) 
			continue;*/
											//���˵���һ����"1001="�ַ�������ȡ�����10λ
		sscanf_s(s[i], "%*5s%s", b[i], 16);//������s[i]�еĺ�10λ������a[i]:
		//printf_s("b[%d] = %s\n", i, b[i]);
	}
	i = 0;
	while (i<255)
	{
		if (strcmp(BH, b[i]) == 0)
		{
			//printf_s("��� �� %s\n", a[i]);
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