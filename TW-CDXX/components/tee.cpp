#include "tee.h"

Tee::Tee(Controller* pController)
{
	m_pController = pController;

	resetInput();
	setAddresses();
}

void Tee::resetInput()
{
	m_InputData.m_TargetX = 1; // aiming to the exact center is not allowed
	m_InputData.m_TargetX = 0;
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

	m_InputAddresses.m_TargetX = (DWORD*)(((DWORD*)inputBaseAddr) - sizeof(byte)*10);
	m_InputAddresses.m_TargetX = (DWORD*)(((DWORD*)inputBaseAddr) - sizeof(byte)*9);
	m_InputAddresses.m_Jump = (DWORD*)(((DWORD*)inputBaseAddr) - sizeof(byte)*8);
	m_InputAddresses.m_Fire = (DWORD*)(((DWORD*)inputBaseAddr) - sizeof(byte)*7);
	m_InputAddresses.m_Hook = (DWORD*)(((DWORD*)inputBaseAddr) - sizeof(byte)*6);
	m_InputAddresses.m_PlaceHolder1 = (DWORD*)(((DWORD*)inputBaseAddr) - sizeof(byte)*5);
	m_InputAddresses.m_PlaceHolder2 = (DWORD*)(((DWORD*)inputBaseAddr) - sizeof(byte)*4);
	m_InputAddresses.m_PlaceHolder3 = (DWORD*)(((DWORD*)inputBaseAddr) - sizeof(byte)*3);
	m_InputAddresses.m_PlaceHolder4 = (DWORD*)(((DWORD*)inputBaseAddr) - sizeof(byte)*2);
	m_InputAddresses.m_DirLeft = (DWORD*)(((DWORD*)inputBaseAddr) - sizeof(byte)*1);
	m_InputAddresses.m_DirRight = inputBaseAddr;
}
