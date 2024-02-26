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
