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
	case  0: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "0-操作成功"); break;
	case  1: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "1-读写错误/数据错误"); break;
	case  2: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "2-卡已损坏"); break;
	case  3: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "3-无卡"); break;
	case  4: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "4-串口错误"); break;
	case  5: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "5-卡被更换"); break;
	case  6: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "6-不是新卡"); break;
	case  7: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "7-卡是新卡"); break;
	case  8: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "8-非本系统卡"); break;
	case  9: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "9-不是客人卡"); break;
	case 10: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "10-不是会员卡"); break;
	case 11: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "11-密码错误"); break;
	case 12: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "12-无开门记录"); break;
	case 13: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "13-卡型不正确"); break;
	case 14: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "14-参数错误"); break;
	case 15: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "15-用户取消操作(按下<ESC>键)"); break;
	case 16: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "16-等待超时"); break;
	case 17: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "17-插卡错误"); break;
	case 18: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "18-卡是空白卡或插卡错误"); break;
	case 19: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "19-保留(为向前兼容)"); break;
	case 20: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "20-没有调用Init函数"); break;
	case 21: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "21-不支持该版本的门锁软件"); break;
	case 22: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "22-连接(门锁系统数据库)错误"); break;
	case 23: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "23-门锁系统参数不存在"); break;
	case 24: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "24-初始化失败"); break;
	case 25: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "25-没有客人在住/指定客人不存在"); break;
	case 26: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "26-客房已满"); break;
	case 27: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "27-没有此卡记录"); break;
	case 28: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "28-没有调用SetPort函数"); break;
	case 29: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "29-无效的客房房号"); break;
	case 30: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "30-错误的时间范围"); break;
	case 31: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "31-卡号已存在，无法登记（Lock9200）"); break;
	case 32: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "32-不支持调用"); break;
	case 33: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "33-无效的授权码，授权码错误或过期"); break;
	case 34: strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "34-读取配置文件失败"); break;
	default: sprintf_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "%ld-未知错误", nCode); break;
	}
};

int CControlBase::PB_Init(int nSoftware, char *szServer, char *szUserName, int nPort, int nEncoder, int nTMEncoder)
{ 
	if (g_ADELFuncs.pInit == NULL)
	{
		strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "未能成功加载动态链接库(MainDll.dll)");
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
		strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "未能成功加载动态链接库(MainDll.dll)");
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
		strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "未能成功加载动态链接库(MainDll.dll)");
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
		strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "未能成功加载动态链接库(MainDll.dll)");
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
	strcpy_s(gate, 8, "00"); //默认授权通道；
	if (g_ADELFuncs.pNewKey == NULL || g_ADELFuncs.pDupKey == NULL)
	{
		strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "未能成功加载动态链接库(MainDll.dll)");
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
		strcpy_s(this->m_szMsg, _ARRAYSIZE(this->m_szMsg), "未能成功加载动态链接库(MainDll.dll)");
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

