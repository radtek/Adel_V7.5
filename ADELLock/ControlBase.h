#pragma once
#include <iostream>
#include <vector>

using namespace std;

typedef struct tagADEL_CARD
{
	char room[16]; //- ���ţ�6��8 chars, �磺1-1-41
	char gate[16]; //- �ӷ���, 1 char, ��:0
	char stime[32]; // - ʱ��, 10 char * 2, �磺14 01 23 18 25�� 14 01 24 13 00
	char beginTime[16]; // ��ʼʱ��
	char endTime[16]; // ����ʱ��
	char guestname[32]; // - ���ã���Adel����һ��
	char guestid[32]; // - ���ã���Adel����һ��
	char sIDnum[16];//��ҵ��ˮ��
	union
	{
		long lVal;
		UINT nVal;
		BYTE bytes[4];
	} cardSn;  // �ڲ�����, int
} ADEL_CARD, *LPADEL_CARD;
class CControlBase
{
public:
	CControlBase();
	virtual ~CControlBase();

// - �ڲ���Ա����
protected:
	BOOL m_bInited; // - �Ƿ��Ѿ���ʼ��

// - �ڲ�����
protected:
	void GetErrMsg(int nCode);

// - ������Ա����
public:
	int m_nRet; // - ����ֵ
	char m_szMsg[128]; // - ������Ϣ
	ADEL_CARD m_card; // - ������Ϣ

// - ��������
	BOOL IsInited() const { return m_bInited; }
	int PB_Init(int nSoftware, char *szServer, char *szUserName, int nPort, int nEncoder, int nTMEncoder); // - ��ʼ��
	int PB_EndSession(); // - �رգ� ��Ϊ��
	int CControlBase::PB_NewKey(BOOL bDupKey);
	//int PB_NewKey(BOOL bDupKey, char * room, char * stime, char * guestname, char * guestid); // - ����
	int PB_ReadCard(); // - ����
	int PB_EraseCard(); // - ע����
	int PB_ReaderBeep(int nSound); // - ����

	//void ChangeOfTime(char* buff, char* TimeofLength);//ʱ����Сʱת��
	
};

// - ���߷���
long Get_the_parameter(char str_parameter[]);