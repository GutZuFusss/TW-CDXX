#include <Windows.h>
#include "patternscan.h"
#include "memory.h"
#include "controller.h"

#include "components/tee.h"

int main()
{
	Controller* pController = new Controller((wchar_t*)L"teeworlds.exe", (wchar_t*)L"teeworlds.exe");
	pController->tick();

	return  0;
}