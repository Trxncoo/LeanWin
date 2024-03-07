#include "LeanMutex.h"

Void mutexDebug(pMutexInfo mutexInfo) {
#ifdef LEAN_DEBUG
	_ftprintf_s(stderr, _T("<Mutex Debug>\n\tName: <%s>\n\tState: <%d>\n"), mutexInfo->name, mutexInfo->state);
#endif
}

Bool mutexCreate(pMutexInfo mutexInfo, pStr name) {
	MutexHandle mutexHandle;

	mutexHandle = CreateMutex(NULL, FALSE, mutexInfo->name);
	if (mutexHandle == NULL) {
		return 0;
	}

	mutexInfo->handle = mutexHandle;
	mutexInfo->state = 0;
	_tcscpy_s(mutexInfo->name, MAX_PATH - 1, name);

	return 1;
}

Bool mutexClose(pMutexInfo mutexInfo) {
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