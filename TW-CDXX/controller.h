#pragma once
#include <chrono>
#include <thread>
#include "memory.h"
#include "patternscan.h"

class Tee; //forward declaration to prevent circular includes
class Player; //same thing here

enum
{
	TICK_SPEED = 20,
	MAX_CLIENTS = 64
};

class Controller
{
public:
	Controller(wchar_t* process, wchar_t* moduleName);

	Memory* getMemory() { return m_pMemory; };
	PatternScan* getPatternScan() { return m_pPatternScan; };

	Tee* getLocalTee() { return m_pTee; };
	Player* getPlayer(int id) { return m_apPlayers[id]; };

	void tick();

private:
	Memory* m_pMemory;
	PatternScan* m_pPatternScan;
	
	//components
	Tee* m_pTee;
	Player* m_apPlayers[MAX_CLIENTS];
};