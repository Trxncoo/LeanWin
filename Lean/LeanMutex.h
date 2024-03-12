#pragma once

#include "LeanTypes.h"

typedef HANDLE MutexHandle;

typedef struct _MutexInfo MutexInfo;
typedef struct _MutexInfo* pMutexInfo;

struct _MutexInfo {
	Str name[MAX_PATH];
	MutexHandle handle;
};

Bool mutexCreate(pMutexInfo mutexInfo, pStr name);

Dword mutexLock(pMutexInfo mutexInfo);

Bool mutexUnlock(pMutexInfo mutexInfo);

Bool mutexOpen(pMutexInfo mutexInfo, pStr name);

Bool mutexClose(pMutexInfo mutexInfo);
