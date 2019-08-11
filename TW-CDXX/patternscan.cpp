#include "patternscan.h"

PatternScan::PatternScan(Memory* mem)
{
	m_pMemory = mem;
}

void* PatternScan::patternScan(char* base, size_t size, char* pattern, char* mask)
{
	size_t patternLength = strlen(mask);

	for (unsigned int i = 0; i < size - patternLength; i++)
	{
		bool found = true;
		for (unsigned int j = 0; j < patternLength; j++)
		{
			if (mask[j] != '?' && pattern[j] != *(base + i + j))
			{
				found = false;
				break;
			}
		}
		if (found)
		{
			return (void*)(base + i);
		}
	}
	return nullptr;
}

void* PatternScan::patternScanEx(uintptr_t begin, uintptr_t end, char* pattern, char* mask)
{
	uintptr_t currentChunk = begin;
	SIZE_T bytesRead;

	while (currentChunk < end)
	{
		char buffer[4096];

		DWORD oldprotect;
		VirtualProtectEx(*m_pMemory->getProcessHandle(), (void*)currentChunk, sizeof(buffer), PAGE_EXECUTE_READWRITE, &oldprotect);
		ReadProcessMemory(*m_pMemory->getProcessHandle(), (void*)currentChunk, &buffer, sizeof(buffer), &bytesRead);
		VirtualProtectEx(*m_pMemory->getProcessHandle(), (void*)currentChunk, sizeof(buffer), oldprotect, &oldprotect);

		if (bytesRead == 0)
		{
			return nullptr;
		}

		void* internalAddress = patternScan((char*)& buffer, bytesRead, pattern, mask);

		if (internalAddress != nullptr)
		{
			//calculate from internal to external
			uintptr_t offsetFromBuffer = (uintptr_t)internalAddress - (uintptr_t)& buffer;
			return (void*)(currentChunk + offsetFromBuffer);
		}
		else
		{
			//advance to next chunk
			currentChunk = currentChunk + bytesRead;
		}
	}
	return nullptr;
}

void* PatternScan::patternScanExModule(char* pattern, char* mask)
{
	MODULEENTRY32* pModEntry = m_pMemory->getModuleEntry();

	if (!pModEntry->th32ModuleID)
	{
		return nullptr;
	}

	uintptr_t begin = (uintptr_t)pModEntry->modBaseAddr;
	uintptr_t end = begin + pModEntry->modBaseSize;
	return patternScanEx(begin, end, pattern, mask);
}
