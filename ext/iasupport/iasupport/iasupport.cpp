
#include "stdafx.h"

HRESULT getAccessibleObjectFromWindow(HWND hwnd, IAccessible **pAccessible) {
	LPFNACCESSIBLEOBJECTFROMWINDOW lpfnAccessibleObjectFromWindow ;

	lpfnAccessibleObjectFromWindow = (LPFNACCESSIBLEOBJECTFROMWINDOW)GetProcAddress(getOleAccModule(), "AccessibleObjectFromWindow");

	return lpfnAccessibleObjectFromWindow(hwnd, OBJID_CLIENT, IID_IAccessible, (void**)pAccessible) ;
}

extern "C"
__declspec( dllexport ) int get_accChildCount(HWND control_hwnd) {
	IAccessible *pAccessible ;

	HRESULT hr = getAccessibleObjectFromWindow(control_hwnd, &pAccessible) ;
	if (SUCCEEDED(hr)) {
		long childCount ;

		pAccessible->get_accChildCount(&childCount) ;
		return childCount ;
	} else {
		return 0 ;
	}
}

extern "C"
__declspec( dllexport ) long get_accRole(HWND control_hwnd, long childId) {
	IAccessible *pAccessible ;

	HRESULT hr = getAccessibleObjectFromWindow(control_hwnd, &pAccessible) ;
	if (SUCCEEDED(hr)) {
		VARIANT varID ;
		VariantInit(&varID) ;
		varID.vt = VT_I4 ;
		varID.lVal = childId ;

		VARIANT varRole ;

		hr = pAccessible->get_accRole(varID, &varRole) ;
		if (SUCCEEDED(hr)) {
			return varRole.lVal ;
		} else
			return 0 ;
	} else {
		return 0 ;
	}
}

extern "C"
__declspec( dllexport ) int get_accName(HWND control_hwnd, long childId, char *pName, int name_len) {
	IAccessible *pAccessible ;

	HRESULT hr = getAccessibleObjectFromWindow(control_hwnd, &pAccessible) ;
	if (FAILED(hr)) return 0 ;
	
	VARIANT varID ;
	VariantInit(&varID) ;
	varID.vt = VT_I4 ;
	varID.lVal = childId ;

	BSTR bstrName ;

	hr = pAccessible->get_accName(varID, &bstrName) ;
	if (FAILED(hr)) return 0 ;

	char *pszName = _com_util::ConvertBSTRToString(bstrName) ;

	if (pName == NULL) {
		int len = strlen(pszName) ;
		delete[] pszName ;
		SysFreeString(bstrName) ;

		return len ;
	} else {
		strncpy(pName, pszName, name_len - 1) ;
		pName[name_len] = '\0' ;
		delete[] pszName ;
		SysFreeString(bstrName) ;
		return name_len ;
	}
}

extern "C"
__declspec( dllexport ) bool is_accessible(HWND control_hwnd, long childId) {
	IAccessible *pAccessible ;

	HRESULT hr = getAccessibleObjectFromWindow(control_hwnd, &pAccessible) ;
	if (FAILED(hr)) return 0 ;

	VARIANT varID ;
	VariantInit(&varID) ;
	varID.vt = VT_I4 ;
	varID.lVal = childId ;

	IDispatch *pDispatch ;
	hr = pAccessible->get_accChild(varID, &pDispatch) ;
	printf("get_accChild for child %d hr = 0x%x\r\n", childId, hr) ;
	
	if (hr == S_OK)
		return true ;
	else
		return false ;
}
