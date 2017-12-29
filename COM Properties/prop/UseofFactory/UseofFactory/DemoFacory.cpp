#include <windows.h>
#include "..\..\prop\prop.h"
#include <iostream>
#include <conio.h>
using namespace std;

IClassFactory* pIClassFactory = NULL;
IFirst* pIFirst = NULL;
ISecond* pISecond = NULL;

int
main(
	)
{
	HRESULT hr;

	CoInitialize(NULL);
	hr = CoGetClassObject(
					CLSID_CPropertyClass,
					CLSCTX_INPROC_SERVER,
					NULL,						// this parameter is used in DCOM CoServerInfo
					IID_IClassFactory,
					(void**)&pIClassFactory
					);

	if(SUCCEEDED(hr))
	{
		hr = pIClassFactory->CreateInstance(NULL, IID_IFirst, (void**)&pIFirst);
		if(FAILED(hr))
		{
			cout<<" \n Createinstace failed.";
		}

	}

	hr = pIFirst->FirstFunction();
	pIFirst->Release();

	pIClassFactory->LockServer(TRUE);
	//	10,000 lines of code
	Sleep(5000);

	hr = pIClassFactory->CreateInstance(NULL, IID_ISecond, (void**)&pISecond);
	if(FAILED(hr))
	{
		cout<<" \n Createinstace failed.";
	}

	hr = pISecond->SecondFunction();
	pISecond->Release();

	// workdone 
	pIClassFactory->LockServer(FALSE);
	pIClassFactory->Release();

	CoUninitialize();
	_getch();
	return 0;
}
