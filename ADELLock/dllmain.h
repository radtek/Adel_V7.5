// dllmain.h : Declaration of module class.

class CADELLockModule : public ATL::CAtlDllModuleT< CADELLockModule >
{
public :
	DECLARE_LIBID(LIBID_ADELLockLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ADELLOCK, "{26EC1F7F-1E2C-4C21-B122-A764399C5485}")
};

extern class CADELLockModule _AtlModule;
