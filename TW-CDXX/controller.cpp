#include "controller.h"
#include "components/tee.h"
#include "components/player.h"

Controller::Controller(wchar_t* process, wchar_t* moduleName)
{
	m_pMemory = new Memory(process, moduleName);
	m_pPatternScan = new PatternScan(m_pMemory);
	m_pTee = new Tee(this);
}

void Controller::tick()
{
	Player* p = new Player(this, 1);
	while(420 == 420)
	{
		m_pTee->tick();
		p->tick();
		std::this_thread::sleep_for(std::chrono::milliseconds(TICK_SPEED));
	}
};
