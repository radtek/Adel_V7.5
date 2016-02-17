// ADELLockCtl.h : Declaration of the CADELLockCtl
#pragma once
#include "resource.h"       // main symbols
#include <atlctl.h>
#include "ADELLock_i.h"//注意名称的改变
#include "_IADELLockCtlEvents_CP.h"
#include "ControlBase.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;



// CADELLockCtl
class ATL_NO_VTABLE CADELLockCtl ://注意名称的改变
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IADELLockCtl, &IID_IADELLockCtl, &LIBID_ADELLockLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IPersistStreamInitImpl<CADELLockCtl>,
	public IOleControlImpl<CADELLockCtl>,
	public IOleObjectImpl<CADELLockCtl>,
	public IOleInPlaceActiveObjectImpl<CADELLockCtl>,
	public IViewObjectExImpl<CADELLockCtl>,
	public IOleInPlaceObjectWindowlessImpl<CADELLockCtl>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CADELLockCtl>,
	public CProxy_IADELLockCtlEvents<CADELLockCtl>,
	public IPersistStorageImpl<CADELLockCtl>,
	public ISpecifyPropertyPagesImpl<CADELLockCtl>,//注意名称的改变
	public IQuickActivateImpl<CADELLockCtl>,
#ifndef _WIN32_WCE
	public IDataObjectImpl<CADELLockCtl>,//注意名称的改变
#endif                                                               //注意名称的改变
	public IProvideClassInfo2Impl<&CLSID_ADELLockCtl, &__uuidof(_IADELLockCtlEvents), &LIBID_ADELLockLib>,
	                        //注意名称的改变
	public IObjectSafetyImpl<CADELLockCtl, INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
	public CComCoClass<CADELLockCtl, &CLSID_ADELLockCtl>,
	public CComControl<CADELLockCtl>,
	public CControlBase
{
public:


	CADELLockCtl()
	{
	}

DECLARE_OLEMISC_STATUS(OLEMISC_RECOMPOSEONRESIZE |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_INSIDEOUT |
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST
)

DECLARE_REGISTRY_RESOURCEID(IDR_ADELLOCKCTL)


BEGIN_COM_MAP(CADELLockCtl)
	COM_INTERFACE_ENTRY(IADELLockCtl)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
#ifndef _WIN32_WCE
	COM_INTERFACE_ENTRY(IDataObject)
#endif
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY_IID(IID_IObjectSafety, IObjectSafety)
END_COM_MAP()

BEGIN_PROP_MAP(CADELLockCtl)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY_TYPE("Property Name", dispid, clsid, vtType)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CADELLockCtl)
	CONNECTION_POINT_ENTRY(__uuidof(_IADELLockCtlEvents))
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CADELLockCtl)
	CHAIN_MSG_MAP(CComControl<CADELLockCtl>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* const arr[] =
		{
			&IID_IADELLockCtl,
		};

		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IADELLockCtl
public:
	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		RECT& rc = *(RECT*)di.prcBounds;
		// Set Clip region to the rectangle specified by di.prcBounds
		HRGN hRgnOld = NULL;
		if (GetClipRgn(di.hdcDraw, hRgnOld) != 1)
			hRgnOld = NULL;
		bool bSelectOldRgn = false;

		HRGN hRgnNew = CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);

		if (hRgnNew != NULL)
		{
			bSelectOldRgn = (SelectClipRgn(di.hdcDraw, hRgnNew) != ERROR);
		}

		Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);
		SetTextAlign(di.hdcDraw, TA_CENTER|TA_BASELINE);
		LPCTSTR pszText = _T("ADELLockCtl");
#ifndef _WIN32_WCE
		TextOut(di.hdcDraw,
			(rc.left + rc.right) / 2,
			(rc.top + rc.bottom) / 2,
			pszText,
			lstrlen(pszText));
#else
		ExtTextOut(di.hdcDraw,
			(rc.left + rc.right) / 2,
			(rc.top + rc.bottom) / 2,
			ETO_OPAQUE,
			NULL,
			pszText,
			ATL::lstrlen(pszText),
			NULL);
#endif

		if (bSelectOldRgn)
			SelectClipRgn(di.hdcDraw, hRgnOld);

		DeleteObject(hRgnNew);

		return S_OK;
	}


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}
	STDMETHOD(get_CardSn)(LONG* pVal);
	STDMETHOD(get_ErrMsg)(BSTR* pVal);
	STDMETHOD(get_Gate)(BSTR* pVal);
	STDMETHOD(get_LastRet)(LONG* pVal);
	STDMETHOD(get_Room)(BSTR* pVal);
	STDMETHOD(get_Stime)(BSTR* pVal);
	STDMETHOD(get_CheckInTime)(BSTR* pVal);
	STDMETHOD(get_CheckOutTime)(BSTR* pVal);
	STDMETHOD(Init)(LONG nSoftware, BSTR szServer, BSTR szUserName, LONG nPort, LONG nEncoder, LONG nTMEncoder, LONG* nRet);
	STDMETHOD(NewKey)(LONG bDupKey, BSTR room, BSTR stime, BSTR guestname, BSTR guestid, LONG* nRet);
	STDMETHOD(ReadCard)(LONG* nRet);
	STDMETHOD(EraseCard)(ULONG nCardSn, LONG* nRet);
	STDMETHOD(EndSession)(LONG* nRet);
	STDMETHOD(ReaderBeep)(LONG nSound, LONG* nRet);
};

OBJECT_ENTRY_AUTO(__uuidof(ADELLockCtl), CADELLockCtl)
