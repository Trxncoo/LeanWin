#include "LeanMutex.h"

Void mutexDebug(pMutexInfo mutexInfo) {
	_tprintf(_T("<Mutex Debug>\n\tName: <%s>\n\tState: <%d>\n"), mutexInfo->name, mutexInfo->state);
}

Bool mutexCreate(pMutexInfo mutexInfo) {
	MutexHandle mutexHandle;

	mutexHandle = CreateMutex(NULL, FALSE, mutexInfo->name);
	if (mutexHandle == NULL) {
		return 0;
	}

	mutexInfo->handle = mutexHandle;
	mutexInfo->state = 0;

	return 1;
}

Bool mutexCloseHandle(pMutexInfo mutexInfo) {
	return CloseHandle(mutexInfo->handle);
}

Void mutexLock(pMutexInfo mutexInfo) {
	mutexInfo->state = 1;
	WaitForSingleObject(mutexInfo->handle, INFINITE);
}

Void mutexUnlock(pMutexInfo mutexInfo) {
	mutexInfo->state = 0;
	ReleaseMutex(mutexInfo->handle);
}