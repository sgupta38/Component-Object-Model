/** @file interface.h
*
*   @brief Interface file declaring GUIDs for  Class and Interfaces.
*
*   @author Sonu Gupta
*/

#include <windows.h>

class ISum: public IUnknown
{
public:
  virtual HRESULT __stdcall AddNumbers(int, int, int*) = 0;
};

class ISubstract: public IUnknown
{
public:
  virtual HRESULT __stdcall SubNumbers(int, int, int*) = 0;
};

//
// @brief Make sure to provide guid, you can generate using Visual Studio itself.
//        Navigate to Tools--> CreateGUID
//        Simply copy and paste GUID here.
//


// {0B61EC71-3103-4025-ABE7-789A0E525DBB} - Class Guid
const CLSID	CLSID_CSumSubstract = {0xb61ec71, 0x3103, 0x4025, 0xab, 0xe7, 0x78, 0x9a, 0xe, 0x52, 0x5d, 0xbb};

// {6B4F9EA9-557D-4439-BABC-E57F6EC58280}
const IID	IID_ISum = {0x6b4f9ea9, 0x557d, 0x4439, 0xba, 0xbc, 0xe5, 0x7f, 0x6e, 0xc5, 0x82, 0x80};

// {D1A47F18-7B91-497d-BF75-5377D1112E53}
const IID	IID_ISubstract = {0xd1a47f18, 0x7b91, 0x497d, 0xbf, 0x75, 0x53, 0x77, 0xd1, 0x11, 0x2e, 0x53};