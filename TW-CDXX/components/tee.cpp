#include "tee.h"

Tee::Tee(Memory* pMem)
{
	m_pMemory = pMem;

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

}
