#include <Windows.h>
#include "patternscan.h"
#include "memory.h"
#include "controller.h"

int main()
{
	Controller* pController = new Controller((wchar_t*)L"teeworlds.exe", (wchar_t*)L"teeworlds.exe");
	DWORD* test = (DWORD*)pController->getPatternScan()->patternScanExModule((char*)"\x00\x00\x00\x00\x00\x97\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", (char*)"xxxxxx?x????????????xxxxxxxx");
	if (test != nullptr)
	{
		test = (DWORD*)(((DWORD*)test) - sizeof(byte));
		while(420 == 420)
		{
			pController->getMemory()->patchEx(test, (char*)"\x01", 1);
		}
	}

	return  0;
}