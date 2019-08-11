#pragma once
#include "memory.h"
#include "patternscan.h"

class Controller
{
public:
	Controller(wchar_t* process, wchar_t* moduleName)
	{
		m_pMemory = new Memory(process, moduleName);
		m_pPatternScan = new PatternScan(m_pMemory);
	};

	Memory* getMemory() { return m_pMemory; };

private:
	Memory* m_pMemory;
	PatternScan* m_pPatternScan;
};