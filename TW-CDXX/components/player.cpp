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
}

void Player::setAddresses()
{
	DWORD* positionBaseAddr = reinterpret_cast<DWORD*>((DWORD)m_pController->getMemory()->getModuleEntry()->modBaseAddr + 0xff76ffe8);
	m_PositionAddresses.m_X = reinterpret_cast<DWORD*>((DWORD)positionBaseAddr + (m_ClientID * (DWORD)POSITION_ADDR_FACTOR));
	m_PositionAddresses.m_Y = reinterpret_cast<DWORD*>((DWORD)positionBaseAddr + (m_ClientID * POSITION_ADDR_FACTOR) + sizeof(int) * 1);

	m_ActiveWeaponAddress = reinterpret_cast<DWORD*>((DWORD)positionBaseAddr + (m_ClientID * (DWORD)POSITION_ADDR_FACTOR) + sizeof(int) * 17);
}