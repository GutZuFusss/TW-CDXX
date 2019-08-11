#include "tee.h"

Tee::Tee(Controller* pController)
{
	m_pController = pController;

	resetInput();
	setAddresses();
}

void Tee::tick()
{
	//update local tee's info (might move this to another function some day
	m_Pos.x = (int)m_pController->getMemory()->readMemoryEx(m_PositionAddresses.m_X, sizeof(int));
	m_Pos.y = (int)m_pController->getMemory()->readMemoryEx(m_PositionAddresses.m_Y, sizeof(int));
}

void Tee::resetInput()
{
	m_InputData.m_TargetX = 1; // aiming to the exact center is not allowed
	m_InputData.m_TargetY = 0;
	m_InputData.m_Jump = 0;
	if((m_InputData.m_Fire & 1) != 0)
		m_InputData.m_Fire++;
	m_InputData.m_Fire &= INPUT_STATE_MASK;
	m_InputData.m_Hook = 0;
	m_InputData.m_PlaceHolder1 = 0;
	m_InputData.m_PlaceHolder2 = 0;
	m_InputData.m_PlaceHolder3 = 0;
	m_InputData.m_PlaceHolder4 = 0;
	m_InputData.m_DirLeft = 0;
	m_InputData.m_DirRight = 0;
}

void Tee::setAddresses()
{
	DWORD* inputBaseAddr = (DWORD*)m_pController->getPatternScan()->patternScanExModule((char*)"\x00\x00\x00\x00\x00\x97\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", (char*)"xxxxxx?x????????????xxxxxxxx");
	m_InputAddresses.m_TargetX = (DWORD*)(((DWORD*)inputBaseAddr) - sizeof(byte)*25);
	m_InputAddresses.m_TargetY = (DWORD*)(((DWORD*)inputBaseAddr) - sizeof(byte)*24);
	m_InputAddresses.m_Jump = (DWORD*)(((DWORD*)inputBaseAddr) - sizeof(byte)*18);
	m_InputAddresses.m_Fire = (DWORD*)(((DWORD*)inputBaseAddr) - sizeof(byte)*17);
	m_InputAddresses.m_Hook = (DWORD*)(((DWORD*)inputBaseAddr) - sizeof(byte)*16);
	m_InputAddresses.m_PlaceHolder1 = (DWORD*)(((DWORD*)inputBaseAddr) - sizeof(byte)*5);
	m_InputAddresses.m_PlaceHolder2 = (DWORD*)(((DWORD*)inputBaseAddr) - sizeof(byte)*4);
	m_InputAddresses.m_PlaceHolder3 = (DWORD*)(((DWORD*)inputBaseAddr) - sizeof(byte)*3);
	m_InputAddresses.m_PlaceHolder4 = (DWORD*)(((DWORD*)inputBaseAddr) - sizeof(byte)*2);
	m_InputAddresses.m_DirLeft = (DWORD*)(((DWORD*)inputBaseAddr) - sizeof(byte)*1);
	m_InputAddresses.m_DirRight = inputBaseAddr;

	DWORD* positionBaseAddr = (DWORD*)m_pController->getPatternScan()->patternScanExModule((char*)"\x18\x00\x00\x00\x58\xc3\xfd\x08\x00\x04\x00\x00", (char*)"?xxxxxxxxxxx");
	m_PositionAddresses.m_X = (DWORD*)(((DWORD*)positionBaseAddr) - sizeof(byte) * 2);
	m_PositionAddresses.m_Y = (DWORD*)(((DWORD*)positionBaseAddr) - sizeof(byte) * 1);;
}

void Tee::setTarget(int x, int y)
{
	m_InputData.m_TargetX = x;
	m_InputData.m_TargetY = y;
	m_pController->getMemory()->patchEx(m_InputAddresses.m_TargetX, &m_InputData.m_TargetX, sizeof(int));
	m_pController->getMemory()->patchEx(m_InputAddresses.m_TargetY, &m_InputData.m_TargetY, sizeof(int));
}

void Tee::jump()
{
	m_InputData.m_Jump = 1;
	m_pController->getMemory()->patchEx(m_InputAddresses.m_Jump, &m_InputData.m_Jump, sizeof(int));
	m_InputData.m_Jump = 0;
	m_pController->getMemory()->patchEx(m_InputAddresses.m_Jump, &m_InputData.m_Jump, sizeof(int));
}

void Tee::fire()
{
	m_InputData.m_Fire++;
	m_InputData.m_Fire &= INPUT_STATE_MASK;
	m_pController->getMemory()->patchEx(m_InputAddresses.m_Fire, &m_InputData.m_Fire, sizeof(int));
}

void Tee::fireHook()
{
	m_InputData.m_Hook = 1;
	m_pController->getMemory()->patchEx(m_InputAddresses.m_Hook, &m_InputData.m_Hook, sizeof(int));
}

void Tee::releaseHook()
{
	m_InputData.m_Hook = 0;
	m_pController->getMemory()->patchEx(m_InputAddresses.m_Hook, &m_InputData.m_Hook, sizeof(int));
}

void Tee::move(int dir)
{
	if(dir == WALK_LEFT)
	{
		m_InputData.m_DirLeft = 1;
		m_InputData.m_DirRight = 0;
		m_pController->getMemory()->patchEx(m_InputAddresses.m_DirLeft, &m_InputData.m_DirLeft, sizeof(int));
		m_pController->getMemory()->patchEx(m_InputAddresses.m_DirRight, &m_InputData.m_DirRight, sizeof(int));
	}
	else if (dir == WALK_RIGHT)
	{
		m_InputData.m_DirLeft = 0;
		m_InputData.m_DirRight = 1;
		m_pController->getMemory()->patchEx(m_InputAddresses.m_DirLeft, &m_InputData.m_DirLeft, sizeof(int));
		m_pController->getMemory()->patchEx(m_InputAddresses.m_DirRight, &m_InputData.m_DirRight, sizeof(int));
	}
	else if (dir == WALK_STAND)
	{
		m_InputData.m_DirLeft = 0;
		m_InputData.m_DirRight = 0;
		m_pController->getMemory()->patchEx(m_InputAddresses.m_DirLeft, &m_InputData.m_DirLeft, sizeof(int));
		m_pController->getMemory()->patchEx(m_InputAddresses.m_DirRight, &m_InputData.m_DirRight, sizeof(int));
	}
}
