#pragma once

#include "../util.h"
#include "../controller.h"
#include "../memory.h"

enum
{
	INPUT_STATE_MASK = 0x3f
};

enum
{
	WALK_LEFT = -1,
	WALK_STAND,
	WALK_RIGHT
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
	} m_InputData;

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
	} m_InputAddresses;

	struct PositionAddresses
	{
		DWORD* m_X;
		DWORD* m_Y;
	} m_PositionAddresses;

	DWORD* m_LocalCIDAddress;

	void resetInput();
	void setAddresses();

	Controller* m_pController;
public:
	Tee(Controller* pController);

	void tick();

	ivec2 m_Pos;

	int m_LocalCID;
	
	void setTarget(int x, int y);
	void jump();
	void fire();
	void fireHook();
	void releaseHook();
	void move(int dir);
};
