#include "LeanThreads.h"

Bool threadCreate(ThreadFunction threadFunction, pVoid threadArgs, pThreadInfo threadInfo) {
	ThreadHandle threadHandle;
	ThreadId threadId;
	
	threadHandle = CreateThread(NULL, 0, threadFunction, threadArgs, 0, &threadId);
	if (threadHandle == NULL) {
		return 0;
	}
	
	threadInfo->handle = threadHandle;
	threadInfo->id = threadId;
	threadInfo->exitCode = STILL_ACTIVE;

	return 1;
}

ExitCode threadWait(pThreadInfo threadInfo) {
	ExitCode waitCode;
	waitCode = WaitForSingleObject(threadInfo->handle, INFINITE);
	GetExitCodeThread(threadInfo->handle, &threadInfo->exitCode);
	return waitCode;
}

Bool threadCloseHandle(pThreadInfo threadInfo) {
	return CloseHandle(threadInfo->handle);
}

Void threadExit(Dword exitCode) {
	ExitThread(exitCode);
}

Void threadGetPseudoHandle(pThreadInfo threadInfo) {
	threadInfo->handle = GetCurrentThread();
}

Void threadGetId(pThreadInfo threadInfo) {
	threadInfo->id = GetCurrentThreadId();
}

ExitCode threadWaitGroup(Dword count, pThreadInfo threadInfo, Bool all) {
	pThreadHandle threadHandles;
	ExitCode waitCode;

	threadHandles = threadInfoToHandles(count, threadInfo);
	if (threadHandles == NULL) {
		return ERROR_NOT_ENOUGH_MEMORY;
	}

	waitCode = WaitForMultipleObjects(count, threadHandles, all, INFINITE);

	for (uInt i = 0; i < count; ++i) {
		GetExitCodeThread(threadInfo[i].handle, &threadInfo[i].exitCode);
	}

	free(threadHandles);

	return waitCode;
}

static pThreadHandle threadInfoToHandles(Dword count, pThreadInfo threadInfo) {
	pThreadHandle threadHandles;

	threadHandles = (pThreadHandle)malloc(sizeof(ThreadHandle) * count);
	if (threadHandles == NULL) {
		return NULL;
	}

	for (uInt i = 0; i < count; ++i) {
		threadHandles[i] = threadInfo[i].handle;
	}

	return threadHandles;
}
