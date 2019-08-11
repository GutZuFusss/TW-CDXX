#include <Windows.h>
#include "patternscan.h"
#include "memory.h"
#include "controller.h"

#include "components/tee.h"

int main()
{
	Controller* pController = new Controller((wchar_t*)L"teeworlds.exe", (wchar_t*)L"teeworlds.exe");
	
	Tee* pTee = new Tee(pController);

	return  0;
}