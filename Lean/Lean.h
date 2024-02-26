#pragma once

#include "LeanProcesses.h"
#include "LeanRegistry.h"	
#include "LeanThreads.h"

#define ErrorLog(msg) _ftprintf(stderr, _T("<Error> %s\n"), msg);
#define Log(msg) _tprintf(_T("%s"), msg);

void LeanInit();