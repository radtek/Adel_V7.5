#pragma once
#include <iostream>
#include <vector>

using namespace std;

typedef struct tagADEL_CARD
{
	char room[16]; //- 房号，6～8 chars, 如：1-1-41
	char gate[16]; //- 子房号, 1 char, 如:0
	char stime[32]; // - 时间, 10 char * 2, 如：14 01 23 18 25， 14 01 24 13 00
	char beginTime[16]; // 开始时间
	char endTime[16]; // 结束时间
	char guestname[32]; // - 无用，与Adel保持一致
	char guestid[32]; // - 无用，与Adel保持一致
	char sIDnum[16];//作业流水号
	union
	{
		long lVal;
		UINT nVal;
		BYTE bytes[4];
	} cardSn;  // 内部卡号, int
} ADEL_CARD, *LPADEL_CARD;
class CControlBase
{
public:
	CControlBase();
	virtual ~CControlBase();

// - 内部成员变量
protected:
	BOOL m_bInited; // - 是否已经初始化

// - 内部方法
protected:
	void GetErrMsg(int nCode);

// - 公开成员变量
public:
	int m_nRet; // - 返回值
	char m_szMsg[128]; // - 错误信息
	ADEL_CARD m_card; // - 卡内信息

// - 公开方法
	BOOL IsInited() const { return m_bInited; }
	int PB_Init(int nSoftware, char *szServer, char *szUserName, int nPort, int nEncoder, int nTMEncoder); // - 初始化
	int PB_EndSession(); // - 关闭， 暂为空
	int CControlBase::PB_NewKey(BOOL bDupKey);
	//int PB_NewKey(BOOL bDupKey, char * room, char * stime, char * guestname, char * guestid); // - 发卡
	int PB_ReadCard(); // - 读卡
	int PB_EraseCard(); // - 注销卡
	int PB_ReaderBeep(int nSound); // - 蜂鸣

	//void ChangeOfTime(char* buff, char* TimeofLength);//时间以小时转换
	
};

// - 工具方法
long Get_the_parameter(char str_parameter[]);