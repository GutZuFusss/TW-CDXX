#include "aimbot.h"
#include "../components/player.h"
#include "../components/tee.h"

AimBot::AimBot(Controller* pController)
{
	m_pController = pController;
	m_Active = true;
}

void AimBot::tick()
{
	if(!m_Active)
		return;

	aimBot();
}

void AimBot::aimBot()
{
	int targetID = getClosestID();
}

int AimBot::getClosestID() //TODO: code duplication
{
	int closestDist = INT_MAX;
	int closestID = -1;
	for(int i = 0; i < MAX_CLIENTS; i++)
	{
		if(!m_pController->getPlayer(i)->isActive())
			continue;
		if(i == m_pController->getLocalTee()->m_LocalCID)
			continue;

		int dist = distance(m_pController->getLocalTee()->m_Pos, m_pController->getPlayer(i)->m_Pos);
		if(dist < closestDist)
		{
			closestDist = dist;
			closestID = i;
		}
	}

	return closestID;
}
