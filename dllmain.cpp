#pragma warning(disable : 4100) // Disable "lpReserved unreferenced formal parameter" warning
#include <stdexcept>
#include <Windows.h>

#include "hooks/hooks.h"
#include "sdk/interfaces/interfaces.h"
#include "sdk/sdk.h"

DWORD WINAPI init(HMODULE hModule)
{
    // Wait for the last module to be loaded, in order to safely continue
    while (!GetModuleHandleA("serverbrowser.dll"))
        Sleep(1000);

    try
    {
        // If using the debug configuration, create a console
        sdk::debug::create_console();
        // Initialize interfaces
        ifaces::init();
        // Initialize hooks
        hooks::init();
    }
    catch (const std::exception& e)
    {
        // Display pop up with error message
        MessageBoxA(NULL, e.what(), NULL, MB_OK | MB_ICONWARNING);
    }

    while (!(GetAsyncKeyState(VK_END) & 1))
        Sleep(1000);

    try
    {
        // Restore all hooked functions
        hooks::restore_all();
        // Free console
        sdk::debug::free_console();
    }
    catch (const std::exception& e)
    {
        MessageBoxA(NULL, e.what(), NULL, MB_OK | MB_ICONWARNING);
    }

    // Safely terminate
    FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        // Disable DLL_THREAD_ATTACH notifications
        DisableThreadLibraryCalls(hModule);
        CreateThread(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(init), hModule, NULL, NULL);
    }

    return TRUE;
}