// uia.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	CoInitialize(NULL) ;

	IUIAutomation *pAutomation ;

	HRESULT hr = CoCreateInstance(__uuidof(CUIAutomation), NULL, CLSCTX_INPROC_SERVER, __uuidof(IUIAutomation), (void**)&pAutomation);
	if (SUCCEEDED(hr)) {
		printf("got IUIAutomation\r\n") ;

		IUIAutomationElement *pRootElement ;
		if (SUCCEEDED(pAutomation->GetRootElement(&pRootElement))) {
			BSTR bstrRootElementName ;
			pRootElement->get_CurrentName(&bstrRootElementName) ;

			IUIAutomationCondition *pCondition ;
			VARIANT varProperty ;
			VariantInit(&varProperty) ;
			varProperty.vt = VT_BSTR ;
			varProperty.bstrVal = SysAllocString(L"aboutButton") ;
			if (SUCCEEDED(pAutomation->CreatePropertyCondition(UIA_AutomationIdPropertyId, varProperty, &pCondition))) {
				IUIAutomationElement *pFound ;
				if (SUCCEEDED(pRootElement->FindFirst(TreeScope_Descendants, pCondition, &pFound))) {
					if (pFound != NULL) {
						printf("Found item\r\n") ;

						BSTR bstrName ;
						pFound->get_CurrentName(&bstrName) ;
						SysFreeString(bstrName) ;

						BSTR bstrItemType ;
						pFound->get_CurrentItemType(&bstrItemType) ;
						SysFreeString(bstrItemType) ;

						CONTROLTYPEID controlType ;
						pFound->get_CurrentControlType(&controlType) ;
						printf("Control type %d\r\n", controlType) ;

						IUIAutomationInvokePattern *pInvokePattern ;
						if (SUCCEEDED(pFound->GetCurrentPatternAs(UIA_InvokePatternId, __uuidof(IUIAutomationInvokePattern), (void **)&pInvokePattern))) {
							hr = pInvokePattern->Invoke() ;
						}
					} else
						printf("Did not find item\r\n") ;
				}
			}
		}
	} else
		printf("Unable to obtain IUIAutomation\r\n") ;

	return 0;
}

