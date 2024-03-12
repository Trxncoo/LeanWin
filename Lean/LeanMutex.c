#include "LeanMutex.h"

Bool mutexCreate(pMutexInfo mutexInfo, pStr name) {
	MutexHandle mutexHandle;

	mutexHandle = CreateMutex(NULL, FALSE, mutexInfo->name);
	if (mutexHandle == NULL) {
		return 0;
	}

	mutexInfo->handle = mutexHandle;
	_tcscpy_s(mutexInfo->name, MAX_PATH - 1, name);

	return 1;
}

Dword mutexLock(pMutexInfo mutexInfo) {
	return WaitForSingleObject(mutexInfo->handle, INFINITE);
}

Bool mutexUnlock(pMutexInfo mutexInfo) {
	return ReleaseMutex(mutexInfo->handle);
}

Bool mutexOpen(pMutexInfo mutexInfo, pStr name) {
	MutexHandle mutexHandle;

	mutexHandle = OpenMutex(MUTEX_ALL_ACCESS, FALSE, name);
	if (mutexHandle == NULL) {
		return 0;
	}

	mutexInfo->handle = mutexHandle;
	_tcscpy_s(mutexInfo->name, MAX_PATH - 1, name);

	return 1;
}

Bool mutexClose(pMutexInfo mutexInfo) {
	return CloseHandle(mutexInfo->handle);
}