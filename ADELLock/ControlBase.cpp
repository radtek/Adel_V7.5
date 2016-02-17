#pragma once
#include "stdafx.h"
#include "ControlBase.h"
#include "funcPtrs.h"

extern ADEL_FUNCS g_ADELFuncs;

CControlBase::CControlBase() :m_nRet(0), m_bInited(false)
{
	memset(this->m_szMsg, 0, sizeof(this->m_szMsg));
	memset(&this->m_card, 0, sizeof(ADEL_CARD));
}

CControlBase::~CControlBase()
{
	this->m_bInited = false;
}

void CControlBase::GetErrMsg(int nCode)
{
	switch (nCode)
	{
	case  0: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "0-�����ɹ�"); break;
	case  1: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "1-��д����/���ݴ���"); break;
	case  2: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "2-������"); break;
	case  3: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "3-�޿�"); break;
	case  4: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "4-���ڴ���"); break;
	case  5: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "5-��������"); break;
	case  6: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "6-�����¿�"); break;
	case  7: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "7-�����¿�"); break;
	case  8: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "8-�Ǳ�ϵͳ��"); break;
	case  9: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "9-���ǿ��˿�"); break;
	case 10: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "10-���ǻ�Ա��"); break;
	case 11: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "11-�������"); break;
	case 12: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "12-�޿��ż�¼"); break;
	case 13: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "13-���Ͳ���ȷ"); break;
	case 14: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "14-��������"); break;
	case 15: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "15-�û�ȡ������(����<ESC>��)"); break;
	case 16: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "16-�ȴ���ʱ"); break;
	case 17: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "17-�忨����"); break;
	case 18: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "18-���ǿհ׿���忨����"); break;
	case 19: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "19-����(Ϊ��ǰ����)"); break;
	case 20: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "20-û�е���Init����"); break;
	case 21: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "21-��֧�ָð汾���������"); break;
	case 22: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "22-����(����ϵͳ���ݿ�)����"); break;
	case 23: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "23-����ϵͳ����������"); break;
	case 24: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "24-��ʼ��ʧ��"); break;
	case 25: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "25-û�п�����ס/ָ�����˲�����"); break;
	case 26: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "26-�ͷ�����"); break;
	case 27: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "27-û�д˿���¼"); break;
	case 28: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "28-û�е���SetPort����"); break;
	case 29: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "29-��Ч�Ŀͷ�����"); break;
	case 30: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "30-�����ʱ�䷶Χ"); break;
	case 31: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "31-�����Ѵ��ڣ��޷��Ǽǣ�Lock9200��"); break;
	case 32: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "32-��֧�ֵ���"); break;
	case 33: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "33-��Ч����Ȩ�룬��Ȩ���������"); break;
	case 34: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "34-��ȡ�����ļ�ʧ��"); break;
	default: sprintf_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "%ld-δ֪����", nCode); break;
	}
};

int CControlBase::PB_Init(int nSoftware, char *szServer, char *szUserName, int nPort, int nEncoder, int nTMEncoder)
{ 
	if (g_ADELFuncs.pInit == NULL)
	{
		strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "δ�ܳɹ����ض�̬���ӿ�(MainDll.dll)");
		this->m_nRet = 1001;
		return this->m_nRet;
	}
	WCHAR section[10];
	WCHAR option1[20];
	WCHAR option2[255];
	WCHAR option3[20];
	WCHAR option4[20];
	WCHAR option5[20];
	WCHAR Server[255];
	WCHAR path[100];

	char server[255] = { 0 };

	MultiByteToWideChar(CP_ACP, 0, "Setting", -1, section, sizeof(section) / sizeof(section[0]));
	MultiByteToWideChar(CP_ACP, 0, "software", -1, option1, sizeof(option1) / sizeof(option1[0]));
	MultiByteToWideChar(CP_ACP, 0, "server", -1, option2, sizeof(option2) / sizeof(option2[0]));
	MultiByteToWideChar(CP_ACP, 0, "Port", -1, option3, sizeof(option3) / sizeof(option3[0]));
	MultiByteToWideChar(CP_ACP, 0, "Encoder", -1, option4, sizeof(option4) / sizeof(option4[0]));
	MultiByteToWideChar(CP_ACP, 0, "TMEncoder", -1, option5, sizeof(option5) / sizeof(option5[0]));
	MultiByteToWideChar(CP_ACP, 0, "C:\\Windows\\system\\BeyondhLockSetting.ini", -1, path, sizeof(path) / sizeof(path[0]));

	int software = GetPrivateProfileIntW(section, option1, 256, path);
	int Port = GetPrivateProfileIntW(section, option3, 256, path);
	int Encoder = GetPrivateProfileIntW(section, option4, 256, path);
	int TMEncoder = GetPrivateProfileIntW(section, option5, 256, path);

	GetPrivateProfileStringW(section, option2, nullptr, Server, 255, path);
	WideCharToMultiByte(CP_OEMCP, NULL, Server, -1, server, 255, NULL, FALSE);

	if (software == 256 || Port == 256 || Encoder == 256 || TMEncoder == 256)
	{
		this->m_nRet = 34;
		this->GetErrMsg(this->m_nRet);
		return this->m_nRet;
	}
	this->m_nRet = g_ADELFuncs.pInit(software, server, "LocalSystem", Port, Encoder, TMEncoder);
	if (this->m_nRet == 0)
		this->m_bInited = TRUE;

	this->GetErrMsg(this->m_nRet);
	return this->m_nRet;
}

int CControlBase::PB_EndSession()
{
	if (g_ADELFuncs.pEndSession == NULL)
	{
		strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "δ�ܳɹ����ض�̬���ӿ�(MainDll.dll)");
		this->m_nRet = 1001;
		return this->m_nRet;
	}
	this->m_nRet = g_ADELFuncs.pEndSession();
	this->GetErrMsg(this->m_nRet);

	if (this->m_nRet == 0)
		this->m_bInited = FALSE;

	return this->m_nRet;
}

int CControlBase::PB_ReaderBeep(int nSound)
{
	if (g_ADELFuncs.pReaderBeep == NULL)
	{
		strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "δ�ܳɹ����ض�̬���ӿ�(MainDll.dll)");
		this->m_nRet = 1001;
		return this->m_nRet;
	}
	this->m_nRet = g_ADELFuncs.pReaderBeep(nSound);
	this->GetErrMsg(this->m_nRet);
	return this->m_nRet;
}

int CControlBase::PB_ReadCard()
{
	if (g_ADELFuncs.pReadCard == NULL)
	{
		strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "δ�ܳɹ����ض�̬���ӿ�(MainDll.dll)");
		this->m_nRet = 1001;
		return this->m_nRet;
	}

	char lift[20] = { 0 };
	int Breakfast;
	int st;
	this->m_nRet = g_ADELFuncs.pReadCard(this->m_card.room,
		this->m_card.gate,
		this->m_card.stime,
		this->m_card.guestname,
		this->m_card.guestid,
		lift,
		NULL,
		NULL,
		&this->m_card.cardSn.lVal,
		&st,
		&Breakfast);

	this->GetErrMsg(this->m_nRet);
	return this->m_nRet;
}

int CControlBase::PB_NewKey(BOOL bDupKey)
{
	char gate[8];
	strcpy_s(gate, 8, "00"); //Ĭ����Ȩͨ����
	if (g_ADELFuncs.pNewKey == NULL || g_ADELFuncs.pDupKey == NULL)
	{
		strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "δ�ܳɹ����ض�̬���ӿ�(MainDll.dll)");
		this->m_nRet = 1001;
		return this->m_nRet;
	}

	int Breakfast = 0;
	char lift[20];
	strcpy_s(lift, 20, "00");
	//this->m_card.cardSn.lVal = atoi(this->m_card.room);
	if (bDupKey)
	{
		this->m_nRet = g_ADELFuncs.pDupKey(
			this->m_card.room,
			this->m_card.gate,
			this->m_card.stime,
			this->m_card.guestname,
			this->m_card.guestid,
			lift,
			1,
			Breakfast,
			&this->m_card.cardSn.lVal, NULL, NULL);
	}
	else
	{
		this->m_nRet = g_ADELFuncs.pNewKey(
			this->m_card.room,
			this->m_card.gate,
			this->m_card.stime,
			this->m_card.guestname,
			this->m_card.guestid,
			lift,
			1,
			Breakfast,
			&this->m_card.cardSn.lVal, NULL, NULL);
	}

	this->GetErrMsg(this->m_nRet);
	return this->m_nRet;
}

int CControlBase::PB_EraseCard()							
{
	if (g_ADELFuncs.pEraseCard == NULL || g_ADELFuncs.pReadCard == NULL)
	{
		strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "δ�ܳɹ����ض�̬���ӿ�(MainDll.dll)");
		this->m_nRet = 1001;
		return this->m_nRet;
	}

	char lift[20] = { 0 };
	int Breakfast;
	int st;
	this->m_nRet = g_ADELFuncs.pReadCard(this->m_card.room,
		this->m_card.gate,
		this->m_card.stime,
		this->m_card.guestname,
		this->m_card.guestid,
		lift,
		NULL,
		NULL,
		&this->m_card.cardSn.lVal,
		&st,
		&Breakfast);

	this->m_nRet = g_ADELFuncs.pEraseCard(this->m_card.cardSn.lVal, NULL, NULL);
	this->GetErrMsg(this->m_nRet);
	return this->m_nRet;
}

