﻿#include <Windows.h>
#include <iostream>
#include <vector>
#include <map>
#include "memory.h"
#include "utils.h"

void ReverseBoolValue(bool* value)
{
    *value = !*value;
    std::cout << "Operation is " << *value << "\n";
}

DWORD WINAPI MainThread(HMODULE hModule)
{
    AllocConsole(); // create console
    SetConsoleTitle(L"CloneDroneInTheDangerZoneCheat"); //naming console
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    std::cout << "All my homies usin' dat shit\n";
    std::cout << "Use numpad to operate cheat\n";
    std::cout << "1. Endless energy(only 1st live)\n2. Endless skills\n";

    bool bEnergy = false;
    bool bSkills = false;
    
    uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"Clone Drone in the Danger Zone.exe"); // for .exe file
    moduleBase = (uintptr_t)GetModuleHandle(L"UnityPlayer.dll"); // for .dll file or null

    while (!GetAsyncKeyState(VK_END))
    {
        // ALL FUNCTIONS:
        // Endless energy
        if (bEnergy)
        {
            float* Energy = (float*)GetPointerAddress(moduleBase + mem::Energy, mem::EnergyOffsets);
            *Energy = 4.0f;
            Sleep(100);
        }

        // Endless skills
        if (bSkills)
        {
            int* Skills = (int*)GetPointerAddress(moduleBase + mem::Skills, mem::SkillsOffsets);
            *Skills = 1;
        }

        if (GetAsyncKeyState(VK_NUMPAD1) & 1)
        {
            ReverseBoolValue(&bEnergy);
        }

        if (GetAsyncKeyState(VK_NUMPAD2) & 1)
        {
            ReverseBoolValue(&bSkills);
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