#pragma once

#include "../controller.h"

enum
{
	BBOT_XDIFF_TOLERANCE = 14,
	BBOT_MAX_DIST = 220
};

class BalanceBot
{
public:
	BalanceBot(Controller* pController);

	void tick();

	void setActive(bool a) { m_Active = a; };

private:
	Controller* m_pController;

	bool m_Active;

	void balance();
	int getClosestID();
};