#pragma once

#include "LeanTypes.h"

typedef	LARGE_INTEGER TimeInfo;
typedef	LARGE_INTEGER* pTimeInfo;

Void timeSetRelative(pTimeInfo timeInfo, Dword seconds);