

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IADELLockCtl,0xCC57C928,0xA810,0x436B,0x9E,0x82,0x2A,0x09,0x3A,0x59,0x0B,0x80);


MIDL_DEFINE_GUID(IID, LIBID_ADELLockLib,0xDA79016B,0xDA86,0x44F9,0xA5,0xE8,0xCB,0xF7,0x1B,0x45,0x14,0x57);


MIDL_DEFINE_GUID(IID, DIID__IADELLockCtlEvents,0x94DCCBD4,0xE722,0x4844,0xA2,0x71,0x28,0x45,0x92,0x0B,0x2F,0xDD);


MIDL_DEFINE_GUID(CLSID, CLSID_ADELLockCtl,0xC934ADA0,0xD568,0x4E72,0x9F,0x53,0x7E,0x01,0xE8,0xB2,0x51,0x34);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



