#pragma once
#include "../controller.h"
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
		DWORD* m_TargetX;
		DWORD* m_TargetY;
		DWORD* m_Jump;
		DWORD* m_Fire;
		DWORD* m_Hook;
		DWORD* m_PlaceHolder1;
		DWORD* m_PlaceHolder2;
		DWORD* m_PlaceHolder3;
		DWORD* m_PlaceHolder4;
		DWORD* m_DirLeft;
		DWORD* m_DirRight;
	};

	InputData m_InputData;
	InputAddresses m_InputAddresses;

	void resetInput();
	void setAddresses();

	Controller* m_pController;
public:
	Tee(Controller* pController);
	
	void setTarget(int x, int y);
	void jump();
	void fire();
	void fireHook();
	void releaseHook();
};
