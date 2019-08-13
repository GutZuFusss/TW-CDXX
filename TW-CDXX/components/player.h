#pragma once

#include "../controller.h"

enum
{
	//POSITION_ADDR_FACTOR = 0x00000064
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

	int getClientID() { return m_ClientID; };

private:
	Controller* m_pController;

	struct PositionAddresses
	{
		DWORD* m_X;
		DWORD* m_Y;
	} m_PositionAddresses;

	void setAddresses();

	int m_ClientID;
};