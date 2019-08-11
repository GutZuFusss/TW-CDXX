#pragma once
#include "../memory.h"

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
	//DWORD* test = (DWORD*)pController->getPatternScan()->patternScanExModule((char*)"\x00\x00\x00\x00\x00\x97\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", (char*)"xxxxxx?x????????????xxxxxxxx");
	Memory* m_pMemory;
public:
	Tee(Memory* pMem);
};
