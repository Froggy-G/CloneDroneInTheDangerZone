#include <Windows.h>
#include <iostream>
#include <vector>
#include "memory.h"
#include "utils.h"

DWORD WINAPI MainThread(HMODULE hModule)
{
    AllocConsole(); // create console
    SetConsoleTitle(L"CloneDroneInTheDangerZoneCheat"); //naming console
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    std::cout << "All my homies usin' dat shit\n";
    std::cout << "Use numpad to operate cheat\n";
    std::cout << "1. Endless energy(please wait 3 sec before use)(only 1st live), num2 to off.\n2. Endless skills, num4 to off\n";
    std::cout << "Only one can work at the same time\n";

    bool bEnergy = false;
    bool bSkills = false;
    
    Sleep(2000);
    uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"Clone Drone in the Danger Zone.exe"); // for .exe file
    moduleBase = (uintptr_t)GetModuleHandle(L"UnityPlayer.dll"); // for .dll file or null

    while (!GetAsyncKeyState(VK_END))
    {
        // Endless energy
        if (GetAsyncKeyState(VK_NUMPAD1))
        {
            if (!bEnergy)
            {
                bEnergy = true;
                std::cout << "Endless energy is Active\n";
            }

            while (bEnergy)
            {
                float* Energy = (float*)GetPointerAddress(moduleBase + mem::Energy, mem::EnergyOffsets);
                *Energy = 4.0f;
                Sleep(100);

                if (GetAsyncKeyState(VK_NUMPAD2))
                {
                    if (bEnergy)
                    {
                        bEnergy = false;
                        std::cout << "Endless energy is not Active\n";
                    }
                }
            }
        }

        // Endless skills
        if (GetAsyncKeyState(VK_NUMPAD3))
        {
            if (!bSkills)
            {
                bSkills = true;
                std::cout << "Endless skills is Active\n";
            }

            while (bSkills)
            {
                int* Skills = (int*)GetPointerAddress(moduleBase + mem::Skills, mem::SkillsOffsets);
                *Skills = 1;

                if (GetAsyncKeyState(VK_NUMPAD4))
                {
                    if (bSkills)
                    {
                        bSkills = false;
                        std::cout << "Endless skills is not Active\n";
                    }
                }
            }
        }
    }

    if (GetAsyncKeyState(VK_END))
    {
        fclose(f);
    }

    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0); // remove this dll
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, nullptr));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}