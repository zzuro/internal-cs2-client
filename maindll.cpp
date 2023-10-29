#define WIN32_LEAN_AND_MEAN   

#include <windows.h>
#include <iostream>
#include "hook/hook.h"

BOOL WINAPI MainThread(HMODULE hModule) {

    AllocConsole();
    FILE* file = nullptr;
    freopen_s(&file, "CONOUT$", "w", stdout);
    std::cout << "DLL injected!" << std::endl;

    bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)& hook::oPresent, hook::hkPresent);
			init_hook = true;
		}
	} while (!init_hook);

    while (!GetAsyncKeyState(VK_END))
    {
       
    }

UNLOAD:

    kiero::shutdown();
    if (file)
        fclose(file);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain(
    HANDLE hModule,
    DWORD dwReason,
    LPVOID lpReserved)

{

    if(dwReason == DLL_PROCESS_ATTACH){
        DisableThreadLibraryCalls((HMODULE)hModule);
        HANDLE thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, 0);
        if (thread) {
            CloseHandle(thread);
        }
    }

    return TRUE;
}