#include "LeanThreads.h"

Bool threadCreate(ThreadFunction threadFunction, pVoid threadArgs, pThreadInfo threadInfo) {
	ThreadHandle threadHandle;
	ThreadId threadId;
	
	threadHandle = CreateThread(NULL, 0, threadFunction, threadArgs, 0, &threadId);
	if (threadHandle == NULL) {
		return 0;
	}
	
	threadInfo->threadHandle = threadHandle;
	threadInfo->threadId = threadId;

	return 1;
}

Bool threadOpen(ThreadId threadId, pThreadInfo threadInfo) {
	ThreadHandle threadHandle;

	threadHandle = OpenThread(THREAD_ALL_ACCESS, FALSE, threadId);
	if (threadHandle == NULL) {
		return 0;
	}

	threadInfo->threadHandle = threadHandle;
	threadInfo->threadId;

	return 1;
}

ExitCode threadWait(ThreadHandle threadHandle) {
	return WaitForSingleObject(threadHandle, INFINITE);
}

Bool threadCloseHandle(ThreadHandle threadHandle) {
	return CloseHandle(threadHandle);
}

Void threadExit(Dword exitCode) {
	ExitThread(exitCode);
}

Bool threadGetExitCode(ThreadHandle threadHandle, pExitCode exitCode) {
	return GetExitCodeThread(threadHandle, exitCode);
}

ThreadHandle threadGetPseudoHandle(Void) {
	return GetCurrentThread();
}

ThreadId threadGetId(Void) {
	return GetCurrentThreadId();
}

pThreadHandle threadInfoToHandles(Dword count, pThreadInfo threadInfo) {
	pThreadHandle threadHandles;

	threadHandles = (pThreadHandle)malloc(sizeof(ThreadHandle) * count);
	if (threadHandles == NULL) {
		return NULL;
	}

	for (uInt i = 0; i < count; ++i) {
		threadHandles[i] = threadInfo[i].threadHandle;
	}

	return threadHandles;
}

Dword threadWaitAll(Dword count, pThreadInfo threadInfos) {
	pThreadHandle threadHandles;
	Dword waitCode;

	threadHandles = threadInfoToHandles(count, threadInfos);
	if (threadHandles == NULL) {
		return ERROR_NOT_ENOUGH_MEMORY;
	}

	waitCode = WaitForMultipleObjects(count, threadHandles, 1, INFINITE);

	free(threadHandles);

	return waitCode;
}

Dword threadWaitOne(Dword count, pThreadInfo threadInfos) {
	pThreadHandle threadHandles;
	Dword waitCode;

	threadHandles = threadInfoToHandles(count, threadInfos);
	if (threadHandles == NULL) {
		return ERROR_NOT_ENOUGH_MEMORY;
	}

	waitCode = WaitForMultipleObjects(count, threadHandles, 0, INFINITE);

	free(threadHandles);
	
	return waitCode;
}

Void threadMutexFill(pMutexInfo mutexInfo, pStr mutexName) {
	_tcscpy_s(mutexInfo->mutexName, MAX_PATH, mutexName);
}

Bool threadMutexCreate(pMutexInfo mutexInfo, Dword mutexFlag) {
	MutexHandle mutexHandle;

	mutexHandle = CreateMutexEx(NULL, mutexInfo->mutexName, mutexFlag, EVENT_ALL_ACCESS);
	if (mutexHandle == NULL) {
		return 0;
	}

	mutexInfo->mutexHandle = mutexHandle;

	return 1;
}