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
	void nop(void* dest, unsigned int size);
	void patch(void* dst, void* src, unsigned int size);

	HANDLE m_ProcessHandle;
	MODULEENTRY32 m_ModuleEntry;

public:
	Memory(wchar_t* process, wchar_t* moduleName);

	//process stuff
	HANDLE* getProcessHandle() { return &m_ProcessHandle; };
	MODULEENTRY32* getModuleEntry() { return &m_ModuleEntry; };

	//memory stuff
	void* readMemoryEx(void* src, unsigned int size);
	void patchEx(void* dst, void* src, unsigned int size);
	void nopEx(void* dst, unsigned int size);
};
