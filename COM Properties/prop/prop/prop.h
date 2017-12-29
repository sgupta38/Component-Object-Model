#include <windows.h>

// creating abstract intefces.

class IFirst: public IUnknown
{
public:
	virtual HRESULT __stdcall FirstFunction()=0;
};

class ISecond: public IUnknown
{
public:
	virtual HRESULT __stdcall SecondFunction()=0;
};

class IThird: public IUnknown
{
public:
	virtual HRESULT __stdcall ThirdFunction()=0;
};

//
//	assigning unique guid to class and interfaces
//

// {64ABD2A5-D591-432a-AB4B-C75288C0A6AD}
const CLSID 
CLSID_CPropertyClass = {0x64abd2a5, 0xd591, 0x432a, 0xab, 0x4b, 0xc7, 0x52, 0x88, 0xc0, 0xa6, 0xad};


// {EBE09EEB-474F-4dc1-ACA3-4E1EE24889FD}
const IID 
IID_IFirst = {0xebe09eeb, 0x474f, 0x4dc1, 0xac, 0xa3, 0x4e, 0x1e, 0xe2, 0x48, 0x89, 0xfd};

// {C17D8F40-AF6D-466d-A8C5-56D28E561C0B}

const IID 
IID_ISecond = {0xc17d8f40, 0xaf6d, 0x466d, 0xa8, 0xc5, 0x56, 0xd2, 0x8e, 0x56, 0x1c, 0xb};

// {D9E441A4-D071-4304-B585-2E5FCA4311B6}

const IID 
IID_IThird = {0xd9e441a4, 0xd071, 0x4304, 0xb5, 0x85, 0x2e, 0x5f, 0xca, 0x43, 0x11, 0xb6};

