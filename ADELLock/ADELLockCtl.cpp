// ADELLockCtl.cpp : Implementation of CADELLockCtl
#include "stdafx.h"
#include "ADELLockCtl.h"
#include <comdef.h>

// CADELLockCtl


STDMETHODIMP CADELLockCtl::get_CardSn(LONG* pVal)
{
	*pVal = this->m_card.cardSn.lVal;

	return S_OK;
}


STDMETHODIMP CADELLockCtl::get_ErrMsg(BSTR* pVal)
{
	*pVal = _com_util::ConvertStringToBSTR(this->m_szMsg);

	return S_OK;
}


STDMETHODIMP CADELLockCtl::get_Gate(BSTR* pVal)
{
	*pVal = _com_util::ConvertStringToBSTR(this->m_card.gate);

	return S_OK;
}


STDMETHODIMP CADELLockCtl::get_LastRet(LONG* pVal)
{
	*pVal = this->m_nRet;

	return S_OK;
}


STDMETHODIMP CADELLockCtl::get_Room(BSTR* pVal)
{
	*pVal = _com_util::ConvertStringToBSTR(this->m_card.room);

	return S_OK;
}


STDMETHODIMP CADELLockCtl::get_Stime(BSTR* pVal)
{
	*pVal = _com_util::ConvertStringToBSTR(this->m_card.stime);

	return S_OK;
}


STDMETHODIMP CADELLockCtl::get_CheckInTime(BSTR* pVal)
{
	*pVal = _com_util::ConvertStringToBSTR(this->m_card.beginTime);

	return S_OK;
}


STDMETHODIMP CADELLockCtl::get_CheckOutTime(BSTR* pVal)
{
	*pVal = _com_util::ConvertStringToBSTR(this->m_card.endTime);

	return S_OK;
}


STDMETHODIMP CADELLockCtl::Init(LONG nSoftware, BSTR szServer, BSTR szUserName, LONG nPort, LONG nEncoder, LONG nTMEncoder, LONG* nRet)
{
	if (this->m_bInited)
	{
		this->m_nRet = 0;
		this->GetErrMsg(this->m_nRet);
		*nRet = this->m_nRet;
		return S_OK;
	}

	*nRet = this->PB_Init(nSoftware, "", "", nPort, nEncoder, nTMEncoder);
	return S_OK;
}

STDMETHODIMP CADELLockCtl::NewKey(LONG bDupKey, BSTR room, BSTR stime, BSTR guestname, BSTR guestid, LONG* nRet)
{
	char *pRoom = _com_util::ConvertBSTRToString(room);
	char *pStime = _com_util::ConvertBSTRToString(stime);
	char *pGuestname = _com_util::ConvertBSTRToString(guestname);
	char *pGuestid = _com_util::ConvertBSTRToString(guestid);

	//*nRet = this->PB_NewKey(bDupKey, pRoom, pStime, pGuestname, pGuestid);

	delete[] pRoom;
	delete[] pStime;
	delete[] pGuestname;
	delete[] pGuestid;

	return S_OK;
}


STDMETHODIMP CADELLockCtl::ReadCard(LONG* nRet)
{
	*nRet = this->PB_ReadCard();
	return S_OK;
}


STDMETHODIMP CADELLockCtl::EraseCard(ULONG nCardSn, LONG* nRet)
{
	*nRet = this->PB_EraseCard();
	return S_OK;
}


STDMETHODIMP CADELLockCtl::EndSession(LONG* nRet)
{
	// TODO: Add your implementation code here

	return S_OK;
}


STDMETHODIMP CADELLockCtl::ReaderBeep(LONG nSound, LONG* nRet)
{
	*nRet = this->PB_ReaderBeep(nSound);

	return S_OK;
}
