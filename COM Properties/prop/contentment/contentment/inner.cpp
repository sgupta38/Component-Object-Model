#include "inner.h"

//
//	globals
//

long g_ActiveNumberOfComponents=0;
long g_ActiveNumberOfServerLocks=0;

class CMulDiv: public IMultiplication, IDivision
{
private:
	long m_cRef;
public :
	CMulDiv();
	~CMulDiv();
	HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);
	ULONG __stdcall Addref();
	ULONG __stdcall Release();

	HRESULT __stdcall MultiPlication(int a,int b,int* c);
	HRESULT __stdcall Division(int a,int b,int* c);
};

class CMulDivFactory : public IClassFactory
{
private:
	long m_cRef;
public:
	CMulDivFactory();
	~CMulDivFactory();
	HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);
	ULONG __stdcall Addref();
	ULONG __stdcall Release();

	HRESULT __stdcall CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv);
	HRESULT __stdcall LockServer(BOOL fLock);
};


HRESULT __stdcall
DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	HRESULT hr;
	CMulDivFactory* pCmulDivFactory;
//	pCmulDivFactory = new CMulDivFactory;

	if(NULL == pCmulDivFactory)
		return E_OUTOFMEMORY;

	hr = pCmulDivFactory->CreateInstance(NULL, riid, ppv);
	pCmulDivFactory->Release();

	return hr;
}

HRESULT __stdcall
DllCanUnloadNow()
{
	if(0 == g_ActiveNumberOfComponents && 0 == g_ActiveNumberOfServerLocks)
	{
		return S_OK;
	}
	else
	{
		return S_FALSE;
	}
}


CMulDiv::CMulDiv()
{
	m_cRef = 1;
	InterlockedIncrement(&g_ActiveNumberOfComponents);
}

CMulDiv::~CMulDiv()
{
	InterlockedDecrement(&g_ActiveNumberOfComponents);
}

HRESULT CMulDiv::QueryInterface(REFIID riid, void **ppv)
{
	if(riid == IID_IUnknown)
	{
		*ppv = static_cast<IMultiplication*>(this);
	}
	else if(riid == IID_IMultiplication)
	{
		*ppv = static_cast<IMultiplication*>(this);
	}
	else if(riid == IID_IDivision)
	{
		*ppv = static_cast<IDivision*>(this);
	}
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}

	reinterpret_cast<IUnknown*>(ppv)->AddRef();
	return S_OK;
}

ULONG CMulDiv::Addref()
{
	InterlockedIncrement(&m_cRef);
	return m_cRef;
}

ULONG CMulDiv::Release()
{
	InterlockedDecrement(&m_cRef);
	if(0 == m_cRef)
	{
		delete this;
		return NULL;
	}
	return m_cRef;
}

HRESULT CMulDiv::MultiPlication(int a, int b, int* c)
{
	*c = a*b;
	return S_OK;
}

HRESULT CMulDiv::Division(int a, int b, int* c)
{
	if(0 == b)
	{
		MessageBox(NULL, L"Can't Divide by zero", L"Exception", MB_ICONASTERISK);
		return S_FALSE;
	}
	*c = a/b;
	return S_OK;
}

//
//	factory class
//

CMulDivFactory::CMulDivFactory()
{
	m_cRef = 1;
	InterlockedIncrement(&g_ActiveNumberOfServerLocks);
}

CMulDivFactory::~CMulDivFactory()
{
	InterlockedDecrement(&g_ActiveNumberOfServerLocks);
}

HRESULT CMulDivFactory::QueryInterface(REFIID riid, void **ppv)
{
	if(riid == IID_IUnknown)
	{
		*ppv = static_cast<IClassFactory*>(this);
	}
	else if(riid == IID_IClassFactory)
	{
		*ppv = static_cast<IClassFactory*>(this);
	}
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}

	reinterpret_cast<IUnknown*>(ppv)->AddRef();
	return S_OK;
}

ULONG CMulDivFactory::Addref()
{
	InterlockedIncrement(&m_cRef);
	return m_cRef;
}

ULONG CMulDivFactory::Release()
{
	InterlockedDecrement(&m_cRef);
	if(0 == m_cRef)
	{
		delete this;
		return NULL;
	}
	return m_cRef;
}

HRESULT CMulDivFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
	HRESULT hr;
	CMulDiv *pMulDiv;
//	pMulDiv = new CMulDiv;

	if(NULL == pMulDiv)
		return E_OUTOFMEMORY;

	if(NULL != pUnkOuter)
		return CLASS_E_NOAGGREGATION;

	hr = pMulDiv->QueryInterface(riid, ppv);
	pMulDiv->Release();

	return hr;
}

HRESULT CMulDivFactory::LockServer(BOOL fLock)
{
	if(fLock)
	{
		InterlockedIncrement(&g_ActiveNumberOfServerLocks);
	}
	else
	{
		InterlockedDecrement(&g_ActiveNumberOfServerLocks);
	}

	return S_OK;
}
