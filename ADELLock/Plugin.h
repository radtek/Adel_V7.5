#pragma once
#include <pluginbase.h>
#include "ScriptablePluginObjectBase.h"
#include "ControlBase.h"

enum enumIdentifierIndex
{
	ID_LASTRET = 0,
	ID_ERRMSG,
	ID_INIT,
	ID_ENDSESSION,
	ID_NEWKEY,
	ID_CHANGEUSER,
	ID_READCARD,
	ID_ERASECARD,
	ID_CHECKOUT,
	ID_LOSTCARD,
	ID_ROOM,
	ID_GATE,
	ID_GUESTNAME,
	ID_GUESTID,
	ID_CARDSN,
	ID_CARDST,
	ID_STIME,
	ID_READERBEEP,
	ID_SETPORTEX,
	ID_INITFROMREG,

#define ID_LAST				ID_INITFROMREG
};


//ID类型（属性或方法）
enum enumIdType
{
	IT_PROPERTY = 0,
	IT_METHOD
};

typedef struct tagRAW_IDITEM
{
	char *name;
	int type;
} RAW_IDITEM, *LPRAW_IDITEM;

typedef struct tagIDITEM
{
	NPIdentifier id;
	int type;
} IDITEM, *LPIDITEM;


class CPlugin :
	public nsPluginInstanceBase,
	public CControlBase
{
private:
	NPP m_pNPInstance;
	NPBool m_bInitialized;
	WNDPROC m_pOldProc;
	HWND m_hWnd;
	NPObject *m_pScriptableObject;

public:
	CPlugin(NPP pNPInstance);
	virtual ~CPlugin(void);

	NPBool init(NPWindow *pNPWindow)
	{
		m_bInitialized = TRUE;
		return TRUE;
	}

	void shut();
	HWND GetHWnd() { return m_hWnd; }
	NPBool isInitialized() { return m_bInitialized; }
	virtual NPError SetWindow(NPWindow* pNPWindow);
	virtual NPError GetValue(NPPVariable variable, void *value);
	NPObject *GetScriptableObject();
};

//Constructable... 为了自定义 Construct 方法而继承 ScriptablePluginObjectBase 的！
class ConstructablePluginObject : public ScriptablePluginObjectBase
{
public:
	ConstructablePluginObject(NPP npp) : ScriptablePluginObjectBase(npp)
	{
	}
	virtual bool Construct(const NPVariant *args, uint32_t argCount, NPVariant *result);
};

class ScriptablePluginObject : public ScriptablePluginObjectBase
{
public:
	ScriptablePluginObject(NPP npp) :
		ScriptablePluginObjectBase(npp)
	{
	}
	virtual bool HasMethod(NPIdentifier name);
	virtual bool HasProperty(NPIdentifier name);
	virtual bool GetProperty(NPIdentifier name, NPVariant *result);
	virtual bool SetProperty(NPIdentifier name, const NPVariant *value);
	virtual bool Invoke(NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result);
	virtual bool InvokeDefault(const NPVariant *args, uint32_t argCount, NPVariant *result);
};

//子类化！
static LRESULT CALLBACK PluginWinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
static NPObject *AllocateConstructablePluginObject(NPP npp, NPClass *aClass);
static NPObject *AllocateScriptablePluginObject(NPP npp, NPClass *aClass);

//从char*转换到UTF8编码（该函数调用了NPN_MemAlloc分配内存）
static char* AllocAnsiCopy(const char *szSrc, int *pResultLen);
static char* UTFToLocalAnsi(const char *szUTF8, UINT nUTFLen, char *pBuf, UINT nBufSize);
static char* AnsiToUTF(const char* szAscii, int *pResultLen);
static char* UTFToAscii(const char* szUTF8, int *pResultLen);

static char* UnicodeToUTF(LPWSTR pUnicode, int *pResultLen);
static WCHAR* UTFToUnicode(const char* szUTF8, int len_utf8, LPWSTR pUnicode, int len_unicode);
