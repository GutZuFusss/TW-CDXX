#pragma once
#include "memory.h"

class Controller
{
public:
	Controller(wchar_t* process, wchar_t* moduleName)
	{
		m_pMemory = new Memory(process, moduleName);
	};

private:
	Memory* m_pMemory;
};