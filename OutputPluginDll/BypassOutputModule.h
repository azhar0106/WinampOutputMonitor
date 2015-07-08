
/*
    +----------------------------------------------------------------+
    | WinampOutputMonitor                                            |
    | Copyright (c) 2015 Syed Azhar.                                 |
    | All Rights Reserved.                                           |
    +----------------------------------------------------------------+
    
    +----------------------------------------------------------------+
    | BypassOutputModule.cpp                                         |
    +----------------------------------------------------------------+
*/


#ifndef BYPASS_OUTPUT_MODULE_H
#define BYPASS_OUTPUT_MODULE_H


#include "Winamp\OUT.H"
#include <Windows.h>


namespace WinampOutputBypass
{
    namespace BypassOutputModule
    {
        extern  Out_Module out;


        void	Config(HWND hwndParent);
        void	About(HWND hwndParent);
        void	Init();
        void	Quit();
        int		Open(int samplerate, int numchannels, int bitspersamp, int bufferlenms, int prebufferms);
        void	Close();
        int		Write(char *buf, int len);
        int		CanWrite();
        int		IsPlaying();
        int		Pause(int pause);
        void	SetVolume(int volume);
        void	SetPan(int pan);
        void	Flush(int t);
        int		GetOutputTime();
        int		GetWrittenTime();
    }

    namespace BypassOutputModule
    {
        namespace ExternalPlugin
        {
            extern  void    (*pointerToConfig)(HWND hwndParent)     ;
            extern  void    (*pointerToAbout)(HWND hwndParent)      ;
            extern  void    (*pointerToInit)(void)                  ;
            extern  void    (*pointerToQuit)(void)                  ;
            extern  int     (*pointerToOpen)(int samplerate, int numchannels, int bitspersamp, int bufferlenms, int prebufferms);
            extern  void    (*pointerToClose)(void)                 ;
            extern  int     (*pointerToWrite)(char *buf, int len)   ;
            extern  int     (*pointerToCanWrite)()                  ;
            extern  int     (*pointerToIsPlaying)()                 ;
            extern  int     (*pointerToPause)(int pause)            ;
            extern  void    (*pointerToSetVolume)(int volume)       ;
            extern  void    (*pointerToSetPan)(int pan)             ;
            extern  void    (*pointerToFlush)(int t)                ;
            extern  int     (*pointerToGetOutputTime)()             ;
            extern  int     (*pointerToGetWrittenTime)()            ;


            void    SetFunctionPointersToBlankFunctions();
            void    SetFunctionPointersToExternalFunctions();

            int     LoadExternalOutput();
            int     UnloadExternalOutput();
            int     FillFilenameOfExternalOutputDll();
        }

		namespace InteropDll
		{
			int     LoadExternalOutput();
			int     FillFilenameOfInteropDll();
		}
    }

}


#endif/*BYPASS_OUTPUT_MODULE_H*/
