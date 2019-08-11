#include <Windows.h>
#include "processtools.h"
#include "patternscan.h"
#include "memhack.h"

int main()
{
	//Get Process ID by enumerating the processes using tlhelp32snapshot
	DWORD processID = GetProcID(L"ac_client.exe");
	//Get handle by OpenProcess
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, processID);

	//PatternScan
	void * healthDecAddress = PatternScanExModule(hProcess, L"ac_client.exe", L"ac_client.exe", "\x29\x7b\x00\x8b\xc7", "xx?xx");

	//Nop the instructions
	if (healthDecAddress != nullptr)
	{
		NopEx(hProcess, healthDecAddress, 5);
	}

	return  0;
}