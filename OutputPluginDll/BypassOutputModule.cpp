
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


#include "BypassOutputModule.h"
#include "Winamp\OUT.H"
#include "Winamp\wa_ipc.h"
#include "Constants.h"
#include <Windows.h>


//using namespace OutputPluginManagedDll;


namespace WinampOutputBypass
{
    namespace BypassOutputModule
    {
		/*public ref class ManagedGlobals abstract sealed
		{
		public:
			static ManagedOutputModule^ managedOutputModule = gcnew ManagedOutputModule();
		};*/

		
        int outputModuleId;     // This one is filled in by Winamp

        
        Out_Module out = {
            OUT_VER,                                                // module version (OUT_VER)
            const_cast<char*>(Constants::pluginNameWithVersion),    // description of module, with version string
            reinterpret_cast<intptr_t>(&outputModuleId),            // module id. each input module gets its own. non-nullsoft modules should
								                                    // be >= 65536.
            0,  // winamp's main window (filled in by winamp)
            0,  // DLL instance handle (filled in by winamp)

            Config,    // configuration dialog
            About,     // about dialog

            Init,  // called when loaded
            Quit,  // called when unloaded
            
            Open,  // returns >=0 on success, <0 on failure
                    // NOTENOTENOTE: bufferlenms and prebufferms are ignored in most if not all output plug-ins. 
		            //    ... so don't expect the max latency returned to be what you asked for.
		            // returns max latency in ms (0 for diskwriters, etc)
		            // bufferlenms and prebufferms must be in ms. 0 to use defaults. 
		            // prebufferms must be <= bufferlenms
		            // pass bufferlenms==-666 to tell the output plugin that it's clock is going to be used to sync video
		            //   out_ds turns off silence-eating when -666 is passed
            Close, // close the ol' output device.

            Write,     // 0 on success. Len == bytes to write (<= 8192 always). buf is straight audio data. 
                        // 1 returns not able to write (yet). Non-blocking, always.
            CanWrite,  // returns number of bytes possible to write at a given time. 
						// Never will decrease unless you call Write (or Close, heh)

            IsPlaying,     // non0 if output is still going or if data in buffers waiting to be
                            // written (i.e. closing while IsPlaying() returns 1 would truncate the song
            Pause,         // returns previous pause state

            SetVolume, // volume is 0-255
            SetPan,    // pan is -128 to 128
            
            Flush, // flushes buffers and restarts output at time t (in ms)
                    // (used for seeking)

            GetOutputTime, // returns played time in MS
            GetWrittenTime // returns time written in MS (used for synching up vis stuff)
            };


        #ifdef DEBUG_ENABLE_LOGGING
        Logger logger;
        #endif


        void	Config(HWND hwndParent)
        {
            MessageBox(NULL,Constants::copyrightNotice,Constants::pluginNameWide,MB_OK);
			ExternalPlugin::pointerToConfig(hwndParent);
        }
        void	About (HWND hwndParent)
        {
            MessageBox(NULL,Constants::copyrightNotice,Constants::pluginNameWide,MB_OK);
            ExternalPlugin::pointerToAbout(hwndParent);
        }
        void	Init()
        {
            ExternalPlugin::LoadExternalOutput();
			//ManagedGlobals::managedOutputModule->Init();
            ExternalPlugin::pointerToInit();
        }
        void	Quit()
        {
            ExternalPlugin::pointerToQuit();
			//ManagedGlobals::managedOutputModule->Quit();
            ExternalPlugin::UnloadExternalOutput();
        }
        int		Open(int samplerate, int numchannels, int bitspersamp, int bufferlenms, int prebufferms)
        {
            int returnValue=0;


            returnValue=ExternalPlugin::pointerToOpen(samplerate, numchannels, bitspersamp, bufferlenms, prebufferms);


            return returnValue;
        }
        void	Close()
        {
            ExternalPlugin::pointerToClose();
        }
        int		Write(char *buf, int len)
        {
            static int returnValue=0;


            returnValue=ExternalPlugin::pointerToWrite(buf, len);


            return returnValue;
        }
        int		CanWrite()
        {
            static int returnValue=0;


            returnValue=ExternalPlugin::pointerToCanWrite();


            return returnValue;
        }
        int		IsPlaying()
        {
            static int returnValue=0;


            returnValue=ExternalPlugin::pointerToIsPlaying();


            return returnValue;
        }
        int		Pause(int pause)
        {
            int returnValue=0;


            returnValue=ExternalPlugin::pointerToPause(pause);


            return returnValue;
        }
        void	SetVolume(int volume)
        {
            ExternalPlugin::pointerToSetVolume(volume);
        }
        void	SetPan(int pan)
        {
            ExternalPlugin::pointerToSetPan(pan);
        }
        void	Flush(int t)
        {
            ExternalPlugin::pointerToFlush(t);
        }
        int		GetOutputTime()
        {
            static int returnValue=0;


            returnValue=ExternalPlugin::pointerToGetOutputTime();


            return returnValue;
        }
        int		GetWrittenTime()
        {
            static int returnValue=0;

            
            returnValue=ExternalPlugin::pointerToGetWrittenTime();


            return returnValue;
        }
    }//BypassOutputModule

    namespace BypassOutputModule
    {
        namespace ExternalPlugin
        {
            Out_Module *out=0;


            // Function Pointers
            void    (*pointerToConfig)(HWND hwndParent)     =0;
            void    (*pointerToAbout)(HWND hwndParent)      =0;
            void    (*pointerToInit)(void)                  =0;
            void    (*pointerToQuit)(void)                  =0;
            int     (*pointerToOpen)(int samplerate, int numchannels, int bitspersamp, int bufferlenms, int prebufferms)=0;
            void    (*pointerToClose)(void)                 =0;
            int     (*pointerToWrite)(char *buf, int len)   =0;
            int     (*pointerToCanWrite)()                  =0;
            int     (*pointerToIsPlaying)()                 =0;
            int     (*pointerToPause)(int pause)            =0;
            void    (*pointerToSetVolume)(int volume)       =0;
            void    (*pointerToSetPan)(int pan)             =0;
            void    (*pointerToFlush)(int t)                =0;
            int     (*pointerToGetOutputTime)()             =0;
            int     (*pointerToGetWrittenTime)()            =0;

            // Blank Functions
            void	Config(HWND hwndParent){ MessageBox(NULL,Constants::copyrightNotice,Constants::pluginNameWide,MB_OK); }
            void	About (HWND hwndParent){ MessageBox(NULL,Constants::copyrightNotice,Constants::pluginNameWide,MB_OK); }
            void	Init(){}
            void	Quit(){}
            int		Open(int samplerate, int numchannels, int bitspersamp, int bufferlenms, int prebufferms){ return 0; }
            void	Close(){}
            int		Write(char *buf, int len){ return 0; }
            int		CanWrite(){ return 0; }
            int		IsPlaying(){ return 0; }
            int		Pause(int pause){ return 0; }
            void	SetVolume(int volume){}
            void	SetPan(int pan){}
            void	Flush(int t){}
            int		GetOutputTime(){ return 0; }
            int		GetWrittenTime(){ return 0; }

            void    SetFunctionPointersToBlankFunctions()
            {
                pointerToConfig=Config;
                pointerToAbout=About;
                pointerToInit=Init;
                pointerToQuit=Quit;
                pointerToOpen=Open;
                pointerToClose=Close;
                pointerToWrite=Write;
                pointerToCanWrite=CanWrite;
                pointerToIsPlaying=IsPlaying;
                pointerToPause=Pause;
                pointerToSetVolume=SetVolume;
                pointerToSetPan=SetPan;
                pointerToFlush=Flush;
                pointerToGetOutputTime=GetOutputTime;
                pointerToGetWrittenTime=GetWrittenTime;
            }
            void    SetFunctionPointersToExternalFunctions()
            {
                pointerToConfig=out->Config;
                pointerToAbout=out->About;
                pointerToInit=out->Init;
                pointerToQuit=out->Quit;
                pointerToOpen=out->Open;
                pointerToClose=out->Close;
                pointerToWrite=out->Write;
                pointerToCanWrite=out->CanWrite;
                pointerToIsPlaying=out->IsPlaying;
                pointerToPause=out->Pause;
                pointerToSetVolume=out->SetVolume;
                pointerToSetPan=out->SetPan;
                pointerToFlush=out->Flush;
                pointerToGetOutputTime=out->GetOutputTime;
                pointerToGetWrittenTime=out->GetWrittenTime;
            }


            HMODULE     handleToExternalOutputDll       =0;
            Out_Module* (*pointerToExportedFunction)()	=0;
            char        *filenameOfExternalOutputDll    =0;
            
            int     LoadExternalOutput()
            {
                int returnValue=0;


                SetFunctionPointersToBlankFunctions();


                returnValue=FillFilenameOfExternalOutputDll();
                if( !returnValue )
                {
                    return 0;
                }


	            handleToExternalOutputDll = LoadLibraryA(filenameOfExternalOutputDll);
                if(!handleToExternalOutputDll)
                {
                    MessageBox(0,L"External Output Dll could not be loaded.",WinampOutputBypass::Constants::pluginNameWide,MB_OK);
                    return 0;
                }
                
		        pointerToExportedFunction = (Out_Module*(*)())GetProcAddress(handleToExternalOutputDll,"winampGetOutModule");
		        if(!pointerToExportedFunction)
                {
                    MessageBox(0,L"Could not get exported function.",WinampOutputBypass::Constants::pluginNameWide,MB_OK);
                    return 0;
                }
                
			    out = pointerToExportedFunction();
			    if(!out)
                {
                    MessageBox(0,L"Exported function did not return output module.",WinampOutputBypass::Constants::pluginNameWide,MB_OK);
                    return 0;
                }


                SetFunctionPointersToExternalFunctions();


                return 1;
            }
            int     UnloadExternalOutput()
            {
                int returnValue=0;
                
                if( !handleToExternalOutputDll )
                {
                    MessageBox(0,L"External Output Dll was not loaded.",WinampOutputBypass::Constants::pluginNameWide,MB_OK);
                    return 0;
                }
                returnValue=FreeLibrary(handleToExternalOutputDll);
                if(!returnValue)
                {
                    MessageBox(0,L"External Output Dll could not be unloaded.",WinampOutputBypass::Constants::pluginNameWide,MB_OK);
                    return 0;
                }


                SetFunctionPointersToBlankFunctions();


                return 1;
            }
            int     FillFilenameOfExternalOutputDll()
            {
                char* pluginDirectory=0;
                int bufferLength=0;


                pluginDirectory	=	(char*)SendMessage(WinampOutputBypass::BypassOutputModule::out.hMainWindow,WM_WA_IPC,0,IPC_GETPLUGINDIRECTORY);
                if(!pluginDirectory)
                {
                    MessageBox(0,L"Winamp did not return plug-in directory location.",WinampOutputBypass::Constants::pluginNameWide,MB_OK);
                    return 0;
                }


                bufferLength = strlen(pluginDirectory)+1+strlen(WinampOutputBypass::Constants::externalOutputPluginName)+1;
                filenameOfExternalOutputDll = new char[bufferLength];
                if(!filenameOfExternalOutputDll)
                {
                    MessageBox(0,L"Could not allocate memory to store plug-in name.",WinampOutputBypass::Constants::pluginNameWide,MB_OK);
                    return 0;
                }


                strcpy_s(filenameOfExternalOutputDll,bufferLength,pluginDirectory);
                strcat_s(filenameOfExternalOutputDll,bufferLength,"\\");
                strcat_s(filenameOfExternalOutputDll,bufferLength,WinampOutputBypass::Constants::externalOutputPluginName);


                return 1;
            }
        }//ExternalPlugin
    }//BypassOutputModule

	namespace BypassOutputModule
	{
		namespace InteropDll
		{
			HMODULE     handleToInteropDll = 0;
			Out_Module* (*pointerToExportedFunction)() = 0;
			char        *filenameOfInteropDll = 0;

			int     LoadExternalOutput()
			{
				int returnValue = 0;



				returnValue = FillFilenameOfInteropDll();
				if (!returnValue)
				{
					return 0;
				}


				handleToInteropDll = LoadLibraryA(filenameOfInteropDll);
				if (!handleToInteropDll)
				{
					MessageBox(0, L"External Output Dll could not be loaded.", WinampOutputBypass::Constants::pluginNameWide, MB_OK);
					return 0;
				}

				pointerToExportedFunction = (Out_Module*(*)())GetProcAddress(handleToInteropDll, "Init");
				if (!pointerToExportedFunction)
				{
					MessageBox(0, L"Could not get exported function.", WinampOutputBypass::Constants::pluginNameWide, MB_OK);
					return 0;
				}


				return 1;
			}
			int     FillFilenameOfInteropDll()
			{
				char* pluginDirectory = 0;
				int bufferLength = 0;


				pluginDirectory = (char*)SendMessage(WinampOutputBypass::BypassOutputModule::out.hMainWindow, WM_WA_IPC, 0, IPC_GETPLUGINDIRECTORY);
				if (!pluginDirectory)
				{
					MessageBox(0, L"Winamp did not return plug-in directory location.", WinampOutputBypass::Constants::pluginNameWide, MB_OK);
					return 0;
				}


				bufferLength = strlen(pluginDirectory) + 1 + strlen(WinampOutputBypass::Constants::externalOutputPluginName) + 1;
				filenameOfInteropDll = new char[bufferLength];
				if (!filenameOfInteropDll)
				{
					MessageBox(0, L"Could not allocate memory to store plug-in name.", WinampOutputBypass::Constants::pluginNameWide, MB_OK);
					return 0;
				}


				strcpy_s(filenameOfInteropDll, bufferLength, pluginDirectory);
				strcat_s(filenameOfInteropDll, bufferLength, "\\");
				strcat_s(filenameOfInteropDll, bufferLength, WinampOutputBypass::Constants::interopDllName);


				return 1;
			}
		}
	}
}//WinampOutputBypass


/*
______________

Documentation:
______________

namespace WinampOutputBypass
{
    namespace BypassOutputModule
    {
        Defines an Out_Module structure which is exported to Winamp.
        Functions here are part of the structure.
        These functions call pointersToFunctions in ExternalPlugin namespace.
    }

    namespace BypassOutputModule
    {
        namespace ExternalPlugin
        {
            Contains everything required to get hold of an external output module.
            - Exploses the pointers to module functions.
            - Loads external module and sets all pointers to the external functions
            - If load fails then pointers point to blank functions.
        }
    }
}

*/