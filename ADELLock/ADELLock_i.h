

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Mon Jan 18 17:28:23 2016
 */
/* Compiler settings for ADELLock.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __ADELLock_i_h__
#define __ADELLock_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IADELLockCtl_FWD_DEFINED__
#define __IADELLockCtl_FWD_DEFINED__
typedef interface IADELLockCtl IADELLockCtl;
#endif 	/* __IADELLockCtl_FWD_DEFINED__ */


#ifndef ___IADELLockCtlEvents_FWD_DEFINED__
#define ___IADELLockCtlEvents_FWD_DEFINED__
typedef interface _IADELLockCtlEvents _IADELLockCtlEvents;
#endif 	/* ___IADELLockCtlEvents_FWD_DEFINED__ */


#ifndef __ADELLockCtl_FWD_DEFINED__
#define __ADELLockCtl_FWD_DEFINED__

#ifdef __cplusplus
typedef class ADELLockCtl ADELLockCtl;
#else
typedef struct ADELLockCtl ADELLockCtl;
#endif /* __cplusplus */

#endif 	/* __ADELLockCtl_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IADELLockCtl_INTERFACE_DEFINED__
#define __IADELLockCtl_INTERFACE_DEFINED__

/* interface IADELLockCtl */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IADELLockCtl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CC57C928-A810-436B-9E82-2A093A590B80")
    IADELLockCtl : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_CardSn( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ErrMsg( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Gate( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_LastRet( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Room( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Stime( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_CheckInTime( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_CheckOutTime( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Init( 
            LONG nSoftware,
            BSTR szServer,
            BSTR szUserName,
            LONG nPort,
            LONG nEncoder,
            LONG nTMEncoder,
            /* [retval][out] */ LONG *nRet) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE NewKey( 
            LONG bDupKey,
            BSTR room,
            BSTR stime,
            BSTR guestname,
            BSTR guestid,
            /* [retval][out] */ LONG *nRet) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ReadCard( 
            /* [retval][out] */ LONG *nRet) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE EraseCard( 
            ULONG nCardSn,
            /* [retval][out] */ LONG *nRet) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE EndSession( 
            /* [retval][out] */ LONG *nRet) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ReaderBeep( 
            LONG nSound,
            /* [retval][out] */ LONG *nRet) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADELLockCtlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IADELLockCtl * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IADELLockCtl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IADELLockCtl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IADELLockCtl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IADELLockCtl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IADELLockCtl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IADELLockCtl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CardSn )( 
            IADELLockCtl * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ErrMsg )( 
            IADELLockCtl * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Gate )( 
            IADELLockCtl * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LastRet )( 
            IADELLockCtl * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Room )( 
            IADELLockCtl * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Stime )( 
            IADELLockCtl * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CheckInTime )( 
            IADELLockCtl * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CheckOutTime )( 
            IADELLockCtl * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Init )( 
            IADELLockCtl * This,
            LONG nSoftware,
            BSTR szServer,
            BSTR szUserName,
            LONG nPort,
            LONG nEncoder,
            LONG nTMEncoder,
            /* [retval][out] */ LONG *nRet);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *NewKey )( 
            IADELLockCtl * This,
            LONG bDupKey,
            BSTR room,
            BSTR stime,
            BSTR guestname,
            BSTR guestid,
            /* [retval][out] */ LONG *nRet);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ReadCard )( 
            IADELLockCtl * This,
            /* [retval][out] */ LONG *nRet);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *EraseCard )( 
            IADELLockCtl * This,
            ULONG nCardSn,
            /* [retval][out] */ LONG *nRet);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *EndSession )( 
            IADELLockCtl * This,
            /* [retval][out] */ LONG *nRet);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ReaderBeep )( 
            IADELLockCtl * This,
            LONG nSound,
            /* [retval][out] */ LONG *nRet);
        
        END_INTERFACE
    } IADELLockCtlVtbl;

    interface IADELLockCtl
    {
        CONST_VTBL struct IADELLockCtlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADELLockCtl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IADELLockCtl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IADELLockCtl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IADELLockCtl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IADELLockCtl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IADELLockCtl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IADELLockCtl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IADELLockCtl_get_CardSn(This,pVal)	\
    ( (This)->lpVtbl -> get_CardSn(This,pVal) ) 

#define IADELLockCtl_get_ErrMsg(This,pVal)	\
    ( (This)->lpVtbl -> get_ErrMsg(This,pVal) ) 

#define IADELLockCtl_get_Gate(This,pVal)	\
    ( (This)->lpVtbl -> get_Gate(This,pVal) ) 

#define IADELLockCtl_get_LastRet(This,pVal)	\
    ( (This)->lpVtbl -> get_LastRet(This,pVal) ) 

#define IADELLockCtl_get_Room(This,pVal)	\
    ( (This)->lpVtbl -> get_Room(This,pVal) ) 

#define IADELLockCtl_get_Stime(This,pVal)	\
    ( (This)->lpVtbl -> get_Stime(This,pVal) ) 

#define IADELLockCtl_get_CheckInTime(This,pVal)	\
    ( (This)->lpVtbl -> get_CheckInTime(This,pVal) ) 

#define IADELLockCtl_get_CheckOutTime(This,pVal)	\
    ( (This)->lpVtbl -> get_CheckOutTime(This,pVal) ) 

#define IADELLockCtl_Init(This,nSoftware,szServer,szUserName,nPort,nEncoder,nTMEncoder,nRet)	\
    ( (This)->lpVtbl -> Init(This,nSoftware,szServer,szUserName,nPort,nEncoder,nTMEncoder,nRet) ) 

#define IADELLockCtl_NewKey(This,bDupKey,room,stime,guestname,guestid,nRet)	\
    ( (This)->lpVtbl -> NewKey(This,bDupKey,room,stime,guestname,guestid,nRet) ) 

#define IADELLockCtl_ReadCard(This,nRet)	\
    ( (This)->lpVtbl -> ReadCard(This,nRet) ) 

#define IADELLockCtl_EraseCard(This,nCardSn,nRet)	\
    ( (This)->lpVtbl -> EraseCard(This,nCardSn,nRet) ) 

#define IADELLockCtl_EndSession(This,nRet)	\
    ( (This)->lpVtbl -> EndSession(This,nRet) ) 

#define IADELLockCtl_ReaderBeep(This,nSound,nRet)	\
    ( (This)->lpVtbl -> ReaderBeep(This,nSound,nRet) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IADELLockCtl_INTERFACE_DEFINED__ */



#ifndef __ADELLockLib_LIBRARY_DEFINED__
#define __ADELLockLib_LIBRARY_DEFINED__

/* library ADELLockLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_ADELLockLib;

#ifndef ___IADELLockCtlEvents_DISPINTERFACE_DEFINED__
#define ___IADELLockCtlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IADELLockCtlEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__IADELLockCtlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("94DCCBD4-E722-4844-A271-2845920B2FDD")
    _IADELLockCtlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IADELLockCtlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IADELLockCtlEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IADELLockCtlEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IADELLockCtlEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IADELLockCtlEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IADELLockCtlEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IADELLockCtlEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IADELLockCtlEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IADELLockCtlEventsVtbl;

    interface _IADELLockCtlEvents
    {
        CONST_VTBL struct _IADELLockCtlEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IADELLockCtlEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IADELLockCtlEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IADELLockCtlEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IADELLockCtlEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IADELLockCtlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IADELLockCtlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IADELLockCtlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IADELLockCtlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ADELLockCtl;

#ifdef __cplusplus

class DECLSPEC_UUID("C934ADA0-D568-4E72-9F53-7E01E8B25134")
ADELLockCtl;
#endif
#endif /* __ADELLockLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


