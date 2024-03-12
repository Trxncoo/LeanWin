#pragma once

#include "LeanTypes.h"

typedef HANDLE SemaphoreHandle;

typedef struct _SemaphoreInfo SemaphoreInfo;
typedef struct _SemaphoreInfo* pSemaphoreInfo;

struct _SemaphoreInfo {
	pStr name[MAX_PATH];
	SemaphoreHandle handle;
};

Bool semaphoreCreate(pSemaphoreInfo semaphoreInfo, pStr name, Long initialCount, Long maximumCount);

Dword semaphoreLock(pSemaphoreInfo semaphoreInfo);

Bool semaphoreUnlock(pSemaphoreInfo semaphoreInfo, Long releaseCount, pLong previousCount);

Bool semaphoreOpen(pSemaphoreInfo semaphoreInfo, pStr name);

Bool semaphoreClose(pSemaphoreInfo semaphoreInfo);