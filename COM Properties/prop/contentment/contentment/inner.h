#include <windows.h>

class IMultiplication:public IUnknown
{
public:
	virtual HRESULT __stdcall MultiPlication(int a,int b,int* c) = 0;
};

class IDivision:public IUnknown
{
public:
	virtual HRESULT __stdcall Division(int a,int b,int* c) = 0;
};


//
//	GUID
//

// {F99F4DF0-3E86-42eb-8734-7C8B184F09B8}
const CLSID 
CLSID_CMULDIV = {0xf99f4df0, 0x3e86, 0x42eb, 0x87, 0x34, 0x7c, 0x8b, 0x18, 0x4f, 0x9, 0xb8};

// {CC8DA8B2-426D-4e73-B654-DE7CFE441384}
const IID
IID_IMultiplication = {0xcc8da8b2, 0x426d, 0x4e73, 0xb6, 0x54, 0xde, 0x7c, 0xfe, 0x44, 0x13, 0x84};

// {42408BE9-0F32-4e16-82A3-A9D51F8676A5}
const IID
IID_IDivision = {0x42408be9, 0xf32, 0x4e16, 0x82, 0xa3, 0xa9, 0xd5, 0x1f, 0x86, 0x76, 0xa5};