/** @file interface.cpp
*
*   @brief This delineates the basic COM Factory class usage.
*
*   @author Sonu Gupta
*/

#include "interface.h"
#include <windows.h>

LONG g_ActiveNoOfComponents = 0;
LONG g_ActiveNoOfServerLocks = 0;

BOOL __stdcall DllMain(
  HMODULE hModule,
  DWORD ul_reason_for_call,
  LPVOID lpReserved
  )
{
  switch(ul_reason_for_call)
  {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
    break;
  }
  return TRUE;
}

class CSumSubstract: public ISum, ISubstract
{
  private:
    long m_cRef;

  public:
    CSumSubstract();
    ~CSumSubstract();

    // Methods from IUnknown Interface
    ULONG __stdcall AddRef(void);
    ULONG __stdcall Release(void);
    HRESULT __stdcall QueryInterface(const IID &riid, void **ppv);

    // Methods from interface.h
    HRESULT __stdcall AddNumbers(int, int, int*);
    HRESULT __stdcall SubNumbers(int, int, int*);
};


// Factory class
class CSumSubstractFactory:public IClassFactory
{
  private:
    long m_Cref;

  public:
    CSumSubstractFactory();
    ~CSumSubstractFactory();

    // Methods from IUnknown Interface
    ULONG __stdcall AddRef(void);
    ULONG __stdcall Release(void);
    HRESULT __stdcall QueryInterface(const IID &riid, void **ppv);

    // Methods of IClassFactory
    HRESULT __stdcall CreateInstance(IUnknown *pUnkOuter, const IID &riid, void **ppv);
    HRESULT __stdcall LockServer(BOOL fLock);
};

CSumSubstract::CSumSubstract()
{
  m_cRef = 1;
  InterlockedIncrement(&g_ActiveNoOfComponents);
}

CSumSubstract::~CSumSubstract()
{
  InterlockedIncrement(&g_ActiveNoOfComponents);
}

HRESULT CSumSubstract::QueryInterface(const IID &riid, void **ppv)
{
  if(riid == IID_IUnknown)
  {
    *ppv = static_cast<ISum *>(this);
  }
  else if(riid == IID_ISum)
  {
    *ppv = static_cast<ISum *>(this);
  }
  else if(riid == IID_ISubstract)
  {
    *ppv = static_cast<ISubstract *>(this);
  }
  else
  {
    *ppv = NULL;
    return E_NOINTERFACE;
  }

  reinterpret_cast<IUnknown *>(*ppv)->AddRef();
  return S_OK;
}

ULONG CSumSubstract::AddRef()
{
  InterlockedIncrement(&m_cRef);
  return m_cRef;
}

ULONG CSumSubstract::Release()
{
  InterlockedDecrement(&m_cRef);
  if(0 == m_cRef)
  {
    delete(this);
    return NULL;
  }

  return m_cRef;
}

HRESULT CSumSubstract::AddNumbers(int a, int b, int *c)
{
  // Your implementation for addition
  *c = a+b;
  return S_OK;
}
HRESULT CSumSubstract::SubNumbers(int a, int b, int *c)
{
  // Your implementation for substraction
  *c = a-b;
  return S_OK;
}

//
//  Class factory implementation
//
CSumSubstractFactory::CSumSubstractFactory()
{
  m_Cref = 1;
}

CSumSubstractFactory::~CSumSubstractFactory()
{
}

HRESULT CSumSubstractFactory::QueryInterface(const IID &riid, void **ppv)
{
  if(riid == IID_IUnknown)
  {
    *ppv = static_cast<IClassFactory *>(this);
  }
  else if(riid == IID_IClassFactory)
  {
    *ppv = static_cast<IClassFactory *>(this);
  }
  else
  {
    *ppv = NULL;
    return E_NOINTERFACE;
  }

  reinterpret_cast<IUnknown *> (*ppv)->AddRef();
  return S_OK;
}

ULONG CSumSubstractFactory::AddRef()
{
  InterlockedIncrement(&m_Cref);
  return m_Cref;
}

ULONG CSumSubstractFactory::Release()
{
  InterlockedDecrement(&m_Cref);
  if(0 == m_Cref)
  {
    delete this;
    return 0;
  }

  return m_Cref;
}

HRESULT CSumSubstractFactory::CreateInstance(IUnknown *pUnkOuter, const IID &riid, void **ppv)
{
  if(NULL != pUnkOuter)
    return CLASS_E_NOAGGREGATION;

  HRESULT hr;
  CSumSubstract *pCSumSubstract;
  pCSumSubstract = new CSumSubstract;

  if(NULL == pCSumSubstract)
    return E_OUTOFMEMORY;

  hr = pCSumSubstract->QueryInterface(riid, ppv);
  pCSumSubstract->Release();

  return hr;
}

HRESULT CSumSubstractFactory::LockServer(BOOL fLock)
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

HRESULT __stdcall DllGetClassObject(REFCLSID clsid, REFIID riid, void** ppv)
{
  HRESULT hr;
  CSumSubstractFactory *pCSumSubstractFactory;

  if(clsid != CLSID_CSumSubstract)
    return CLASS_E_CLASSNOTAVAILABLE;

  pCSumSubstractFactory = new CSumSubstractFactory;
  if(NULL == pCSumSubstractFactory)
    return E_OUTOFMEMORY;

  hr = pCSumSubstractFactory->QueryInterface(riid, ppv);
  pCSumSubstractFactory->Release();

  return hr;
}

HRESULT __stdcall DllCanUnloadNow()
{
  if((g_ActiveNoOfComponents == 0) && (g_ActiveNoOfServerLocks ==0))
  {
    return S_OK;
  }
  else
  {
    return S_FALSE;
  }
}
