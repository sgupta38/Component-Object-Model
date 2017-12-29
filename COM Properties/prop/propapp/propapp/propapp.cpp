#include <windows.h>
#include <iostream>
#include <conio.h>
using namespace std;
#include "..\..\prop\prop.h"

IFirst* pIFirst = NULL;
ISecond* pISecond = NULL;
IThird* pIThird = NULL;

IUnknown* pIUnknownFromFirst = NULL;
IUnknown* pIUnknownFromSecond = NULL;
IFirst* pIFirstAgain = NULL;

int
main(
	)
{
	HRESULT hr;
	CoInitialize(NULL);

	hr = CoCreateInstance(
					CLSID_CPropertyClass,
					NULL,
					CLSCTX_INPROC_SERVER,
					IID_IFirst,
					(void**)&pIFirst
	);

	if(FAILED(hr))
	{
		cout<<"\n CoCreateInstance failed";
	}

	//1.Identity

	hr = pIFirst->QueryInterface(IID_IUnknown, (void**)&pIUnknownFromFirst);
	if(FAILED(hr))
	{
		cout<<"\n1. QI First failed!";
	}

	hr = pIFirst->QueryInterface(IID_ISecond, (void**)&pISecond);
	if(FAILED(hr))
	{
		cout<<"\n1. QI First failed!";
	}

	hr = pISecond->QueryInterface(IID_IUnknown, (void**)&pIUnknownFromSecond);
	if(FAILED(hr))
	{
		cout<<"\n1. QI Second failed!";
	}

	if(pIUnknownFromFirst == pIUnknownFromSecond)
	{
		cout<<"\n \"Identity\" is proved.";
	}

	//2.Predictability
	pIUnknownFromSecond->Release();
	pIUnknownFromSecond->Release();
	pISecond->Release();
	Sleep(5000);

	hr = pIFirst->QueryInterface(IID_ISecond, (void**)&pISecond);
	if(FAILED(hr))
	{
		cout<<"\n2. QI First failed!";
	}

	if(NULL != pISecond)
	{
		cout<<"\n \"Predictability\" is proved";
	}

	//3.Symmetry

	pISecond->Release();
	hr = pIFirst->QueryInterface(IID_ISecond, (void**)&pISecond);
	if(FAILED(hr))
	{
		cout<<"\n3. QI First failed!";
	}

	hr = pISecond->QueryInterface(IID_IFirst, (void**)&pIFirstAgain);
	if(FAILED(hr))
	{
		cout<<"\n3. QI First failed!";
	}

	if(pIFirst == pIFirstAgain)
	{
		cout<<"\n \"Symmetry\" is proved.";
	}

	//4.Reflexivity
	pISecond->Release();
	pIFirstAgain->Release();

	hr = pIFirst->QueryInterface(IID_IFirst, (void**)&pIFirstAgain);
	if(FAILED(hr))
	{
		cout<<"\n4. QI First failed!";
	}

	if(pIFirst == pIFirstAgain)
	{
		cout<<"\n \"Reflexivity is proved.\"";
	}


	//5.Transitivity
	pIFirstAgain->Release();
	hr = pIFirst->QueryInterface(IID_ISecond, (void**)&pISecond);
	if(FAILED(hr))
	{
		cout<<"\n5. QI First failed!";
	}

	hr = pISecond->QueryInterface(IID_IThird, (void**)&pIThird);
	if(FAILED(hr))
	{
		cout<<"\n5. QI Second failed!";
	}

	hr = pIThird->QueryInterface(IID_IFirst, (void**)&pIFirstAgain);
	if(FAILED(hr))
	{
		cout<<"\n5. QI Third failed!";
	}

	if(pIFirst == pIFirstAgain)
	{
		cout<<"\n\"Transitivity\" is proved.";
	}

	pIFirstAgain->Release();
	pISecond->Release();
	pIThird->Release();
	pIFirst->Release();

	_getch();

	CoUninitialize();
	return 0;
}