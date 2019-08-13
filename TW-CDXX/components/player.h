#pragma once

#include "../util.h"
#include "../controller.h"

enum
{
	POSITION_ADDR_FACTOR = 0x000000bc
};

class Player
{
public:
	Player(Controller* pController, int id);

	void tick();

	ivec2 m_Pos;

	int m_ActiveWeapon;

	int getClientID() { return m_ClientID; };
	bool isActive() { return m_Active; };

private:
	Controller* m_pController;

	struct PositionAddresses
	{
		DWORD* m_X;
		DWORD* m_Y;
	} m_PositionAddresses;

	DWORD* m_ActiveWeaponAddress;

	DWORD* m_ActiveAddress;

	void setAddresses();

	int m_ClientID;
	bool m_Active;
};