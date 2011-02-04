// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

HMODULE oleAccModule = NULL ;

HMODULE getOleAccModule() {
	return oleAccModule ;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call) {
		case DLL_PROCESS_ATTACH:
			oleAccModule = LoadLibrary(L"oleacc.dll") ;

			if (oleAccModule == 0)
				return FALSE ;

			break ;
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	return TRUE;
}

