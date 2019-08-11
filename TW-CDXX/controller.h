#pragma once
#include <chrono>
#include <thread>
#include "memory.h"
#include "patternscan.h"
#include "components/tee.h"

enum
{
	TICK_SPEED = 20
};

class Controller
{
public:
	Controller(wchar_t* process, wchar_t* moduleName)
	{
		m_pMemory = new Memory(process, moduleName);
		m_pPatternScan = new PatternScan(m_pMemory);
	};

	Memory* getMemory() { return m_pMemory; };
	PatternScan* getPatternScan() { return m_pPatternScan; };

	Tee* getLocalTee() { return m_pTee; };

private:
	Memory* m_pMemory;
	PatternScan* m_pPatternScan;
	
	//components
	Tee* m_pTee;

	void tick()
	{
		m_pTee->tick();
		std::this_thread::sleep_for(std::chrono::milliseconds(TICK_SPEED));
	};
};