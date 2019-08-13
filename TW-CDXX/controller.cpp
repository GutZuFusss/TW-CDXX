#include "controller.h"
#include "components/tee.h"
#include "components/player.h"
#include "haxx/balancebot.h"
#include "haxx/aimbot.h"

Controller::Controller(wchar_t* process, wchar_t* moduleName)
{
	m_pMemory = new Memory(process, moduleName);
	m_pPatternScan = new PatternScan(m_pMemory);

	//components
	m_pTee = new Tee(this);
	for(int i = 0; i < MAX_CLIENTS; i++)
		m_apPlayers[i] = new Player(this, i);

	//haxx
	m_pBalanceBot = new BalanceBot(this);
	m_pAimBot = new AimBot(this);
}

void Controller::tick()
{
	while(420 == 420)
	{
		//component ticks
		m_pTee->tick();
		for(int i = 0; i < MAX_CLIENTS; i++)
			m_apPlayers[i]->tick();

		//haxx ticks
		m_pBalanceBot->tick();
		m_pAimBot->tick();

		std::this_thread::sleep_for(std::chrono::milliseconds(TICK_SPEED));
	}
};
