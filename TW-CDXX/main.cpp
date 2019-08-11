#include <Windows.h>
#include "patternscan.h"
#include "memory.h"

int main()
{
	DWORD processID = getProcessID((wchar_t*)L"teeworlds.exe");
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, processID);

	DWORD* test = (DWORD*)patternScanExModule(hProcess, (wchar_t*)L"teeworlds.exe", (wchar_t*)L"teeworlds.exe", (char*)"\x00\x00\x00\x00\x00\x97\xc3\x00\xd8\x75\x2a\x01", (char*)"xxx?xxx?xxxx");
	
	if (test != nullptr)
	{
		//test = (DWORD*)(((DWORD*)test) - 0x00000001);
		while(420 == 420)
		{
			PatchEx(hProcess, test, (char*)"\x01", 1);
		}
	}

	return  0;
}