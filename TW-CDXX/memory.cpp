#include "memory.h"

DWORD getProcessID(wchar_t* exeName)
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

MODULEENTRY32 getModuleEntry(DWORD dwProcID, wchar_t* moduleName)
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

void Patch(void* dst, void* src, unsigned int size)
{
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	memcpy(dst, src, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}

void PatchEx(HANDLE hProcess, void* dst, void* src, unsigned int size)
{
	DWORD oldprotect;
	VirtualProtectEx(hProcess, dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	WriteProcessMemory(hProcess, dst, src, size, NULL);
	VirtualProtectEx(hProcess, dst, size, oldprotect, &oldprotect);
}

void Nop(HANDLE hProcess, void* dst, unsigned int size)
{
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	memset(dst, 0x90, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}

void NopEx(HANDLE hProcess, void* dst, unsigned int size)
{
	byte* nopArray = new byte[size];
	memset(nopArray, 0x90, size);

	DWORD oldprotect;
	VirtualProtectEx(hProcess, dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	WriteProcessMemory(hProcess, dst, nopArray, size, NULL);
	VirtualProtectEx(hProcess, dst, size, oldprotect, &oldprotect);
	delete[] nopArray;
}
