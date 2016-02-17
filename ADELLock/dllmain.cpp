// dllmain.cpp : Implementation of DllMain.

#include "stdafx.h"
#include "resource.h"
#include "ADELLock_i.h"
#include "dllmain.h"
#include "funcPtrs.h"
CADELLockModule _AtlModule;
ADEL_FUNCS g_ADELFuncs;

// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	hInstance;
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
		if (g_ADELFuncs.hDllInst == NULL)
		{
			g_ADELFuncs.hDllInst = LoadLibrary(_T("MainDll.dll"));
			if (g_ADELFuncs.hDllInst != NULL)
			{
				g_ADELFuncs.pInit = (PF_INIT)GetProcAddress(g_ADELFuncs.hDllInst, "Init");
				g_ADELFuncs.pEndSession = (PF_ENDSESSION)GetProcAddress(g_ADELFuncs.hDllInst, "EndSession");
				g_ADELFuncs.pChangeUser = (PF_CHANGEUSER)GetProcAddress(g_ADELFuncs.hDllInst, "ChangeUser");
				g_ADELFuncs.pNewKey = (PF_NEWKEY)GetProcAddress(g_ADELFuncs.hDllInst, "NewKey");
				g_ADELFuncs.pDupKey = (PF_DUPKEY)GetProcAddress(g_ADELFuncs.hDllInst, "DupKey");
				g_ADELFuncs.pReadCard = (PF_READCARD)GetProcAddress(g_ADELFuncs.hDllInst, "ReadCard");
				g_ADELFuncs.pEraseCard = (PF_ERASECARD)GetProcAddress(g_ADELFuncs.hDllInst, "EraseCard");
				g_ADELFuncs.pCheckOut = (PF_CHECKOUT)GetProcAddress(g_ADELFuncs.hDllInst, "CheckOut");
				g_ADELFuncs.pLostCard = (PF_LOSTCARD)GetProcAddress(g_ADELFuncs.hDllInst, "Lostcard");
				g_ADELFuncs.pSetPort = (PF_SETPORT)GetProcAddress(g_ADELFuncs.hDllInst, "SetPort");
				g_ADELFuncs.pReaderBeep = (PF_READER_BEEP)GetProcAddress(g_ADELFuncs.hDllInst, "Reader_Beep");
				g_ADELFuncs.pReadCardID = (PF_READCARDID)GetProcAddress(g_ADELFuncs.hDllInst, "ReadCardId");
			}
		}
		break;
	case DLL_PROCESS_DETACH:
		if (g_ADELFuncs.hDllInst != NULL)
		{
			FreeLibrary(g_ADELFuncs.hDllInst);
			memset(&g_ADELFuncs, 0, sizeof(ADEL_FUNCS));
		}
		break;

	}
	return _AtlModule.DllMain(dwReason, lpReserved);
}
