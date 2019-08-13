#pragma once

#include "../controller.h"

class BalanceBot
{
public:
	BalanceBot(Controller* pController);

	void tick();

	void setActive(bool a) { m_Active = a; };

private:
	Controller* m_pController;

	bool m_Active;
};