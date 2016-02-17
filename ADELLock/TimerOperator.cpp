#include "stdafx.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
/*****************************************************************************
* ��Ȩ����(C) 2006, ZTE Corp. WiMAX
*----------------------------------------------------------------------------
* ģ �� �� : BSPCommon
* �ļ����� : str2time.c
* �ļ���ʶ : {[N/A]}
* ����ժҪ : ���ַ���ת��Ϊʱ��
* ע������ :
* ��    �� : ������
* �������� : 2008-12-27
* ��ǰ�汾 : Ver1.0
*----------------------------------------------------------------------------
* �����¼ :
*
* $��¼1
* �� �� ��: $0000000(N/A)
* �� �� ��: ������
* �޸��մ�: 2008-12-27 10:54:17
* ���˵��: �����ļ�
*
*----------------------------------------------------------------------------
*/

/* ���ļ���Ҫ������ⲿ����ֻ�� struct tm ����ṹ, ���Ķ�������:
*  struct tm
*  	{
*  	int tm_sec;	    // seconds after the minute	- [0, 59]
*  	int tm_min;	    // minutes after the hour	- [0, 59]
*  	int tm_hour;    // hours after midnight		- [0, 23]
*  	int tm_mday;    // day of the month		    - [1, 31]
*  	int tm_mon;	    // months since January		- [0, 11]
*  	int tm_year;	// years since 1900
*  	int tm_wday;	// days since Sunday		- [0, 6]
*  	int tm_yday;	// days since January 1		- [0, 365]
*  	int tm_isdst;	// Daylight Saving Time flag
*  	};
*
* ����������ṹ��, ֻ��������ʱ����6����Ҫ��Ԫ��, ���������ֿ��Լ���õ�.
* ��Ϊ�ṹ�������1900�꿪ʼ, ��ת�����ͳһ����ֻ�ܴﵽ136��, ����Ŀǰ�ܹ�ʶ��
* �����޷�Χ����1900~2036��֮��.
* ���ļ��ṩ���ַ���ת����Ŀǰֻ֧�ֳ�������Ӣ�ĸ�ʽ, ����������, ʱ����,
* ͨ�����ܹ�ֱ�۶��������ڶ���, ����Ӧ�ö�����ʶ��, ����:
*  sep 3, 1995, 20:30      -> 1995-09-03 20:30:00
*  3sep97                  -> 1997-09-03 00:00:00
*  oct 4,03                -> 2003-10-04 00:00:00
*  mon dec 29, 2008        -> 2008-12-29 00:00:00
*  2011 nov 11, 11:11:11   -> 2011-11-11 11:11:11
*  10:00am, 2008/9/1       -> 2008-09-01 10:00:00
*  10/01/1976 3:01:05pm    -> 1976-10-01 15:01:05
* ���������������, ���� 01/02/03, ���Ľ������·�����, �������,
* �������ݵĸ�ʽ��������� 2003��1��2��.
*
* �������ʶ��һ������������ɵ����ڸ�ʽ, ������ʱ�������ʹ����λʮ��������ʾ.
*
* ��������������������, ��������strtotimeTest()�������м��. ����ֲ��PC������ʱ
* ֻҪ����Ϊmain()�������ɱ�������(�����stdio.hͷ�ļ�). ����@2008-12-29
*
*/

#define EOS				'\0'
#define TOKEN_INIT      0
#define TOKEN_VAL       1
#define TOKEN_SEC       2
#define TOKEN_MIN       3
#define TOKEN_HOUR      4
#define TOKEN_HALFDAY   5
#define TOKEN_DAY       6
#define TOKEN_MONTH     7
#define TOKEN_YEAR      8
#define TOKEN_WEEKDAY   9

#define STEP_INIT       0
#define STEP_DATE       1
#define STEP_TIME       2
#define STEP_OVER       3

#define FLAG_SEC        0x0001
#define FLAG_MIN        0x0002
#define FLAG_HOUR       0x0004
#define FLAG_HALFDAY    0x0008
#define FLAG_DAY        0x0010
#define FLAG_MONTH      0x0020
#define FLAG_YEAR       0x0040
#define FLAG_TIME       0x0100
#define FLAG_DATE       0x0200
#define FLAG_ALPHA      0x1000

static char s_cWeekDay[] = "MonTueWedThuFriSatSun";
static char s_cWeekDayU[] = "MONTUEWEDTHUFRISATSUN";
static char s_cWeekDayL[] = "montuewedthufrisatsun";
static char s_cMonth[] = "JanFebMarAprMayJunJulAugSepOctNovDec";
static char s_cMonthU[] = "JANFEBMARAPRMAYJUNJULAUTSEPOCTNOVDEC";
static char s_cMonthL[] = "janfebmaraprmayjunjulaugsepoctnovdec";
static int  s_iMonthFix[] = { 2, 0, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2 };

#define IsTimeDelim(a)  ((a) == ':')
#define IsDateDelim(a)  (isspace(a) || (a) == ',' || (a) == '.' || \
	(a) == '-' || (a) == '/' || (a) == '\\')
#define LeapYear(year)  (((year) % 400 == 0) || \
	(((year) % 100 != 0) && ((year) % 4 == 0)))

/*****************************************************************************
*  ��������   : nextTimeToken(*)
*  ��������   : �ҵ���һ��ʱ����
*  ��ȫ�ֱ��� : ��
*  дȫ�ֱ��� : ��
*  �������   : timeStr    - ʱ�������ַ���
*  �������   : pVal       - ��ǿ���ת���������ռ�ʱ��Ķ���ֵ
pFlag      - ���ͱ��, ����������������, ���������ٵ�ֵ
*  �� �� ֵ   : ���������ַ�����, ʧ��ʱ����0
*  ����˵��   : �ڲ�����, Ҫ�����ָ�����ǿ�
*---------------------------------------------------------------------------
* ��ʷ��¼(�����, ������@�޸�����, ����˵��)
*  $0000000(N/A), 2008-12-27 16:14:59 ����
*----------------------------------------------------------------------------
*/
static int nextTimeToken(char *timeStr, int *pVal, int *pFlag)
{
	char    *pChar = timeStr, *pCharEnd;
	int     iFlags = 0, iTemp;

	*pFlag = TOKEN_INIT;

	/* �����ָ��� */
	while (IsTimeDelim(*pChar) || IsDateDelim(*pChar))
	{
		pChar++;
	}

	/* ����ֵ��, ֱ�ӷ�����ֵ */
	if (isdigit(*pChar))
	{
		for (*pVal = 0, pCharEnd = pChar; isdigit(*pCharEnd); pCharEnd++)
		{
			*pVal = *pVal * 10 + (*pCharEnd - '0');
		}

		/* Ӣ����ĸ���, ��ָ��Ϊday */
		if (*(pCharEnd - 1) == '1' && strncmp(pCharEnd, "st", 2) == 0)
		{
			*pFlag = TOKEN_DAY, pCharEnd += 2;
		}
		else if (*(pCharEnd - 1) == '2' && strncmp(pCharEnd, "nd", 2) == 0)
		{
			*pFlag = TOKEN_DAY, pCharEnd += 2;
		}
		else if (*(pCharEnd - 1) == '3' && strncmp(pCharEnd, "rd", 2) == 0)
		{
			*pFlag = TOKEN_DAY, pCharEnd += 2;
		}
		else if (strncmp(pCharEnd, "th", 2) == 0)
		{
			*pFlag = TOKEN_DAY, pCharEnd += 2;
		}

		if (*pFlag == TOKEN_DAY)
		{
			return pCharEnd - timeStr;
		}

#if 1   /* Ϊ���ķ���, �ɺ��� */
		/* �����ո�, �Լ�鵥λʶ��� */
		while (isspace(*pChar))
		{
			pChar++;
		}
		/* ��������, ������Ϊ��ʶ������ڱ�ʶ */
		if (strncmp(pCharEnd, "��", 2) == 0)
		{
			*pFlag = TOKEN_YEAR, pCharEnd += 2;
		}
		else if (strncmp(pCharEnd, "��", 2) == 0)
		{
			*pFlag = TOKEN_MONTH, pCharEnd += 2;
		}
		else if (strncmp(pCharEnd, "��", 2) == 0)
		{
			*pFlag = TOKEN_DAY, pCharEnd += 2;
		}
		else if (strncmp(pCharEnd, "ʱ", 2) == 0)
		{
			*pFlag = TOKEN_HOUR, pCharEnd += 2;
		}
		else if (strncmp(pCharEnd, "��", 2) == 0)
		{
			*pFlag = TOKEN_MIN, pCharEnd += 2;
		}
		else if (strncmp(pCharEnd, "��", 2) == 0)
		{
			*pFlag = TOKEN_SEC, pCharEnd += 2;
		}
		else
#endif
		{
			*pFlag = TOKEN_VAL;
		}
		return pCharEnd - timeStr;

	} /* (isdigit(*pChar)) */

	/* ������ֵ�Ҳ�����ĸ(�������, ������ʾ�ַ�), һ�㲻��֧��, ����0 */
	if (!isalpha(*pChar))
	{
		if (*pChar >= 0)
		{
			return 0;
		}
		/* ��ASCII�ַ���, ����������"����һ"֮��, ���� */
		pCharEnd = pChar;
		while (*pCharEnd != ' ' && *pCharEnd != ',' && *pCharEnd != EOS)
		{
			pCharEnd++;
		}
		return pCharEnd - timeStr;
	} /* (!isdigit(*pChar) && !isalpha(*pChar)) */

	/* ����ĸ, ����ǲ����·� */
	for (iTemp = 0; iTemp < 12; iTemp++)
	{
		if (strncmp(pChar, s_cMonth + iTemp * 3, 3) == 0)
		{
			*pVal = iTemp + 1;
			break;
		}
		else if (strncmp(pChar, s_cMonthL + iTemp * 3, 3) == 0)
		{
			*pVal = iTemp + 1;
			break;
		}
		else if (strncmp(pChar, s_cMonthU + iTemp * 3, 3) == 0)
		{
			*pVal = iTemp + 1;
			break;
		}
	} /* �·���ĸ��� */

	/* �ҵ��·���ĸ, ����β����ĸ */
	if (iTemp < 12)
	{
		pCharEnd = pChar + 3;
		while (isalpha(*pCharEnd))
		{
			pCharEnd++;
		}
		*pFlag = TOKEN_MONTH;
		return pCharEnd - timeStr;
	}

	/* δ�ҵ��·���ĸ, ����������ĸ */
	for (iTemp = 0; iTemp < 7; iTemp++)
	{
		if (strncmp(pChar, s_cWeekDay + iTemp * 3, 3) == 0)
		{
			*pVal = iTemp;
			break;
		}
		else if (strncmp(pChar, s_cWeekDayL + iTemp * 3, 3) == 0)
		{
			*pVal = iTemp;
			break;
		}
		else if (strncmp(pChar, s_cWeekDayU + iTemp * 3, 3) == 0)
		{
			*pVal = iTemp;
			break;
		}
	} /* ������ĸ��� */

	/* �ҵ�������ĸ */
	if (iTemp < 7)
	{
		pCharEnd = pChar + 3;
		while (isalpha(*pCharEnd))
		{
			pCharEnd++;
		}
		*pFlag = TOKEN_WEEKDAY;
		return pCharEnd - timeStr;
	}

	/* ��ǰ����־��� */
	if (strncmp(pChar, "am", 2) == 0 || strncmp(pChar, "AM", 2) == 0)
	{
		pCharEnd = pChar + 2;
		if (!isalpha(*pCharEnd))
		{
			*pFlag = TOKEN_HALFDAY;
			*pVal = 0;
			return pCharEnd - timeStr;
		}
	}
	if (strncmp(pChar, "pm", 2) == 0 || strncmp(pChar, "PM", 2) == 0)
	{
		pCharEnd = pChar + 2;
		if (!isalpha(*pCharEnd))
		{
			*pFlag = TOKEN_HALFDAY;
			*pVal = 1;
			return pCharEnd - timeStr;
		}
	}

	return 0;

} /* nextTimeToken() */

/*****************************************************************************
*  ��������   : digit2time(*)
*  ��������   : ����������ת��Ϊʱ��ṹ, ���밴������ʱ��������, ���򿴲���
*  ��ȫ�ֱ��� : ��
*  дȫ�ֱ��� : ��
*  �������   : timeStr    - ʱ�������ַ���
iLen       - ʱ�������ַ�������
*  �������   : ptTime     - ����ʱ��ṹ
*  �� �� ֵ   : ������ʱ������Ч�ı�־
*  ����˵��   : ����ͳ�ͻ����, �����е�����˳�����
*---------------------------------------------------------------------------
* ��ʷ��¼(�����, ������@�޸�����, ����˵��)
*  $0000000(N/A), ������@2008-12-28 10:47:31 ����
*----------------------------------------------------------------------------
*/
static int digit2time(char *timeStr, int iLen, struct tm *ptTime)
{
	char    *pChar = timeStr;

	memset(ptTime, 0, sizeof(*ptTime));

	if (iLen < 6 || iLen % 2 != 0)
	{
		return 0;
	}

	/* ���������ʱ���ʽ(������Ƶ������): 5 + 4 + 3 + 2 + 1 = 15
	��������ʱ����  - YYYYMMDDHHmmss
	������ʱ����    - YYMMDDHHmmss
	��������ʱ��    - YYYYMMDDHHmm
	����ʱ����      - MMDDHHmmss
	������ʱ��      - YYMMDDHHmm
	��������ʱ      - YYYYMMDDHH
	����ʱ��        - MMDDHHmm
	��������        - YYYYMMDD
	��ʱ����        - DDHHmmss
	������ʱ        - YYMMDDHH
	������          - YYMMDD
	������          - YYYYMM
	ʱ����          - HHmmss
	��ʱ��          - DDHHmm
	����ʱ          - MMDDHH
	*/

	/* ������ʽ, ֻ��: YYYYMMDDHHmmss */
	if (iLen >= 14)
	{
		ptTime->tm_year = (pChar[0] - '0') * 1000 + (pChar[1] - '0') * 100 +
			(pChar[2] - '0') * 10 + (pChar[3] - '0');
		ptTime->tm_mon = (pChar[4] - '0') * 10 + (pChar[5] - '0');
		ptTime->tm_mday = (pChar[6] - '0') * 10 + (pChar[7] - '0');
		ptTime->tm_hour = (pChar[8] - '0') * 10 + (pChar[9] - '0');
		ptTime->tm_min = (pChar[10] - '0') * 10 + (pChar[11] - '0');
		ptTime->tm_sec = (pChar[12] - '0') * 10 + (pChar[13] - '0');
		if (ptTime->tm_year >= 1900 && ptTime->tm_year < 2036 &&
			ptTime->tm_mon < 13 &&
			ptTime->tm_mday <= 29 + s_iMonthFix[ptTime->tm_mon - 1] &&
			ptTime->tm_hour < 24 && ptTime->tm_min < 60 && ptTime->tm_sec < 60)
		{
			return FLAG_SEC | FLAG_MIN | FLAG_HOUR |
				FLAG_DAY | FLAG_MONTH | FLAG_YEAR;
		}
	}
	/* �γ���ʽ, ��: YYYYMMDDHHmm, YYMMDDHHmmss */
	else if (iLen == 12)
	{
		/* YYYYMMDDHHmm */
		ptTime->tm_year = (pChar[0] - '0') * 1000 + (pChar[1] - '0') * 100 +
			(pChar[2] - '0') * 10 + (pChar[3] - '0');
		ptTime->tm_mon = (pChar[4] - '0') * 10 + (pChar[5] - '0');
		ptTime->tm_mday = (pChar[6] - '0') * 10 + (pChar[7] - '0');
		ptTime->tm_hour = (pChar[8] - '0') * 10 + (pChar[9] - '0');
		ptTime->tm_min = (pChar[10] - '0') * 10 + (pChar[11] - '0');
		if (ptTime->tm_year >= 1900 && ptTime->tm_year < 2036 &&
			ptTime->tm_mon < 13 &&
			ptTime->tm_mday <= 29 + s_iMonthFix[ptTime->tm_mon - 1] &&
			ptTime->tm_hour < 24 && ptTime->tm_min < 60)
		{
			return FLAG_MIN | FLAG_HOUR | FLAG_DAY | FLAG_MONTH | FLAG_YEAR;
		}
		/* YYMMDDHHmmss */
		ptTime->tm_year = (pChar[0] - '0') * 10 + (pChar[1] - '0');
		ptTime->tm_year += (ptTime->tm_year >= 70) ? 1900 : 2000;
		ptTime->tm_mon = (pChar[2] - '0') * 10 + (pChar[3] - '0');
		ptTime->tm_mday = (pChar[4] - '0') * 10 + (pChar[5] - '0');
		ptTime->tm_hour = (pChar[6] - '0') * 10 + (pChar[7] - '0');
		ptTime->tm_min = (pChar[8] - '0') * 10 + (pChar[9] - '0');
		ptTime->tm_sec = (pChar[10] - '0') * 10 + (pChar[11] - '0');
		if (ptTime->tm_year >= 1900 && ptTime->tm_year < 2036 &&
			ptTime->tm_mon < 13 &&
			ptTime->tm_mday <= 29 + s_iMonthFix[ptTime->tm_mon - 1] &&
			ptTime->tm_hour < 24 && ptTime->tm_min < 60 && ptTime->tm_sec < 60)
		{
			return FLAG_SEC | FLAG_MIN | FLAG_HOUR |
				FLAG_DAY | FLAG_MONTH | FLAG_YEAR;
		}
	} /* (iLen == 12) */
	/* 10�ֽ�, ��: MMDDHHmmss, YYMMDDHHmm, YYYYMMDDHH */
	else if (iLen == 10)
	{
		/* MMDDHHmmss */
		ptTime->tm_mon = (pChar[0] - '0') * 10 + (pChar[1] - '0');
		ptTime->tm_mday = (pChar[2] - '0') * 10 + (pChar[3] - '0');
		ptTime->tm_hour = (pChar[4] - '0') * 10 + (pChar[5] - '0');
		ptTime->tm_min = (pChar[6] - '0') * 10 + (pChar[7] - '0');
		ptTime->tm_sec = (pChar[8] - '0') * 10 + (pChar[9] - '0');
		if (ptTime->tm_mon < 13 &&
			ptTime->tm_mday <= 29 + s_iMonthFix[ptTime->tm_mon - 1] &&
			ptTime->tm_hour < 24 && ptTime->tm_min < 60 && ptTime->tm_sec < 60)
		{
			return FLAG_SEC | FLAG_MIN | FLAG_HOUR | FLAG_DAY | FLAG_MONTH;
		}
		/* YYMMDDHHmm */
		ptTime->tm_year = (pChar[0] - '0') * 10 + (pChar[1] - '0');
		ptTime->tm_year += (ptTime->tm_year >= 70) ? 1900 : 2000;
		ptTime->tm_mon = (pChar[2] - '0') * 10 + (pChar[3] - '0');
		ptTime->tm_mday = (pChar[4] - '0') * 10 + (pChar[5] - '0');
		ptTime->tm_hour = (pChar[6] - '0') * 10 + (pChar[7] - '0');
		ptTime->tm_min = (pChar[8] - '0') * 10 + (pChar[9] - '0');
		if (ptTime->tm_year >= 1900 && ptTime->tm_year < 2036 &&
			ptTime->tm_mon < 13 &&
			ptTime->tm_mday <= 29 + s_iMonthFix[ptTime->tm_mon - 1] &&
			ptTime->tm_hour < 24 && ptTime->tm_min < 60)
		{
			return FLAG_MIN | FLAG_HOUR | FLAG_DAY | FLAG_MONTH | FLAG_YEAR;
		}
		/* YYYYMMDDHH */
		ptTime->tm_year = (pChar[0] - '0') * 1000 + (pChar[1] - '0') * 100 +
			(pChar[2] - '0') * 10 + (pChar[3] - '0');
		ptTime->tm_mon = (pChar[4] - '0') * 10 + (pChar[5] - '0');
		ptTime->tm_mday = (pChar[6] - '0') * 10 + (pChar[7] - '0');
		ptTime->tm_hour = (pChar[8] - '0') * 10 + (pChar[9] - '0');
		if (ptTime->tm_hour < 24 &&
			ptTime->tm_year >= 1900 && ptTime->tm_year < 2036 &&
			ptTime->tm_mon < 13 &&
			ptTime->tm_mday <= 29 + s_iMonthFix[ptTime->tm_mon - 1])
		{
			return FLAG_HOUR | FLAG_DAY | FLAG_MONTH | FLAG_YEAR;
		}
	} /* (iLen == 10) */
	/* 8�ֽ�, ��: MMDDHHmm, YYYYMMDD, DDHHmmss, YYMMDDHH */
	else if (iLen == 8)
	{
		/* MMDDHHmm */
		ptTime->tm_mon = (pChar[0] - '0') * 10 + (pChar[1] - '0');
		ptTime->tm_mday = (pChar[2] - '0') * 10 + (pChar[3] - '0');
		ptTime->tm_hour = (pChar[4] - '0') * 10 + (pChar[5] - '0');
		ptTime->tm_min = (pChar[6] - '0') * 10 + (pChar[7] - '0');
		if (ptTime->tm_mon < 13 &&
			ptTime->tm_mday <= 29 + s_iMonthFix[ptTime->tm_mon - 1] &&
			ptTime->tm_hour < 24 && ptTime->tm_min < 60)
		{
			return FLAG_MIN | FLAG_HOUR | FLAG_DAY | FLAG_MONTH;
		}
		/* YYYYMMDD */
		ptTime->tm_year = (pChar[0] - '0') * 1000 + (pChar[1] - '0') * 100 +
			(pChar[2] - '0') * 10 + (pChar[3] - '0');
		ptTime->tm_mon = (pChar[4] - '0') * 10 + (pChar[5] - '0');
		ptTime->tm_mday = (pChar[6] - '0') * 10 + (pChar[7] - '0');
		if (ptTime->tm_year >= 1900 && ptTime->tm_year < 2036 &&
			ptTime->tm_mon < 13 &&
			ptTime->tm_mday <= 29 + s_iMonthFix[ptTime->tm_mon - 1])
		{
			return FLAG_DAY | FLAG_MONTH | FLAG_YEAR;
		}
		/* DDHHmmss */
		ptTime->tm_mday = (pChar[0] - '0') * 10 + (pChar[1] - '0');
		ptTime->tm_hour = (pChar[2] - '0') * 10 + (pChar[3] - '0');
		ptTime->tm_min = (pChar[4] - '0') * 10 + (pChar[5] - '0');
		ptTime->tm_sec = (pChar[6] - '0') * 10 + (pChar[7] - '0');
		if (ptTime->tm_mday <= 31 && ptTime->tm_hour < 24 &&
			ptTime->tm_min < 60 && ptTime->tm_sec < 60)
		{
			return FLAG_SEC | FLAG_MIN | FLAG_HOUR | FLAG_DAY;
		}
		/* YYMMDDHH */
		ptTime->tm_year = (pChar[0] - '0') * 10 + (pChar[1] - '0');
		ptTime->tm_year += (ptTime->tm_year >= 70) ? 1900 : 2000;
		ptTime->tm_mon = (pChar[2] - '0') * 10 + (pChar[3] - '0');
		ptTime->tm_mday = (pChar[4] - '0') * 10 + (pChar[5] - '0');
		ptTime->tm_hour = (pChar[6] - '0') * 10 + (pChar[7] - '0');
		if (ptTime->tm_hour < 24 &&
			ptTime->tm_year >= 1900 && ptTime->tm_year < 2036 &&
			ptTime->tm_mon < 13 &&
			ptTime->tm_mday <= 29 + s_iMonthFix[ptTime->tm_mon - 1])
		{
			return FLAG_HOUR | FLAG_DAY | FLAG_MONTH | FLAG_YEAR;
		}
	} /* (iLen == 8) */
	else
	{
		/* YYMMDD */
		ptTime->tm_year = (pChar[0] - '0') * 10 + (pChar[1] - '0');
		ptTime->tm_year += (ptTime->tm_year >= 70) ? 1900 : 2000;
		ptTime->tm_mon = (pChar[2] - '0') * 10 + (pChar[3] - '0');
		ptTime->tm_mday = (pChar[4] - '0') * 10 + (pChar[5] - '0');
		if (ptTime->tm_year >= 1900 && ptTime->tm_year < 2036 &&
			ptTime->tm_mon < 13 &&
			ptTime->tm_mday <= 29 + s_iMonthFix[ptTime->tm_mon - 1])
		{
			return FLAG_DAY | FLAG_MONTH | FLAG_YEAR;
		}
		/* YYYYMM */
		ptTime->tm_year = (pChar[0] - '0') * 1000 + (pChar[1] - '0') * 100 +
			(pChar[2] - '0') * 10 + (pChar[3] - '0');
		ptTime->tm_mon = (pChar[4] - '0') * 10 + (pChar[5] - '0');
		if (ptTime->tm_year >= 1900 && ptTime->tm_year < 2036 &&
			ptTime->tm_mon < 13)
		{
			return FLAG_MONTH | FLAG_YEAR;
		}
		/* HHmmss */
		ptTime->tm_hour = (pChar[0] - '0') * 10 + (pChar[1] - '0');
		ptTime->tm_min = (pChar[2] - '0') * 10 + (pChar[3] - '0');
		ptTime->tm_sec = (pChar[4] - '0') * 10 + (pChar[5] - '0');
		if (ptTime->tm_hour < 24 && ptTime->tm_min < 60 && ptTime->tm_sec < 60)
		{
			return FLAG_SEC | FLAG_MIN | FLAG_HOUR;
		}
		/* DDHHmm */
		ptTime->tm_mday = (pChar[0] - '0') * 10 + (pChar[1] - '0');
		ptTime->tm_hour = (pChar[2] - '0') * 10 + (pChar[3] - '0');
		ptTime->tm_min = (pChar[4] - '0') * 10 + (pChar[5] - '0');
		if (ptTime->tm_mday <= 31 && ptTime->tm_hour < 24 && ptTime->tm_min < 60)
		{
			return FLAG_MIN | FLAG_HOUR | FLAG_DAY;
		}
		/* MMDDHH */
		ptTime->tm_mon = (pChar[0] - '0') * 10 + (pChar[1] - '0');
		ptTime->tm_mday = (pChar[2] - '0') * 10 + (pChar[3] - '0');
		ptTime->tm_hour = (pChar[4] - '0') * 10 + (pChar[5] - '0');
		if (ptTime->tm_mon < 13 &&
			ptTime->tm_mday <= 29 + s_iMonthFix[ptTime->tm_mon - 1] &&
			ptTime->tm_hour < 24)
		{
			return FLAG_HOUR | FLAG_DAY | FLAG_MONTH;
		}
	} /* (iLen == 6) */

	return 0;
} /* digit2time() */

/*****************************************************************************
*  ��������   : strtotime(*)
*  ��������   : �����ڼ�(��)ʱ���ַ���ת��Ϊʱ��ṹ, ��: Dec 19 2008, 13:35:40
*  ��ȫ�ֱ��� : ��
*  дȫ�ֱ��� : ��
*  �������   : timeStr    - ʱ�������ַ���
*  �������   : ptTime     - ����ʱ��ṹ
*  �� �� ֵ   : ������ʱ������Ч�ı�־
*  ����˵��   : ʱ����֮�����ʹ��ð��":"�ָ�, ���ұ�Ȼ�Ǵ�˳��
*---------------------------------------------------------------------------
* ��ʷ��¼(�����, ������@�޸�����, ����˵��)
*  $0000000(N/A), ������@2008-12-27 16:14:59 ����
*----------------------------------------------------------------------------
*/
static int strtotime(char *timeStr, struct tm *ptTime)
{
 	int     iFlags, iVal, iLen, iStep, iDateTimeFlag;
	int     iYear, iMonth, iDay, iHour, iMinute, iSecond;
	char    *pChar = timeStr, *pCharEnd = timeStr, tempStr[8];

	iDateTimeFlag = iYear = iMonth = iDay = iHour = iMinute = iSecond = 0;
	memset(ptTime, 0, sizeof(*ptTime));

	/* ����ǰ���ո� */
	while (*pChar == ' ' || *pChar == '\t')
	{
		pChar++;
	}

	/* �����ڿɽ������м��ַ��� */
	if ((iLen = nextTimeToken(pChar, &iVal, &iFlags)) <= 0)
	{
		return iDateTimeFlag;
	}

	/* ��ֵ���ҳ��ȴ��ڵ���6, ��Ϊȫ����������ʱ��, ��20081229080306
	* ��Ҫ���½��� */
	if (iFlags == TOKEN_VAL && iLen >= 6 && iLen % 2 == 0)
	{
		iDateTimeFlag = digit2time(pChar, iLen, ptTime);
		if (iDateTimeFlag == 0)
		{
			memset(ptTime, 0, sizeof(*ptTime));
		}
		/* ���ڽ�����ֵ����, ��������ʱ, Ҫ�������ֵ */
		ptTime->tm_year =
			(iDateTimeFlag & FLAG_YEAR) ? ptTime->tm_year - 1900 : 0;

		ptTime->tm_mon =
			(iDateTimeFlag & FLAG_MONTH) ? ptTime->tm_mon - 1 : 0;

		if ((iDateTimeFlag & FLAG_DAY) == 0)
		{
			ptTime->tm_mday = 1;
		}
		if ((iDateTimeFlag & FLAG_HOUR) == 0)
		{
			ptTime->tm_hour = 0;
		}
		if ((iDateTimeFlag & FLAG_MIN) == 0)
		{
			ptTime->tm_min = 0;
		}
		if ((iDateTimeFlag & FLAG_SEC) == 0)
		{
			ptTime->tm_sec = 0;
		}
		if (!iDateTimeFlag)
		{
			goto strToTimeErrOut;
		}
		return iDateTimeFlag;
	}

	/* ������ֶ�֮���Ȼ�зָ���(������Ӣ�ķָ�, ���� 22sep92) */
	for (iStep = STEP_INIT; *pChar != EOS && iLen > 0;
		pChar += iLen, iLen = nextTimeToken(pChar, &iVal, &iFlags))
	{
		/* ǿ��ʽ���, ֱ����䵽�����Ϣ�� */
		if (iFlags == TOKEN_YEAR)
		{
			if ((iDateTimeFlag & FLAG_YEAR) == 0)
			{
				iYear = iVal, iDateTimeFlag |= FLAG_YEAR;
			}
			else
			{
				goto strToTimeErrOut;
			}
			iStep = STEP_DATE, iDateTimeFlag |= FLAG_DATE;
			continue;
		}
		/* ǿ��ʽ�·�, ֱ����䵽�·���Ϣ��(������Ҫ��̽�Ƚ�) */
		else if (iFlags == TOKEN_MONTH)
		{
			if ((iDateTimeFlag & FLAG_MONTH) == 0)
			{
				iMonth = iVal, iDateTimeFlag |= FLAG_ALPHA | FLAG_MONTH;
			}
			/* ���·���Ϣ������ĸָ��, ˵������̽, ��������(ֵ�ؾ���1~12) */
			else if ((iDateTimeFlag & FLAG_ALPHA) == 0)
			{
				if ((iDateTimeFlag & FLAG_DAY) == 0)
				{
					iDay = iMonth, iDateTimeFlag |= FLAG_DAY;
				}
				else if ((iDateTimeFlag & FLAG_YEAR) == 0) /* 2001 ~ 2012�� */
				{
					iYear = iMonth, iDateTimeFlag |= FLAG_YEAR;
				}
				else
				{
					goto strToTimeErrOut;
				}
				iMonth = iVal, iDateTimeFlag |= FLAG_ALPHA;
			}
			else
			{
				goto strToTimeErrOut;
			}
			iStep = STEP_DATE, iDateTimeFlag |= FLAG_DATE;
			continue;
		} /* (iFlags == TOKEN_MONTH) */
		/* ǿ��ʽ����, ֱ����䵽������Ϣ�� */
		else if (iFlags == TOKEN_DAY)
		{
			if ((iDateTimeFlag & FLAG_DAY) == 0)
			{
				iDay = iVal, iDateTimeFlag |= FLAG_DAY;
			}
			else
			{
				goto strToTimeErrOut;
			}
			iStep = STEP_DATE, iDateTimeFlag |= FLAG_DATE;
			continue;
		}
		/* ������Ϣ(����, ����, ��Ȼ��ʱ���, ��Ȼ�����Ͽ�) */
		else if (iFlags == TOKEN_HALFDAY)
		{
			if ((iDateTimeFlag & FLAG_HALFDAY) == 0 &&
				iHour + iVal * 12 < 24)
			{
				iHour += iVal * 12, iDateTimeFlag |= FLAG_HALFDAY;
			}
			else
			{
				goto strToTimeErrOut;
			}
			iStep = STEP_TIME, iDateTimeFlag |= FLAG_TIME;
			continue;
		}
		/* ǿ��ʽСʱ, ֱ����䵽Сʱ��Ϣ�� */
		else if (iFlags == TOKEN_HOUR)
		{
			if ((iDateTimeFlag & FLAG_HOUR) == 0 && iVal < 24)
			{
				iHour = iVal, iDateTimeFlag |= FLAG_HOUR;
			}
			else
			{
				goto strToTimeErrOut;
			}
			iStep = STEP_TIME, iDateTimeFlag |= FLAG_TIME;
			continue;
		}
		/* ǿ��ʽ����, ֱ����䵽������Ϣ�� */
		else if (iFlags == TOKEN_MIN)
		{
			if ((iDateTimeFlag & FLAG_MIN) == 0 && iVal < 60)
			{
				iMinute = iVal, iDateTimeFlag |= FLAG_MIN;
			}
			else
			{
				goto strToTimeErrOut;
			}
			iStep = STEP_TIME, iDateTimeFlag |= FLAG_TIME;
			continue;
		}
		/* ǿ��ʽ��, ֱ����䵽����Ϣ�� */
		else if (iFlags == TOKEN_SEC)
		{
			if ((iDateTimeFlag & FLAG_SEC) == 0 && iVal < 60)
			{
				iSecond = iVal, iDateTimeFlag |= FLAG_SEC;
			}
			else
			{
				goto strToTimeErrOut;
			}
			iStep = STEP_TIME, iDateTimeFlag |= FLAG_TIME;
			continue;
		}

		/* ������ֵ, ���� */
		if (iFlags != TOKEN_VAL)
		{
			continue;
		}

		/* ���β����ʱ��ָ���, ��ֱ�ӽ���ʱ����Ϣ������ */
		if (IsTimeDelim(pChar[iLen]))
		{
			if ((iDateTimeFlag & FLAG_TIME) == 0)
			{
				iStep = STEP_TIME, iDateTimeFlag |= FLAG_TIME;
			}
			/* ���ʱ����Ϣ�ѻ�ȡ, ���ڴ�������״̬, ������ */
			else if (iStep == STEP_DATE)
			{
				iStep = STEP_OVER;
			}
		}
		/* ʱ����Ϣ������, ��û������ʱ��ָ���, ��Ҫ�л������� */
		else if (iStep == STEP_TIME)
		{
			if (IsTimeDelim(pChar[0]))
			{
				/* ���һ���ֶ�, ״̬���� */;
			}
			else if ((iDateTimeFlag & FLAG_DATE) == 0)
			{
				iStep = STEP_DATE, iDateTimeFlag |= FLAG_DATE;
			}
			/* ���������Ϣ�ѻ�ȡ, ���ڴ���ʱ��״̬, ������ */
			else
			{
				iStep = STEP_OVER;
			}
		}
		/* Ĭ������¶��Ǵ������� */
		else
		{
			iStep = STEP_DATE;
		}

		/* ����ʱ��: ʱ����, ��μ��(����ܱ�ʡ��) */
		if (iStep == STEP_TIME)
		{
			if ((iDateTimeFlag & FLAG_HOUR) == 0)
			{
				if (iVal >= 0 && iVal <= 23)
				{
					iHour = iVal, iDateTimeFlag |= FLAG_HOUR;
				}
				else
				{
					goto strToTimeErrOut;
				}
			}
			else if ((iDateTimeFlag & FLAG_MIN) == 0)
			{
				if (iVal >= 0 && iVal <= 59)
				{
					iMinute = iVal, iDateTimeFlag |= FLAG_MIN;
				}
				else
				{
					goto strToTimeErrOut;
				}
			}
			else if ((iDateTimeFlag & FLAG_SEC) == 0)
			{
				if (iVal >= 0 && iVal <= 59)
				{
					iSecond = iVal, iDateTimeFlag |= FLAG_SEC;
				}
				else
				{
					goto strToTimeErrOut;
				}
			}
			else /* �����ʱ������, ����Ϊ�ַ������Ϸ� */
			{
				goto strToTimeErrOut;
			}

			continue;

		} /* if (iStep == STEP_TIME) */

		/* ���ڴ���, ���ڸ�ʽֻ������: ������, ������, ������, 03oct01?
		* ��������һ�ɰ�"������"˳����, ������01��10��3�ն�����03��10��1�� */

		/* ��λ�������, ��������ֱ����� */
		if (iVal >= 1900 && iVal <= 2036)
		{
			if ((iDateTimeFlag & FLAG_YEAR) == 0)
			{
				iYear = iVal, iDateTimeFlag |= FLAG_YEAR;
			}
			else
			{
				goto strToTimeErrOut;
			}
		}
		/* ��λ�������������, ��� */
		else if (iVal == 0 || (iVal >= 70 && iVal <= 99))
		{
			if ((iDateTimeFlag & FLAG_YEAR) == 0)
			{
				iYear = iVal, iDateTimeFlag |= FLAG_YEAR;
			}
			else
			{
				goto strToTimeErrOut;
			}
		}
		else if (iVal <= 12)    /* С��12������, �����ն����� */
		{
			/* д���·ݶ���ʱҪ������ڶ�����ͻ */
			if ((iDateTimeFlag & FLAG_MONTH) == 0)
			{
				if ((iDateTimeFlag & FLAG_DAY) == 0 ||
					iDay <= 29 + s_iMonthFix[iVal - 1])
				{
					iMonth = iVal, iDateTimeFlag |= FLAG_MONTH;
				}
				else if ((iDateTimeFlag & FLAG_YEAR) == 0)
				{
					iYear = iVal, iDateTimeFlag |= FLAG_YEAR;
				}
				else
				{
					goto strToTimeErrOut;
				}
			}
			else if ((iDateTimeFlag & FLAG_DAY) == 0)
			{
				iDay = iVal, iDateTimeFlag |= FLAG_DAY;
			}
			else if ((iDateTimeFlag & FLAG_YEAR) == 0)
			{
				iYear = iVal, iDateTimeFlag |= FLAG_YEAR;
			}
			else
			{
				goto strToTimeErrOut;
			}
		}
		else if (iVal <= 31 /* && iVal > 12 */)
		{
			/* д�����ڶ���ʱҪ����·ݶ�����ͻ */
			if ((iDateTimeFlag & FLAG_DAY) == 0)
			{
				if ((iDateTimeFlag & FLAG_MONTH) == 0 ||
					iVal <= 29 + s_iMonthFix[iMonth - 1])
				{
					iDay = iVal, iDateTimeFlag |= FLAG_DAY;
				}
				else if ((iDateTimeFlag & FLAG_YEAR) == 0)
				{
					iYear = iVal, iDateTimeFlag |= FLAG_YEAR;
				}
				else
				{
					goto strToTimeErrOut;
				}
			}
			else if ((iDateTimeFlag & FLAG_YEAR) == 0)
			{
				iYear = iVal, iDateTimeFlag |= FLAG_YEAR;
			}
			else
			{
				goto strToTimeErrOut;
			}
		}
		else if (iVal > 31 && iVal <= 36)
		{
			if ((iDateTimeFlag & FLAG_YEAR) == 0)
			{
				iYear = iVal, iDateTimeFlag |= FLAG_YEAR;
			}
			else
			{
				goto strToTimeErrOut;
			}
		}
		else /* ���Ϸ��Ķ��� */
		{
			goto strToTimeErrOut;
		}

	} /* while (*pChar != EOS && iLen > 0) */

	/* ���ڴ�����������ڼ�ʱ��, Ŀǰ��Ĭ��˳����: �·�, ����, ���
	* ʹ����������ԭ������, �·ݵ��������ϸ�(1~12), �������(1~31), �������,
	* �����˳���������ڶ���, ���Ա����ͻ���ݵİ��Ʋ���,
	* Ҫ�ı����Ĭ�Ϲ���, ֻ�����������Ƿ��������, Ȼ���޸�˳�򼴿� */

	/* ��ݶ���ת��Ϊ�ڲ���ʾ */
	if (iDateTimeFlag & FLAG_YEAR)
	{
		if (iYear > 2036)
		{
			goto strToTimeErrOut;
		}
		else if (iYear >= 1900)
		{
			ptTime->tm_year = iYear - 1900;
		}
		else if (iYear >= 0 && iYear < 36)
		{
			ptTime->tm_year = iYear + 100;
		}
		else if (iYear >= 70 && iYear <= 99)
		{
			ptTime->tm_year = iYear;
		}
		else
		{
			goto strToTimeErrOut;
		}
	} /* (iDateTimeFlag & FLAG_YEAR) */

	/* �·ݶ���ҲҪת��Ϊ�ڲ���ʾ(0~11) */
	if (iDateTimeFlag & FLAG_MONTH)
	{
		if (iMonth < 1 || iMonth > 12)
		{
			goto strToTimeErrOut;
		}
		ptTime->tm_mon = iMonth - 1;
	}

	/* ����, Ҫ�鿴�Ƿ��������� */
	if (iDateTimeFlag & FLAG_DAY)
	{
		if ((iDay > 29 + s_iMonthFix[ptTime->tm_mon]) ||
			(ptTime->tm_mon == 1 && !LeapYear(iYear) && iDay > 28))
		{
			goto strToTimeErrOut;
		}
		ptTime->tm_mday = iDay;
	}
	else
	{
		ptTime->tm_mday = 1;
	}

	/* ʱ��ֵ�ڸ�ֵʱ���ǺϷ��� */
	ptTime->tm_hour = iHour;
	ptTime->tm_min = iMinute;
	ptTime->tm_sec = iSecond;

	return iDateTimeFlag;

strToTimeErrOut:
	memset(ptTime, 0, sizeof(*ptTime));
	ptTime->tm_mday = 1;
	printf("Unrecognized date and/or time string:\n%s\n", timeStr);
	return 0;
} /* strtotime() */

/*****************************************************************************
*  ��������   : strtotimeTest(*)
*  ��������   : �ַ���ת��Ϊ����ʱ�亯������, ���Է�����֤ת����������ȷ��
*  ��ȫ�ֱ��� : ��
*  дȫ�ֱ��� : ��
*  �������   : �ȴ��û�����
*  �������   : ��
*  �� �� ֵ   : OK
*  ����˵��   : �޸�Ϊmain()���������PC�ϵ���
*---------------------------------------------------------------------------
* ��ʷ��¼(�����, ������@�޸�����, ����˵��)
*  $0000000(N/A), ������@2008-12-28 20:42:26
*----------------------------------------------------------------------------
*/
/* strtotimeTest() */