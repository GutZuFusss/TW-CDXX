#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include "memory.h"

class PatternScan
{
public:
	PatternScan(Memory* pMem);
	void* patternScanEx(uintptr_t begin, uintptr_t end, char* pattern, char* mask);
	void* patternScanExModule(char* pattern, char* mask);
	
private:
	void* patternScan(char* base, size_t size, char* pattern, char* mask);

	Memory* m_pMemory;
};
