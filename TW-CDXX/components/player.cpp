#include "player.h"

Player::Player(Controller* pController, int id)
{
	m_pController = pController;
	m_ClientID = id;

	setAddresses();
}

void Player::tick()
{
	m_Pos.x = (int)m_pController->getMemory()->readMemoryEx(m_PositionAddresses.m_X, sizeof(int));
	m_Pos.y = (int)m_pController->getMemory()->readMemoryEx(m_PositionAddresses.m_Y, sizeof(int));

	printf("X: %i       Y: %i\n", m_Pos.x, m_Pos.y);
}

void Player::setAddresses()
{
	DWORD* positionBaseAddr = reinterpret_cast<DWORD*>((DWORD)m_pController->getMemory()->getModuleEntry()->modBaseAddr + 0xff76ffe8);
	DWORD* ttt = reinterpret_cast<DWORD*>(0x001A004C - (DWORD)positionBaseAddr);
	m_PositionAddresses.m_X = positionBaseAddr + (m_ClientID * POSITION_ADDR_FACTOR);
	m_PositionAddresses.m_Y = (DWORD*)(((DWORD*)positionBaseAddr) - sizeof(byte) * 1 + (m_ClientID * POSITION_ADDR_FACTOR));
}