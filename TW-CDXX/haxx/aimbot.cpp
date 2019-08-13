#include "aimbot.h"

AimBot::AimBot(Controller* pController)
{
	m_pController = pController;
	m_Active = false;
}

void tick()
{
	if(!m_Active)
		return;

	aimBot();
}

void aimBot()
{

}
