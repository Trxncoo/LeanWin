#pragma once

#include "LeanTime.h"

typedef HANDLE WaitableTimerHandle;

typedef PTIMERAPCROUTINE AsyncFunction;

typedef struct _WaitableTimerInfo WaitableTimerInfo;
typedef struct _WaitableTimerInfo* pWaitableTimerInfo;

struct _WaitableTimerInfo {
	pStr name[MAX_PATH];
	WaitableTimerHandle handle;
};

Bool waitableTimerCreate(pWaitableTimerInfo waitableTimerInfo, pStr name, Bool manualReset);

Bool waitableTimerSet(pWaitableTimerInfo waitableTimerInfo, pTimeInfo timeInfo, AsyncFunction asyncFunction, pVoid args);

Dword waitableTimerWait(pWaitableTimerInfo waitableTimerInfo);

Bool waitableTimerCancel(pWaitableTimerInfo waitableTimerInfo);

Bool waitableTimerClose(pWaitableTimerInfo waitableTimerInfo);