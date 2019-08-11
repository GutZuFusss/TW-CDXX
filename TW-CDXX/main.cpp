#include <Windows.h>
#include "patternscan.h"
#include "memory.h"
#include "controller.h"
#include "components/tee.h"

Tee* pTee;

void tick()
{
	while (420 == 420)
	{
		pTee->tick();
		std::this_thread::sleep_for(std::chrono::milliseconds(TICK_SPEED));
	}
};

int main()
{
	Controller* pController = new Controller((wchar_t*)L"teeworlds.exe", (wchar_t*)L"teeworlds.exe");
	pTee = new Tee(pController);
	tick();

	return  0;
}