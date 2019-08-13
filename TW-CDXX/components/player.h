#pragma once

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

	struct Position
	{
		int x;
		int y;
	} m_Pos;

	int m_ActiveWeapon;

	int getClientID() { return m_ClientID; };

private:
	Controller* m_pController;

	struct PositionAddresses
	{
		DWORD* m_X;
		DWORD* m_Y;
	} m_PositionAddresses;

	DWORD* m_ActiveWeaponAddress;

	void setAddresses();

	int m_ClientID;
};