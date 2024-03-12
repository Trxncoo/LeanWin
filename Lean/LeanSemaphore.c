#include "LeanSemaphore.h"

Bool semaphoreCreate(pSemaphoreInfo semaphoreInfo, pStr name, Long initialCount, Long maximumCount) {
	SemaphoreHandle semaphoreHandle;

	semaphoreHandle = CreateSemaphore(NULL, initialCount, maximumCount, name);
	if (semaphoreHandle == NULL) {
		return 0;
	}

	semaphoreInfo->handle = semaphoreHandle;
	_tcscpy_s(semaphoreInfo->name, MAX_PATH - 1, name);

	return 1;
}

Dword semaphoreLock(pSemaphoreInfo semaphoreInfo) {
	return WaitForSingleObject(semaphoreInfo->handle, INFINITE);
}

Bool semaphoreUnlock(pSemaphoreInfo semaphoreInfo, Long releaseCount, pLong previousCount) {
	return ReleaseSemaphore(semaphoreInfo->handle, releaseCount, previousCount);
}

Bool semaphoreOpen(pSemaphoreInfo semaphoreInfo, pStr name) {
	SemaphoreHandle semaphoreHandle;

	semaphoreHandle = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, name);
	if (semaphoreHandle == NULL) {
		return 0;
	}

	semaphoreInfo->handle = semaphoreHandle;
	_tcscpy_s(semaphoreInfo->name, MAX_PATH - 1, name);

	return 1;
}

Bool semaphoreClose(pSemaphoreInfo semaphoreInfo) {
	return CloseHandle(semaphoreInfo->handle);
}
