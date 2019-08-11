#pragma once
#include "../memory.h"

enum
{
	INPUT_STATE_MASK = 0x3f
};

class Tee
{
private:
	struct InputData
	{
		int m_TargetX;
		int m_TargetY;
		int m_Jump;
		int m_Fire;
		int m_Hook;
		int m_PlaceHolder1;
		int m_PlaceHolder2;
		int m_PlaceHolder3;
		int m_PlaceHolder4;
		int m_DirLeft;
		int m_DirRight;
	};

	struct InputAddresses
	{
		int m_TargetX;
		int m_TargetY;
		int m_Jump;
		int m_Fire;
		int m_Hook;
		int m_PlaceHolder1;
		int m_PlaceHolder2;
		int m_PlaceHolder3;
		int m_PlaceHolder4;
		int m_DirLeft;
		int m_DirRight;
	};

	InputData m_InputData;
	InputAddresses m_InputAddresses;

	void resetInput();
	void setAddresses();

	Memory* m_pMemory;
public:
	Tee(Memory* pMem);
};
