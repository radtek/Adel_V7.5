#include "StdAfx.h"
#include "Plugin.h"
#include <windowsx.h>

//extern NPNetscapeFuncs NPNFuncs;
DECLARE_NPOBJECT_CLASS_WITH_BASE(ScriptablePluginObject,    AllocateScriptablePluginObject);
DECLARE_NPOBJECT_CLASS_WITH_BASE(ConstructablePluginObject, AllocateConstructablePluginObject);

static IDITEM IdArray[ID_LAST + 1];
static NPObject *sWindowObj;

CPlugin::CPlugin(NPP pNPInstance) :
	nsPluginInstanceBase(),
	m_pNPInstance(pNPInstance),
	m_hWnd(NULL),
	m_pScriptableObject(NULL),
	m_bInitialized(FALSE)
{
	int i;
	NPN_GetValue(m_pNPInstance, NPNVWindowNPObject, &sWindowObj);

	const RAW_IDITEM _ids[ID_LAST + 1] = 
	{
		{ "LastRet",			IT_PROPERTY	},
		{ "ErrMsg",				IT_PROPERTY	},
		{ "Init",				IT_METHOD	},
		{ "EndSession",			IT_METHOD	},
		{ "NewKey",				IT_METHOD	},
		{ "ChangeUser",			IT_METHOD	},
		{ "ReadCard",			IT_METHOD	},
		{ "EraseCard",			IT_METHOD	},
		{ "CheckOut",			IT_METHOD	},
		{ "LostCard",			IT_METHOD	},
		{ "Room",				IT_PROPERTY	},
		{ "Gate",				IT_PROPERTY	},
		{ "GuestName",			IT_PROPERTY	},
		{ "GuestID",			IT_PROPERTY	},
		{ "CardSn",				IT_PROPERTY	},
		{ "CardSt",				IT_PROPERTY	},
		{ "Stime",				IT_PROPERTY	},
		{ "ReaderBeep",			IT_METHOD	},
		{ "SetPortEx",			IT_METHOD	},
		{ "InitFromReg",		IT_METHOD	}
	};

	for(i = 0; i < _ARRAYSIZE(IdArray); i++)
	{
		IdArray[i].id = NPN_GetStringIdentifier(_ids[i].name);
		IdArray[i].type = _ids[i].type;
	}
}

CPlugin::~CPlugin(void)
{
	if (sWindowObj != NULL)
	{
		NPN_ReleaseObject(sWindowObj);
		sWindowObj = NULL;
	}

	if(this->m_pScriptableObject != NULL)
	{
		NPN_ReleaseObject(m_pScriptableObject);
		this->m_pScriptableObject = NULL;
	}
}

//浏览器把窗口句柄通知给插件，在这里进行子类化
NPError CPlugin::SetWindow(NPWindow* pNPWindow)
{
	this->m_hWnd = (HWND)pNPWindow->window;
	this->m_pOldProc = SubclassWindow(this->m_hWnd, (WNDPROC)PluginWinProc);
	//本类的实例指针附着到窗口实例上
	SetWindowLongPtr(this->m_hWnd, GWLP_USERDATA, (LONG_PTR)this);
	this->m_bInitialized = TRUE;
	return NPERR_NO_ERROR;
}

void CPlugin::shut()
{
	//subclass it back!
	if(this->m_hWnd != NULL && this->m_pOldProc != NULL)
		SubclassWindow(this->m_hWnd, this->m_pOldProc);
	this->m_hWnd = NULL;
	this->m_bInitialized = FALSE;
}

NPError CPlugin::GetValue(NPPVariable variable, void *value)
{
	NPError rv = NPERR_NO_ERROR;
	switch (variable)
	{
	case NPPVpluginNameString:
		*((char**)value) = "NPRuntimeTest";
		break;
	case NPPVpluginDescriptionString:
		*((char**)value) = "NPRuntime scriptability API test plugin";
		break;
	case NPPVpluginScriptableNPObject:
		*(NPObject**)value = this->GetScriptableObject();
		break;
	default:
		rv = NPERR_GENERIC_ERROR;
	}
	return rv;
}

NPObject *CPlugin::GetScriptableObject()
{
	if(this->m_pScriptableObject == NULL) 
	{
		this->m_pScriptableObject = NPN_CreateObject(m_pNPInstance, GET_NPOBJECT_CLASS(ScriptablePluginObject));
	}
	if(this->m_pScriptableObject)
	{
		NPN_RetainObject(this->m_pScriptableObject);
	}
	return this->m_pScriptableObject;
}

NPError NS_PluginInitialize()
{
	return NPERR_NO_ERROR;
}

void NS_PluginShutdown()
{
}

nsPluginInstanceBase* NS_NewPluginInstance(nsPluginCreateData *pCreateDataStruct)
{
	if(pCreateDataStruct == NULL)
		return NULL;

	CPlugin *plugin = new CPlugin(pCreateDataStruct->instance);
	return plugin;
}

void NS_DestroyPluginInstance(nsPluginInstanceBase *pPlugin)
{
	if(pPlugin != NULL)
		delete (CPlugin*)pPlugin;
}

static LRESULT CALLBACK PluginWinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) 
	{
	case WM_PAINT:
		{
			// draw a frame and display the string
			RECT rc;
			PAINTSTRUCT ps;
			BeginPaint(hWnd, &ps);
			GetClientRect(hWnd, &rc);
			FrameRect(ps.hdc, &rc, GetStockBrush(BLACK_BRUSH));
			//CPlugin *p = (CPlugin *)GetWindowLong(hWnd, GWL_USERDATA);
			//if(p != NULL) p->PaintClient(ps.hdc, &rc);
			SetBkMode(ps.hdc, TRANSPARENT);
			//SetTextColor(ps.hdc, RGB(0, 0, 255));
			DrawText(ps.hdc, _T("ADEL Lock Plugin."), -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			EndPaint(hWnd, &ps);
		}
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool ConstructablePluginObject::Construct(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	//printf("Creating new ConstructablePluginObject!\n");
	NPObject *myobj = NPN_CreateObject(mNpp, GET_NPOBJECT_CLASS(ConstructablePluginObject));
	if (!myobj)
		return false;
	
	OBJECT_TO_NPVARIANT(myobj, *result);
	return true;
}

static NPObject *AllocateConstructablePluginObject(NPP npp, NPClass *aClass)
{
	return new ConstructablePluginObject(npp);
}


static NPObject *AllocateScriptablePluginObject(NPP npp, NPClass *aClass)
{
	return new ScriptablePluginObject(npp);
}

bool ScriptablePluginObject::HasMethod(NPIdentifier name)
{
	int i;
	for(i = 0; i < _ARRAYSIZE(IdArray); i++)
	{
		if(IdArray[i].type == IT_METHOD && IdArray[i].id == name)
			return true;
	}
	return false;
}

bool ScriptablePluginObject::HasProperty(NPIdentifier name)
{
	int i;
	for(i = 0; i < _ARRAYSIZE(IdArray); i++)
	{
		if(IdArray[i].type == IT_PROPERTY && IdArray[i].id == name)
			return true;
	}
	return false;
}

bool ScriptablePluginObject::GetProperty(NPIdentifier name, NPVariant *result)
{
	char *pUTF8 = NULL;
	int len = 0;
	CPlugin *plugin = (CPlugin*)(this->mNpp->pdata);

	VOID_TO_NPVARIANT(*result);

	if(name == IdArray[ID_LASTRET].id)
	{
		INT32_TO_NPVARIANT(plugin->m_nRet, *result);
	}
	else if(name == IdArray[ID_ERRMSG].id)
	{
		pUTF8 = AnsiToUTF(plugin->m_szMsg, &len);
		STRINGN_TO_NPVARIANT(pUTF8, len, *result);
	}
	else if(name == IdArray[ID_ROOM].id)
	{
		pUTF8 = AllocAnsiCopy(plugin->m_card.room, &len);
		STRINGN_TO_NPVARIANT(pUTF8, len, *result);
	}
	else if(name == IdArray[ID_GATE].id)
	{
		pUTF8 = AllocAnsiCopy(plugin->m_card.gate, &len);
		STRINGN_TO_NPVARIANT(pUTF8, len, *result);
	}
	
	else if(name == IdArray[ID_CARDSN].id)
	{
		INT32_TO_NPVARIANT(plugin->m_card.cardSn.lVal, *result);
	}
	
	else if(name == IdArray[ID_STIME].id)
	{
		pUTF8 = AllocAnsiCopy(plugin->m_card.stime, &len);
		STRINGN_TO_NPVARIANT(pUTF8, len, *result);
	}
	return true;
}

bool ScriptablePluginObject::SetProperty(NPIdentifier name, const NPVariant *value)
{
	CPlugin *plugin = (CPlugin*)(this->mNpp->pdata);
	return true;
}

bool ScriptablePluginObject::Invoke(NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	CPlugin *plugin = (CPlugin*)(this->mNpp->pdata);
	if(plugin == NULL)
		return false;

	char szServer[96], szUser[32];
	int nSoftware = 18;
	int nPort = 0; //USB Port
	int nEncoder = 0; //手工发行机
	int nTMEncoder = 1;
	UINT argIndex = -1; //实际是 0xFFFFFFFF

	//Init(int software, string server, string username, int port, int encoder, int TMEncoder);
	if(name == IdArray[ID_INIT].id)
	{
		if(plugin->IsInited())
		{
			plugin->m_nRet = 0;
			INT32_TO_NPVARIANT(plugin->m_nRet, *result);
			return true;
		}

		++argIndex;
		if(argCount > argIndex)
			nSoftware = this->GetInt(&args[argIndex]);

		++argIndex;
		szServer[0] = 0;
		if(argCount > argIndex)
			this->GetUTFStr(&args[argIndex], szServer, _ARRAYSIZE(szServer));
		
		++argIndex;
		szUser[0] = 0;
		if(argCount > argIndex && NPVARIANT_IS_STRING(args[argIndex]))
		{
			UTFToLocalAnsi(args[argIndex].value.stringValue.UTF8Characters, 
				args[argIndex].value.stringValue.UTF8Length,
				szUser, _ARRAYSIZE(szUser));
		}

		++argIndex;
		if(argCount > argIndex)
			nPort = this->GetInt(&args[argIndex]);

		++argIndex;
		if(argCount > argIndex)
			nEncoder = this->GetInt(&args[argIndex]);

		++argIndex;
		if(argCount > argIndex)
			nTMEncoder = this->GetInt(&args[argIndex]);

		plugin->PB_Init(nSoftware, szServer, szUser, nPort, nEncoder, nTMEncoder);
	}
	else if(name == IdArray[ID_ENDSESSION].id)
	{
		plugin->PB_EndSession();
	}

	//NewKey(BOOL bDupKey, string room, string stime, string guestname, string guestid);
	else if(name == IdArray[ID_NEWKEY].id)
	{
		BOOL bDupKey = FALSE;
		memset(&plugin->m_card, 0, sizeof(ADEL_CARD));

		//[BUGBUG!!!] 对于chrome，使用的是 doubleVal 传递数字！
		++argIndex;
		if(argCount > argIndex)
			bDupKey = this->GetInt(&args[argIndex]);

		++argIndex;
		if(argCount > argIndex)
			this->GetUTFStr(&args[argIndex], plugin->m_card.room, _ARRAYSIZE(plugin->m_card.room));

		++argIndex;
		if(argCount > argIndex)
			this->GetUTFStr(&args[argIndex], plugin->m_card.stime, _ARRAYSIZE(plugin->m_card.stime));

		++argIndex;
		if(argCount > argIndex && NPVARIANT_IS_STRING(args[argIndex]))
		{
			UTFToLocalAnsi(args[argIndex].value.stringValue.UTF8Characters,
				args[argIndex].value.stringValue.UTF8Length,
				plugin->m_card.guestname,
				_ARRAYSIZE(plugin->m_card.guestname));
		}

		++argIndex;
		if(argCount > argIndex && NPVARIANT_IS_STRING(args[argIndex]))
		{
			UTFToLocalAnsi(args[argIndex].value.stringValue.UTF8Characters,
				args[argIndex].value.stringValue.UTF8Length,
				plugin->m_card.guestid,
				_ARRAYSIZE(plugin->m_card.guestid));
		}
		plugin->PB_NewKey(bDupKey);
	}

	//ReadCard();
	else if(name == IdArray[ID_READCARD].id)
	{
		plugin->PB_ReadCard();
	}

	//EraseCard(ULONG cardSn);
	else if(name == IdArray[ID_ERASECARD].id)
	{
		++argIndex;
		plugin->m_card.cardSn.lVal = 0;
		if(argCount > argIndex)
			plugin->m_card.cardSn.lVal = this->GetInt(&args[argIndex]);

		plugin->PB_EraseCard();
	}

	//ReaderBeep(int nSound);
	else if(name == IdArray[ID_READERBEEP].id)
	{
		int nSound = 0;
		
		++argIndex;
		if(argCount >= argIndex)
			nSound = this->GetInt(&args[argIndex]);

		plugin->PB_ReaderBeep(nSound);
	}

	INT32_TO_NPVARIANT(plugin->m_nRet, *result);
	return true;
}

bool ScriptablePluginObject::InvokeDefault(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	//printf("ScriptablePluginObject default method called!\n");
	UINT nBufSize = 48;
	char *s = (char*)NPN_MemAlloc(nBufSize);
	if(s != NULL)
	{
		strcpy_s(s, nBufSize, "default method return val");
		STRINGZ_TO_NPVARIANT(s, *result);
		return TRUE;
	}
	else
		return FALSE;
}

//分配一个 ansi 字符串的原样的拷贝
static char* AllocAnsiCopy(const char *szSrc, int *pResultLen)
{
	size_t len_ascii = strlen(szSrc);
	char *pDest = (char*)NPN_MemAlloc((len_ascii + 1) * sizeof(CHAR));
	if(pDest != NULL)
	{
		strcpy_s(pDest, len_ascii + 1, szSrc);
		*pResultLen = len_ascii;
	}
	else
	{
		*pResultLen = 0;
	}
	return pDest;
}

//把从外部传入的参数字符串，转码到栈上的字符串缓冲区
static char* UTFToLocalAnsi(const char *szUTF8, UINT nUTFLen, char *pBuf, UINT nBufSize)
{
	if(szUTF8 == NULL)
	{
		return NULL;
	}
	int cchWideChar = MultiByteToWideChar(CP_UTF8, 0, szUTF8, nUTFLen, NULL, 0);
	if(cchWideChar < 0)
	{
		return NULL;
	}
	LPWSTR pUnicode = (LPWSTR)NPN_MemAlloc((cchWideChar + 1) * sizeof(WCHAR));
	if(pUnicode == NULL)
	{
		return NULL;
	}
	MultiByteToWideChar(CP_UTF8, 0, szUTF8, nUTFLen, pUnicode, cchWideChar + 1);

	int cbAscii = WideCharToMultiByte(CP_ACP, 0, pUnicode, cchWideChar, NULL, 0, NULL, NULL);
	if(cbAscii < 0)
	{
		NPN_MemFree(pUnicode);
		return NULL;
	}
	memset(pBuf, 0, sizeof(CHAR) * nBufSize);
	WideCharToMultiByte(CP_ACP, 0, pUnicode, cchWideChar, pBuf, nBufSize, NULL, NULL);

	//free memory!!!
	NPN_MemFree(pUnicode);
	return pBuf;
}

//如果src全部是ascii字符，就无需转换，只有含有中文字时需要转换
static char* AnsiToUTF(const char* szAscii, int *pResultLen)
{
	if(szAscii == NULL)
	{
		*pResultLen = 0;
		return NULL;
	}

	size_t len_ascii = strlen(szAscii);
	int cchWideChar = MultiByteToWideChar(CP_ACP, 0, szAscii, len_ascii, NULL, 0);
	if(cchWideChar < 0)
	{
		*pResultLen = 0;
		return NULL;
	}
	LPWSTR pUnicode = (LPWSTR)NPN_MemAlloc((cchWideChar + 1) * sizeof(WCHAR));
	if(pUnicode == NULL)
	{
		*pResultLen = 0;
		return NULL;
	}
	MultiByteToWideChar(CP_ACP, 0, szAscii, len_ascii, pUnicode, cchWideChar + 1);

	int cbUTF8 = WideCharToMultiByte(CP_UTF8, 0, pUnicode, cchWideChar, NULL, 0, NULL, NULL);
	if(cbUTF8 < 0)
	{
		NPN_MemFree(pUnicode);
		*pResultLen = 0;
		return NULL;
	}

	LPSTR pUTF8 = (LPSTR)NPN_MemAlloc((cbUTF8 + 1) * sizeof(CHAR));
	if(pUTF8 == NULL)
	{
		NPN_MemFree(pUnicode);
		*pResultLen = 0;
		return NULL;
	}
	WideCharToMultiByte(CP_UTF8, 0, pUnicode, cchWideChar, pUTF8, cbUTF8 + 1, NULL, NULL);
	pUTF8[cbUTF8] = '\0';

	//free memory!!!
	NPN_MemFree(pUnicode);

	*pResultLen = cbUTF8;
	return pUTF8;
}

static char* UTFToAnsi(const char* szUTF8, int *pResultLen)
{
	if(szUTF8 == NULL)
	{
		*pResultLen = 0;
		return NULL;
	}

	size_t len_utf8 = strlen(szUTF8);
	int cchWideChar = MultiByteToWideChar(CP_UTF8, 0, szUTF8, len_utf8, NULL, 0);
	if(cchWideChar < 0)
	{
		*pResultLen = 0;
		return NULL;
	}
	LPWSTR pUnicode = (LPWSTR)NPN_MemAlloc((cchWideChar + 1) * sizeof(WCHAR));
	if(pUnicode == NULL)
	{
		*pResultLen = 0;
		return NULL;
	}
	MultiByteToWideChar(CP_UTF8, 0, szUTF8, len_utf8, pUnicode, cchWideChar + 1);

	int cbAscii = WideCharToMultiByte(CP_ACP, 0, pUnicode, cchWideChar, NULL, 0, NULL, NULL);
	if(cbAscii < 0)
	{
		NPN_MemFree(pUnicode);
		*pResultLen = 0;
		return NULL;
	}

	LPSTR pAscii = (LPSTR)NPN_MemAlloc((cbAscii + 1) * sizeof(CHAR));
	if(pAscii == NULL)
	{
		NPN_MemFree(pUnicode);
		*pResultLen = 0;
		return NULL;
	}
	WideCharToMultiByte(CP_ACP, 0, pUnicode, cchWideChar, pAscii, cbAscii + 1, NULL, NULL);
	pAscii[cbAscii] = '\0';

	//free memory!!!
	NPN_MemFree(pUnicode);

	*pResultLen = cbAscii;
	return pAscii;
}

//如果src全部是ascii字符，就无需转换，只有含有中文字时需要转换
static char* UnicodeToUTF(LPWSTR pUnicode, int *pResultLen)
{
	if(pUnicode == NULL)
	{
		*pResultLen = 0;
		return NULL;
	}
	size_t len_unicode = wcslen(pUnicode);

	int cbUTF8 = WideCharToMultiByte(CP_UTF8, 0, pUnicode, len_unicode, NULL, 0, NULL, NULL);
	if(cbUTF8 < 0)
	{
		*pResultLen = 0;
		return NULL;
	}
	LPSTR pUTF8 = (LPSTR)NPN_MemAlloc((cbUTF8 + 1) * sizeof(CHAR));
	if(pUTF8 == NULL)
	{
		*pResultLen = 0;
		return NULL;
	}
	WideCharToMultiByte(CP_UTF8, 0, pUnicode, len_unicode, pUTF8, cbUTF8 + 1, NULL, NULL);
	pUTF8[cbUTF8] = '\0';

	*pResultLen = cbUTF8;
	return pUTF8;
}

static WCHAR* UTFToUnicode(const char* szUTF8, int len_utf8, LPWSTR pUnicode, int len_unicode)
{
	int cchWideChar = MultiByteToWideChar(CP_UTF8, 0, szUTF8, len_utf8, pUnicode, len_unicode);
	if(cchWideChar >= 0)
		pUnicode[cchWideChar] = 0;
	return pUnicode;
}