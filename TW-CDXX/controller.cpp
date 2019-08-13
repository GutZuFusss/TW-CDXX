#include "controller.h"
#include "components/tee.h"
#include "components/player.h"

Controller::Controller(wchar_t* process, wchar_t* moduleName)
{
	m_pMemory = new Memory(process, moduleName);
	m_pPatternScan = new PatternScan(m_pMemory);

	m_pTee = new Tee(this);

	for(int i = 0; i < MAX_CLIENTS; i++)
		m_apPlayers[i] = new Player(this, i);
}

void Controller::tick()
{
	while(420 == 420)
	{
		m_pTee->tick();
		for(int i = 0; i < MAX_CLIENTS; i++)
			m_apPlayers[i]->tick();
		std::this_thread::sleep_for(std::chrono::milliseconds(TICK_SPEED));
	}
};
