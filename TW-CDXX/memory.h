#pragma once
#include <Windows.h>
#include <TlHelp32.h>

class Memory
{
private:
	//process stuff
	DWORD getProcessID(wchar_t* exeName);
	MODULEENTRY32 getModuleEntry(DWORD dwProcID, wchar_t* moduleName);

	//memory stuff
	void nop(HANDLE hProcess, void* dest, unsigned int size);
	void patch(void* dst, void* src, unsigned int size);

	HANDLE m_ProcessHandle;
	MODULEENTRY32 m_ModuleEntry;

public:
	Memory(wchar_t* process, wchar_t* moduleName);

	//memory stuff
	void patchEx(void* dst, void* src, unsigned int size);
	void nopEx(void* dst, unsigned int size);
};
