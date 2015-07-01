
/*
    +----------------------------------------------------------------+
    | WinampOutputMonitor                                            |
    | Copyright (c) 2015 Syed Azhar.                                 |
    | All Rights Reserved.                                           |
    +----------------------------------------------------------------+
    
    +----------------------------------------------------------------+
    | Main.h                                                    |
    +----------------------------------------------------------------+
*/


#include "Winamp\OUT.H"
#include "BypassOutputModule.h"
#include "Constants.h"
#include <Windows.h>


extern "C"
__declspec( dllexport )
Out_Module* winampGetOutModule()
{
    return &WinampOutputBypass::BypassOutputModule::out;
}


BOOL APIENTRY DllMain(
    HANDLE hModule, 
    DWORD  ul_reason_for_call, 
    LPVOID lpReserved
    )
{
    
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	default:
		break;
	}

    return TRUE;
}
