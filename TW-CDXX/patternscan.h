#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include "memory.h"

void* patternScan(char* base, size_t size, char* pattern, char* mask);
void* patternScanEx(HANDLE hPRocess, uintptr_t begin, uintptr_t end, char* pattern, char* mask);
void* patternScanExModule(HANDLE hProcess, wchar_t* exeName, wchar_t* module, char* pattern, char* mask);