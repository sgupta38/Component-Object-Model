#include "prop.h"

//	globals

LONG g_ActiveNoOfComponents = 0;
LONG g_ActiveNoOfServerLocks = 0;

class CPropertyClass: public IFirst, ISecond, IThird
{
private:
	LONG m_cRef;
public:
	CPropertyClass();
	~CPropertyClass();

	//	IUnknown routines
	HRESULT __stdcall QueryInterface(REFIID riid, void **ppv);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();

	//	IFirst
	HRESULT __stdcall FirstFunction();

	//	ISecond
	HRESULT __stdcall SecondFunction();

	//	IThree
	HRESULT __stdcall ThirdFunction();
};


class CPropertyClassFactory: public IClassFactory
{
private:
	LONG m_cRef;
public:
	CPropertyClassFactory();
	~CPropertyClassFactory();

	//	IUnknown routines
	HRESULT __stdcall QueryInterface(REFIID riid, void **ppv);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();

	//	IClassFactory
		//	IUnknown routines
	HRESULT __stdcall CreateInstance(IUnknown* pUnkOuter, REFIID riid, void **ppv);
	HRESULT __stdcall LockServer(BOOL fLock);
};

HRESULT __stdcall
DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	HRESULT hr;
	CPropertyClassFactory* pCpropertyClassFactory;
	pCpropertyClassFactory = new CPropertyClassFactory;

	if(NULL == pCpropertyClassFactory)
		return E_OUTOFMEMORY;

	if(CLSID_CPropertyClass != rclsid)
		return CLASS_E_CLASSNOTAVAILABLE;

	hr = pCpropertyClassFactory->QueryInterface(riid, ppv);
	pCpropertyClassFactory->Release();

	return hr;
}

HRESULT __stdcall
DllCanUnloadNow()
{
	if(0 == g_ActiveNoOfComponents && 0 == g_ActiveNoOfServerLocks)
	{
		return S_OK;
	}
	else
	{
		return S_FALSE;
	}
}

//
//	Implementing main class
//

CPropertyClass::CPropertyClass()
{
	m_cRef = 1;
	InterlockedIncrement(&g_ActiveNoOfComponents);
}

CPropertyClass::~CPropertyClass()
{
	InterlockedDecrement(&g_ActiveNoOfComponents);
}

HRESULT CPropertyClass::QueryInterface(const IID &riid, void **ppv)
{
	if(IID_IUnknown == riid)
	{
		*ppv = static_cast<IFirst*>(this);
	}
	else if(IID_IFirst == riid)
	{
		*ppv = static_cast<IFirst*>(this);
	}
	else if(IID_ISecond == riid)
	{
		*ppv = static_cast<ISecond*>(this);
	}
	else if(IID_IThird == riid)
	{
		*ppv = static_cast<IThird*>(this);
	}
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return S_OK;
}

ULONG CPropertyClass::AddRef()
{
	InterlockedIncrement(&m_cRef);
	return m_cRef;
}

ULONG CPropertyClass::Release()
{
	InterlockedDecrement(&m_cRef);
	if(0 == m_cRef)
	{
		delete this;
		return 0;
	}
	return m_cRef;
}

HRESULT CPropertyClass::FirstFunction()
{
	MessageBoxA(NULL, "First Function", "IFirst", MB_ICONEXCLAMATION);
	return S_OK;
}

HRESULT CPropertyClass::SecondFunction()
{
	MessageBoxA(NULL, "Second Function", "ISecond", MB_ICONEXCLAMATION);
	return S_OK;
}

HRESULT CPropertyClass::ThirdFunction()
{
	MessageBoxA(NULL, "Thirs Function", "IThird", MB_ICONEXCLAMATION);
	return S_OK;
}

//
//	Factory class
//

CPropertyClassFactory::CPropertyClassFactory()
{
	InterlockedIncrement(&g_ActiveNoOfServerLocks);
}

CPropertyClassFactory::~CPropertyClassFactory()
{
}

HRESULT CPropertyClassFactory::QueryInterface(const IID &riid, void **ppv)
{
	if(IID_IUnknown == riid)
	{
		*ppv = static_cast<IClassFactory*>(this);
	}
	else if(IID_IClassFactory == riid)
	{
		*ppv = static_cast<IClassFactory*>(this);
	}
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return S_OK;
}

ULONG CPropertyClassFactory::AddRef()
{
	InterlockedIncrement(&m_cRef);
	return m_cRef;
}

ULONG CPropertyClassFactory::Release()
{
	InterlockedDecrement(&m_cRef);
	if(0 == m_cRef)
	{
		delete this;
		return 0;
	}
	return m_cRef;
}

HRESULT CPropertyClassFactory::CreateInstance(IUnknown *pUnkOuter, const IID &riid, void **ppv)
{
	HRESULT hr;
	CPropertyClass* pCpropertyClass;
	pCpropertyClass = new CPropertyClass;

	if(NULL == pCpropertyClass)
		return E_OUTOFMEMORY;

	if(NULL != pUnkOuter)
		return CLASS_E_NOAGGREGATION;

	hr = pCpropertyClass->QueryInterface(riid, ppv);
	pCpropertyClass->Release();

	return hr;
}

HRESULT CPropertyClassFactory::LockServer(BOOL fLock)
{
	if(fLock)
	{
		InterlockedIncrement(&g_ActiveNoOfServerLocks);
	}
	else
	{
		InterlockedDecrement(&g_ActiveNoOfServerLocks);
	}
	return S_OK;
}