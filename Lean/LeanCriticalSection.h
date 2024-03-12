#pragma once

#include "LeanTypes.h"

typedef CRITICAL_SECTION CriticalSectionInfo;
typedef LPCRITICAL_SECTION pCriticalSectionInfo;

Void criticalSectionCreate(pCriticalSectionInfo criticalSectionInfo);

Void criticalSectionEnter(pCriticalSectionInfo criticalSectionInfo);

Void criticalSectionLeave(pCriticalSectionInfo criticalSectionInfo);

Void criticalSectionClose(pCriticalSectionInfo criticalSectionInfo);