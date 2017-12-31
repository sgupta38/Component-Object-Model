#include <windows.h>
#include <iostream>
#include "..\..\contentment3\cont.h"
#include "..\..\contentment3\interface.h"
using namespace std;

ISum *pIsum = NULL;
ISubstract *pIsubstract = NULL;
Imul *pImul = NULL;
Idiv *pIdiv = NULL;

int
main(
)
{
	int a, b, c, d, iChoice;

	HRESULT hr;
	CoInitialize(NULL);

	hr = CoCreateInstance(
					CLSID_Cmuldiv,
					NULL,
					CLSCTX_INPROC_SERVER,
					IID_mul,
					(void**)&pImul
					);
	if(FAILED(hr))
	{
		MessageBox(NULL, L"CoCreateInstance failed!", L"Application failed", MB_ICONERROR);
		return hr;
	}

	do
	{
		cout<<"\nenter your choice:";
		cout<<"\n1. Multiplication \n2. Division \n3. Addition \n4.Substratcion \n5.Exit";
		cin>>iChoice;


		switch(iChoice)
		{
		case 1:
			cout<<"\n Enter two numbers";
			cin>>a>>b;
			hr = pImul->mul(a, b, &c);
			if(FAILED(hr))
			{
				cout<<"\nfailed for multiplication";
				break;
			}

			cout<<"\n Nultiplication is: "<<c;
			break;

		case 2:
			cout<<"\n Enter two numbers";
			cin>>a>>b;
			hr = pImul->QueryInterface(IID_div, (void**)&pIdiv);
			if(FAILED(hr))
			{
				cout<<"\nQueryInterface failed for division";
				break;
			}

			hr = pIdiv->div(a, b, &c);
			if(FAILED(hr))
			{
				cout<<"\nfailed for division";
				break;
			}

			cout<<"\n Division is: "<<c;
			pIdiv->Release();
			break;

		case 3:
			cout<<"\n Enter two numbers";
			cin>>a>>b;
			hr = pImul->QueryInterface(IID_ISum, (void**)&pIsum);
			if(FAILED(hr))
			{
				cout<<"\nQueryInterface failed for addition";
				break;
			}

			hr = pIsum->AddNumbers(a, b, &c);
			if(FAILED(hr))
			{
				cout<<"\nfailed for addition";
				break;
			}

			cout<<"\n Addition is: "<<c;
			pIsum->Release();
			break;

		case 4:
			cout<<"\n Enter two numbers";
			cin>>a>>b;
			hr = pImul->QueryInterface(IID_ISubstract, (void**)&pIsubstract);
			if(FAILED(hr))
			{
				cout<<"\nQueryInterface failed for substraction";
				break;
			}

			hr = pIsubstract->SubNumbers(a, b, &c);
			if(FAILED(hr))
			{
				cout<<"\nfailed for substraction";
				break;
			}

			cout<<"\n Substraction is: "<<c;
			pIsubstract->Release();
			break;

		case 5:
			cout<<"\n Exiting";
			break;

		default:
			cout<<"\n Invalid Input";
			break;
		}
	}while(iChoice != 5);

	if(NULL != pImul)
	{
		pImul->Release();
	}

	CoUninitialize();
	return 0;
}