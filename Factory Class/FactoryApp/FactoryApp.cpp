/** @file FactoryApp.cpp
*
*   @brief Application which will use Factory Class functions exported by FactoryDll.
*
*   @author Sonu Gupta
*/

#include <windows.h>
#include <conio.h>
#include <iostream>
#include "..\FactoryDll\interface.h"
using namespace std;

ISum *pISum = NULL;
ISubstract *pISubstract = NULL;
IUnknown *pIUnknown = NULL;

int
main(
  )
{
  HRESULT hr;
  int iSum, iSub;

  CoInitialize(NULL);

  hr = CoCreateInstance(
                      CLSID_CSumSubstract,
                      pIUnknown,
                      CLSCTX_INPROC_SERVER,
                      IID_ISum,
                      (void**)&pISum
                      );
  if(SUCCEEDED(hr))
  {
    pISum->AddNumbers(46, 36, &iSum);
    cout<<"\nAddition of numbers = "<< iSum;
    pISum->QueryInterface(IID_ISubstract, (void**)&pISubstract);
    pISum->Release();

    pISubstract->SubNumbers(46,36, &iSub);
    cout<<"\nSubstraction of numbers = "<< iSub;
    pISubstract->Release();
  }
  else
  {
    cout<<"CoCreateInstance failed ErrorCode: "<<GetLastError();
  }

  CoUninitialize();

  _getch();
  return 0;
}
