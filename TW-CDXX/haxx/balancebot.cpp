#include "balancebot.h"

BalanceBot::BalanceBot(Controller* pController)
{
	m_pController = pController;
	m_Active = false;
}

void BalanceBot::tick()
{
	if(!m_Active)
		return;
}
