#include "stdafx.h"
#include "ScriptablePluginObjectBase.h"

ScriptablePluginObjectBase::ScriptablePluginObjectBase(NPP npp) :
	mNpp(npp)
{
}

ScriptablePluginObjectBase::~ScriptablePluginObjectBase(void)
{
}

void
ScriptablePluginObjectBase::Invalidate()
{
}

bool
ScriptablePluginObjectBase::HasMethod(NPIdentifier name)
{
	return false;
}

bool
ScriptablePluginObjectBase::Invoke(NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	return false;
}

bool
ScriptablePluginObjectBase::InvokeDefault(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	return false;
}

bool
ScriptablePluginObjectBase::HasProperty(NPIdentifier name)
{
	return false;
}

bool
ScriptablePluginObjectBase::GetProperty(NPIdentifier name, NPVariant *result)
{
	return false;
}

bool
ScriptablePluginObjectBase::SetProperty(NPIdentifier name, const NPVariant *value)
{
	return false;
}

bool
ScriptablePluginObjectBase::RemoveProperty(NPIdentifier name)
{
	return false;
}

bool
ScriptablePluginObjectBase::Enumerate(NPIdentifier **identifier, uint32_t *count)
{
	return false;
}

bool
ScriptablePluginObjectBase::Construct(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	return false;
}

// static
void
ScriptablePluginObjectBase::_Deallocate(NPObject *npobj)
{
	// Call the virtual destructor.
	delete (ScriptablePluginObjectBase *)npobj;
}

// static
void
ScriptablePluginObjectBase::_Invalidate(NPObject *npobj)
{
	((ScriptablePluginObjectBase *)npobj)->Invalidate();
}

// static
bool
ScriptablePluginObjectBase::_HasMethod(NPObject *npobj, NPIdentifier name)
{
	return ((ScriptablePluginObjectBase *)npobj)->HasMethod(name);
}

// static
bool
ScriptablePluginObjectBase::_Invoke(NPObject *npobj, NPIdentifier name, 
	const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	return ((ScriptablePluginObjectBase *)npobj)->Invoke(name, args, argCount, result);
}

// static
bool
ScriptablePluginObjectBase::_InvokeDefault(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	return ((ScriptablePluginObjectBase *)npobj)->InvokeDefault(args, argCount, result);
}

// static
bool
ScriptablePluginObjectBase::_HasProperty(NPObject * npobj, NPIdentifier name)
{
	return ((ScriptablePluginObjectBase *)npobj)->HasProperty(name);
}

// static
bool
ScriptablePluginObjectBase::_GetProperty(NPObject *npobj, NPIdentifier name, NPVariant *result)
{
	return ((ScriptablePluginObjectBase *)npobj)->GetProperty(name, result);
}

// static
bool
ScriptablePluginObjectBase::_SetProperty(NPObject *npobj, NPIdentifier name, const NPVariant *value)
{
	return ((ScriptablePluginObjectBase *)npobj)->SetProperty(name, value);
}

// static
bool
ScriptablePluginObjectBase::_RemoveProperty(NPObject *npobj, NPIdentifier name)
{
	return ((ScriptablePluginObjectBase *)npobj)->RemoveProperty(name);
}

// static
bool
ScriptablePluginObjectBase::_Enumerate(NPObject *npobj, NPIdentifier **identifier, uint32_t *count)
{
	return ((ScriptablePluginObjectBase *)npobj)->Enumerate(identifier, count);
}

// static
bool
ScriptablePluginObjectBase::_Construct(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	return ((ScriptablePluginObjectBase *)npobj)->Construct(args, argCount, result);
}

int
ScriptablePluginObjectBase::GetInt(const NPVariant *pVal) const
{
	if(NPVARIANT_IS_INT32(*pVal))
		return NPVARIANT_TO_INT32(*pVal);
	else if(NPVARIANT_IS_DOUBLE(*pVal))
		return (int)(NPVARIANT_TO_DOUBLE(*pVal) + 0.5);
	return 0;
}

char*
ScriptablePluginObjectBase::GetUTFStr(const NPVariant *pVal, char *pBuf, UINT nBufSize) const
{
	if(NPVARIANT_IS_STRING(*pVal)
		&& pVal->value.stringValue.UTF8Length >= 0
		&& pVal->value.stringValue.UTF8Length < nBufSize)
	{
		strncpy_s(pBuf, nBufSize,
			pVal->value.stringValue.UTF8Characters,
			pVal->value.stringValue.UTF8Length);

		pBuf[pVal->value.stringValue.UTF8Length] = 0;
	}
	return pBuf;
}
