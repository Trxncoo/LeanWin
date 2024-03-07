#pragma once

#include "LeanTypes.h"

typedef CRITICAL_SECTION CriticalSectionHandle;

typedef struct _CriticalSectionInfo CriticalSectionInfo;
typedef struct _CriticalSectionInfo* pCriticalSectionInfo;

struct _CriticalSectionInfo {
	CriticalSectionHandle handle;
	Bool state;
};

Void criticalSectionDebug(pCriticalSectionInfo criticalSectionInfo);

Void criticalSectionCreate(pCriticalSectionInfo criticalSectionInfo);

Void criticalSectionEnter(pCriticalSectionInfo criticalSectionInfo);

Void criticalSectionLeave(pCriticalSectionInfo criticalSectionInfo);

Void criticalSectionClose(pCriticalSectionInfo criticalSectionInfo);