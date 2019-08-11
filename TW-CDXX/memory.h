#pragma once
#include <Windows.h>
#include <TlHelp32.h>

//process stuff
DWORD getProcessID(wchar_t* exeName);
MODULEENTRY32 getModuleEntry(DWORD dwProcID, wchar_t* moduleName);

//memory stuff
void Patch(void* dst, void* src, unsigned int size);
void PatchEx(HANDLE hProcess, void* dst, void* src, unsigned int size);
void Nop(HANDLE hProcess, void* dest, unsigned int size);
void NopEx(HANDLE hProcess, void* dst, unsigned int size);