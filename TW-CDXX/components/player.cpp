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

	m_Active = (bool)m_pController->getMemory()->readMemoryEx(m_ActiveAddress, sizeof(bool));

	m_ActiveWeapon = (int)m_pController->getMemory()->readMemoryEx(m_ActiveWeaponAddress, sizeof(int));
}

void Player::setAddresses()
{
	DWORD* positionBaseAddr = reinterpret_cast<DWORD*>((DWORD)m_pController->getMemory()->getModuleEntry()->modBaseAddr + 0xff76ffe8);
	m_PositionAddresses.m_X = reinterpret_cast<DWORD*>((DWORD)positionBaseAddr + (m_ClientID * (DWORD)POSITION_ADDR_FACTOR));
	m_PositionAddresses.m_Y = reinterpret_cast<DWORD*>((DWORD)positionBaseAddr + (m_ClientID * POSITION_ADDR_FACTOR) + sizeof(int) * 1);

	m_ActiveAddress = reinterpret_cast<DWORD*>((DWORD)positionBaseAddr + (m_ClientID * (DWORD)POSITION_ADDR_FACTOR) + 0x005c02c0); //sry 4 teh hardcore man

	m_ActiveWeaponAddress = reinterpret_cast<DWORD*>((DWORD)positionBaseAddr + (m_ClientID * (DWORD)POSITION_ADDR_FACTOR) + sizeof(int) * 17);
}
