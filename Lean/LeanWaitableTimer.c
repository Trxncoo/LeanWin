#include "LeanWaitableTimer.h"

Bool waitableTimerCreate(pWaitableTimerInfo waitableTimerInfo, pStr name, Bool manualReset) {
	WaitableTimerHandle waitableTimerHandle;

	waitableTimerHandle = CreateWaitableTimer(NULL, manualReset, name);
	if (waitableTimerHandle == NULL) {
		return 0;
	}

	waitableTimerInfo->handle = waitableTimerHandle;
	_tcscpy_s(waitableTimerInfo->name, MAX_PATH - 1, name);

	return 1;
}

Bool waitableTimerSet(pWaitableTimerInfo waitableTimerInfo, pTimeInfo timeInfo, AsyncFunction asyncFunction, pVoid args) {
	return SetWaitableTimer(waitableTimerInfo->handle, timeInfo, 0, asyncFunction, args, FALSE);
}

Dword waitableTimerWait(pWaitableTimerInfo waitableTimerInfo) {
	return WaitForSingleObject(waitableTimerInfo->handle, INFINITE);
}

Bool waitableTimerCancel(pWaitableTimerInfo waitableTimerInfo) {
	return CancelWaitableTimer(waitableTimerInfo->handle);
}

Bool waitableTimerClose(pWaitableTimerInfo waitableTimerInfo) {
	return CloseHandle(waitableTimerInfo->handle);
}