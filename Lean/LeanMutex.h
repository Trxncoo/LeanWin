#pragma once

#include "LeanTypes.h"

typedef HANDLE MutexHandle;

typedef struct _MutexInfo MutexInfo;
typedef struct _MutexInfo* pMutexInfo;

struct _MutexInfo {
	Str name[MAX_PATH];
	MutexHandle handle;
	Bool state;
};

Void mutexDebug(pMutexInfo mutexInfo);

Bool mutexCreate(pMutexInfo mutexInfo, pStr name);

Bool mutexClose(pMutexInfo mutexInfo);

Void mutexLock(pMutexInfo mutexInfo);

Void mutexUnlock(pMutexInfo mutexInfo);