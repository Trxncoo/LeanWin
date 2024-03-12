#include "LeanCriticalSection.h"

Void criticalSectionCreate(pCriticalSectionInfo criticalSectionInfo) {
	InitializeCriticalSection(criticalSectionInfo);
}

Void criticalSectionEnter(pCriticalSectionInfo criticalSectionInfo) {
	EnterCriticalSection(criticalSectionInfo);
}

Void criticalSectionLeave(pCriticalSectionInfo criticalSectionInfo) {
	LeaveCriticalSection(criticalSectionInfo);
}

Void criticalSectionClose(pCriticalSectionInfo criticalSectionInfo) {
	DeleteCriticalSection(criticalSectionInfo);
}