#include "LeanCriticalSection.h"

Void criticalSectionDebug(pCriticalSectionInfo criticalSectionInfo) {
#ifdef LEAN_DEBUG
	_ftprintf_s(stderr, _T("<CriticalSection Debug>\n\tState: <%d>\n"), criticalSectionInfo->state);
#endif
}

Void criticalSectionCreate(pCriticalSectionInfo criticalSectionInfo) {
	InitializeCriticalSection(&(criticalSectionInfo->handle));
	criticalSectionInfo->state = 0;
}

Void criticalSectionEnter(pCriticalSectionInfo criticalSectionInfo) {
	EnterCriticalSection(&(criticalSectionInfo->handle));
	criticalSectionInfo->state = 1;
}

Void criticalSectionLeave(pCriticalSectionInfo criticalSectionInfo) {
	LeaveCriticalSection(&(criticalSectionInfo->handle));
	criticalSectionInfo->state = 0;
}

Void criticalSectionClose(pCriticalSectionInfo criticalSectionInfo) {
	DeleteCriticalSection(&(criticalSectionInfo->handle));
	criticalSectionInfo->state = 0;
}