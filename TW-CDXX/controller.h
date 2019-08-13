#pragma once
#include <chrono>
#include <thread>
#include "memory.h"
#include "patternscan.h"

class Tee; //forward declaration to prevent circular includes
class Player; //same thing here

class BalanceBot; //you get the drill
class AimBot;

enum
{
	TICK_SPEED = 20,
	MAX_CLIENTS = 64
};

class Controller
{
public:
	Controller(wchar_t* process, wchar_t* moduleName);

	void tick();

	Memory* getMemory() { return m_pMemory; };
	PatternScan* getPatternScan() { return m_pPatternScan; };

	//components
	Tee* getLocalTee() { return m_pTee; };
	Player* getPlayer(int id) { return m_apPlayers[id]; };

	//haxx
	BalanceBot* getBalanceBot() { return m_pBalanceBot; };
	AimBot* getAimBot() { return m_pAimBot; };

private:
	Memory* m_pMemory;
	PatternScan* m_pPatternScan;
	
	//components
	Tee* m_pTee;
	Player* m_apPlayers[MAX_CLIENTS];

	//haxx
	BalanceBot* m_pBalanceBot;
	AimBot* m_pAimBot;
};