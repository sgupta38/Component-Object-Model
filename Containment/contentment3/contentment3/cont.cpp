#include <windows.h>
#include "cont.h"
#include "interface.h"


long g_ActiveNoOfComponents = 0;
long g_ActiveNoOfLocks = 0;

class CmulDiv : public Imul, Idiv, ISum, ISubstract
{
private:
	long m_cRef;
	ISum *m_pIsum;
	ISubstract *m_pIsubstract;
public:
	CmulDiv();
	~CmulDiv();

	//	Iunknown
	HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();

	//Imul
	HRESULT __stdcall mul(int a, int b, int *c);

	//Idiv
	HRESULT __stdcall div(int a, int b, int *c);

	//Isum
	HRESULT __stdcall AddNumbers(int a, int b, int *c);

	//ISubstract
	HRESULT __stdcall SubNumbers(int a, int b, int *c);

	//inner component
	HRESULT InitializeInnerComponent();
};

class CmuldivFactory: public IClassFactory
{
private:
	long m_cRef;
public:

	CmuldivFactory();
	~CmuldivFactory();
	//Iunknown
	HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();

	//IclassFactory
	HRESULT __stdcall CreateInstance(IUnknown *pUnkOuter, REFIID riid, void** ppv);
	HRESULT __stdcall LockServer(BOOL fLock);
};

HRESULT __stdcall
DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	HRESULT hr;
	CmuldivFactory *pcmuldivFactory;
	pcmuldivFactory = new CmuldivFactory;

	if(NULL == pcmuldivFactory)
		return E_OUTOFMEMORY;

	if(rclsid != CLSID_Cmuldiv)
		return CLASS_E_CLASSNOTAVAILABLE;

	hr = pcmuldivFactory->QueryInterface(riid, ppv);
	pcmuldivFactory->Release();

	return hr;
};

HRESULT __stdcall
DllCanUnloadNow()
{
	if(0 == g_ActiveNoOfComponents && g_ActiveNoOfLocks)
	{
		return S_OK;
	}
	else
	{
		return S_FALSE;
	}
}

//
//	class implemetations
//

CmulDiv::CmulDiv()
{
	m_cRef = 1;
	m_pIsum = NULL;
	m_pIsubstract = NULL;
	InterlockedIncrement(&g_ActiveNoOfComponents);
}

CmulDiv::~CmulDiv()
{
	InterlockedDecrement(&g_ActiveNoOfComponents);
}

HRESULT CmulDiv::QueryInterface(REFIID riid, void** ppv)
{
	if(IID_IUnknown == riid)
	{
		*ppv = static_cast<Imul*>(this);
	}
	else if(IID_mul == riid)
	{
		*ppv = static_cast<Imul*>(this);
	}
	else if(IID_div == riid)
	{
		*ppv = static_cast<Idiv*>(this);
	}
	else if(IID_ISum == riid)
	{
		*ppv = static_cast<ISum*>(this);
	}
	else if(IID_ISubstract == riid)
	{
		*ppv = static_cast<ISubstract*>(this);
	}
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return S_OK;
}

ULONG CmulDiv::AddRef()
{
	InterlockedIncrement(&m_cRef);
	return m_cRef;
}

ULONG CmulDiv::Release()
{
	InterlockedDecrement(&m_cRef);
	if(0 == m_cRef)
	{
		delete this;
		return 0;
	}
	return m_cRef;
}

HRESULT CmulDiv::mul(int a, int b, int *c)
{
	*c = a*b;
	return S_OK;
}

HRESULT CmulDiv::div(int a, int b, int *c)
{
	*c = a/b;
	return S_OK;
}


HRESULT CmulDiv::InitializeInnerComponent()
{
	HRESULT hr;
	hr = CoCreateInstance(
						CLSID_CSumSubstract,
						NULL,
						CLSCTX_INPROC_SERVER,
						IID_ISum,
						(void**)&m_pIsum
						);

	if(FAILED(hr))
	{
		MessageBox(NULL, L"Failed to load inner component", L"CoCreateInstace Failed:IID_ISum", MB_ICONEXCLAMATION);
		return E_FAIL;
	}

	hr = m_pIsum->QueryInterface(IID_ISubstract, (void**)&m_pIsubstract);
	if(FAILED(hr))
	{
		MessageBox(NULL, L"Failed to load inner component", L"IID_ISubstract Failed", MB_ICONEXCLAMATION);
		return E_FAIL;
	}

	return hr;
}

HRESULT CmulDiv::AddNumbers(int a, int b, int *c)
{
	HRESULT hr;
	MessageBox(NULL, L"Inner Component", L"Addition", MB_ICONASTERISK);
	hr = m_pIsum->AddNumbers(a,b,c);
	return hr;
}

HRESULT CmulDiv::SubNumbers(int a, int b, int *c)
{
	HRESULT hr;
	MessageBox(NULL, L"Inner Component", L"Substratcion", MB_ICONASTERISK);
	hr = m_pIsubstract->SubNumbers(a,b,c);
	return hr;
}

//
//	Factory implementation
//

CmuldivFactory::CmuldivFactory()
{
	m_cRef=1;
	InterlockedIncrement(&g_ActiveNoOfLocks);
}

CmuldivFactory::~CmuldivFactory()
{

}

HRESULT CmuldivFactory::CreateInstance(IUnknown *pUnkOuter, const IID &riid, void **ppv)
{
	HRESULT hr;
	CmulDiv *pmuldivclass;
	pmuldivclass = new CmulDiv;

	if(NULL == pmuldivclass)
		return E_OUTOFMEMORY;

	if(NULL != pUnkOuter)
		return CLASS_E_NOAGGREGATION;

	//	inner component initialization
	hr = pmuldivclass->InitializeInnerComponent();
	if(FAILED(hr))
	{
		MessageBox(NULL, L"Failed to initilize inner component", L"Failure", MB_ICONEXCLAMATION);
		pmuldivclass->Release();
		return hr;
	}

	hr = pmuldivclass->QueryInterface(riid, ppv);
	pmuldivclass->Release();
	return hr;
}

HRESULT CmuldivFactory::LockServer(BOOL fLock)
{
	if(fLock)
	{
		InterlockedIncrement(&g_ActiveNoOfLocks);
	}
	else
	{
		InterlockedDecrement(&g_ActiveNoOfLocks);
	}

	return S_OK;
}

HRESULT CmuldivFactory::QueryInterface(const IID &riid, void **ppv)
{
	if(IID_IUnknown == riid)
	{
		*ppv = static_cast<IClassFactory*> (this);
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

ULONG CmuldivFactory::AddRef()
{
	InterlockedIncrement(&m_cRef);
	return m_cRef;
}

ULONG CmuldivFactory::Release()
{
	InterlockedDecrement(&m_cRef);
	if(0 == m_cRef)
	{
		delete this;
		return 0;
	}
	return m_cRef;
}
