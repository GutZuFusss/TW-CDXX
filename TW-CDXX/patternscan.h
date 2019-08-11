#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include "memory.h"

class PatternScan
{
public:
	PatternScan(Memory* mem);
	void* patternScanEx(uintptr_t begin, uintptr_t end, char* pattern, char* mask);
	void* patternScanExModule(wchar_t* exeName, wchar_t* module, char* pattern, char* mask);
	
private:
	void* patternScan(char* base, size_t size, char* pattern, char* mask);

	Memory* m_pMemory;
};
