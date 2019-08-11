#include "memory.h"

Memory::Memory(wchar_t* process, wchar_t* moduleName)
{
	DWORD processID = getProcessID(process);
	m_ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, false, processID);
	m_ModuleEntry = getModuleEntry(processID, moduleName);
}

DWORD Memory::getProcessID(wchar_t* exeName)
{
	PROCESSENTRY32 procEntry = { 0 };
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if(!hSnapshot)
	{
		return 0;
	}

	procEntry.dwSize = sizeof(procEntry);

	if(!Process32First(hSnapshot, &procEntry))
		return 0;

	do
	{
		if(!wcscmp(procEntry.szExeFile, exeName))
		{
			CloseHandle(hSnapshot);
			return procEntry.th32ProcessID;
		}
	} while(Process32Next(hSnapshot, &procEntry));

	CloseHandle(hSnapshot);
	return 0;
}

MODULEENTRY32 Memory::getModuleEntry(DWORD dwProcID, wchar_t* moduleName)
{
	MODULEENTRY32 modEntry = { 0 };

	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcID);

	if(hSnapshot != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 curr = { 0 };

		curr.dwSize = sizeof(MODULEENTRY32);
		if(Module32First(hSnapshot, &curr))
		{
			do
			{
				if(!wcscmp(curr.szModule, moduleName))
				{
					modEntry = curr;
					break;
				}
			} while(Module32Next(hSnapshot, &curr));
		}
		CloseHandle(hSnapshot);
	}
	return modEntry;
}

void* Memory::readMemoryEx(void* src, unsigned int size)
{
	int buffer = 0;
	DWORD oldprotect;
	VirtualProtectEx(m_ProcessHandle, src, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	ReadProcessMemory(m_ProcessHandle, src, &buffer, size, NULL);
	VirtualProtectEx(m_ProcessHandle, src, size, oldprotect, &oldprotect);
	return (void*)buffer;
}

void Memory::patch(void* dst, void* src, unsigned int size)
{
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	memcpy(dst, src, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}

void Memory::patchEx(void* dst, void* src, unsigned int size)
{
	DWORD oldprotect;
	VirtualProtectEx(m_ProcessHandle, dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	WriteProcessMemory(m_ProcessHandle, dst, src, size, NULL);
	VirtualProtectEx(m_ProcessHandle, dst, size, oldprotect, &oldprotect);
}

void Memory::nop(void* dst, unsigned int size)
{
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	memset(dst, 0x90, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}

void Memory::nopEx(void* dst, unsigned int size)
{
	byte* nopArray = new byte[size];
	memset(nopArray, 0x90, size);

	DWORD oldprotect;
	VirtualProtectEx(m_ProcessHandle, dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	WriteProcessMemory(m_ProcessHandle, dst, nopArray, size, NULL);
	VirtualProtectEx(m_ProcessHandle, dst, size, oldprotect, &oldprotect);
	delete[] nopArray;
}
