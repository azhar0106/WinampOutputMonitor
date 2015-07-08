
/*
    +----------------------------------------------------------------+
    | WinampOutputMonitor                                            |
    | Copyright (c) 2015 Syed Azhar.                                 |
    | All Rights Reserved.                                           |
    +----------------------------------------------------------------+
    
    +----------------------------------------------------------------+
    | Constants.h                                                    |
    +----------------------------------------------------------------+
*/


#ifndef CONSTANTS_H
#define CONSTANTS_H


namespace WinampOutputBypass
{
    namespace Constants
    {
        static const char*      pluginName      =  "Winamp Output Monitor";
        static const wchar_t*   pluginNameWide  = L"Winamp Output Monitor";
        static const char*      pluginNameWithVersion = "Winamp Output Monitor v0.0";

        static const wchar_t*   copyrightNotice  = L"Copyright (c) 2015 Syed Azhar.\nAll rights reserved.";

        static const char*      externalOutputPluginName = "out_ds.dll";
		static const char*      interopDllName = "OutputPluginInteropDll.dll";
    }
}


#endif/*CONSTANTS_H*/
