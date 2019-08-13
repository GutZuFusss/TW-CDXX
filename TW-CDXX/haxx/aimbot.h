#pragma once

#include "../controller.h"

class AimBot
{
public:
	AimBot(Controller* pController);

	void tick();

	void setActive(bool a) { m_Active = a; };

private:
	Controller* m_pController;

	bool m_Active;

	void aimBot();
	int getClosestID();
};