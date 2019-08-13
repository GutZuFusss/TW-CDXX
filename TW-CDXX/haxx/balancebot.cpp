#include "balancebot.h"
#include "../util.h"
#include "../components/tee.h"
#include "../components/player.h"

BalanceBot::BalanceBot(Controller* pController)
{
	m_pController = pController;
	m_Active = true;
}

void BalanceBot::tick()
{
	if(!m_Active)
		return;

	balance();
}

void BalanceBot::balance()
{
	int id = getClosestID();
	if(id == -1)
		return;

	ivec2 myPos = m_pController->getLocalTee()->m_Pos;
	ivec2 targetPos = m_pController->getPlayer(id)->m_Pos;

	if(distance(myPos, targetPos) > BBOT_MAX_DIST)
		return;

	if(abs(myPos.x - targetPos.x) <= BBOT_XDIFF_TOLERANCE)
	{
		m_pController->getLocalTee()->move(WALK_STAND);
		return;
	}

	printf("%i\n", id);

	if(myPos.x > targetPos.x)
		m_pController->getLocalTee()->move(WALK_LEFT);
	else
		m_pController->getLocalTee()->move(WALK_RIGHT);
}

int BalanceBot::getClosestID()
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
