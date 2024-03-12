#pragma once

#include "LeanTypes.h"

typedef HANDLE ThreadHandle;
typedef DWORD ThreadId;
typedef LPHANDLE pThreadHandle;
typedef LPTHREAD_START_ROUTINE ThreadFunction;

typedef struct _ThreadInfo ThreadInfo;
typedef struct _ThreadInfo* pThreadInfo;

struct _ThreadInfo {
	ThreadHandle handle;
	ThreadId id;
	ExitCode exitCode;
};

Bool threadCreate(ThreadFunction threadFunction, pVoid threadArgs, pThreadInfo threadInfo);

ExitCode threadWait(pThreadInfo threadInfo);

Bool threadClose(pThreadInfo threadInfo);

Void threadExit(Dword exitCode);

Void threadGetPseudoHandle(pThreadInfo threadInfo);

Void threadGetId(pThreadInfo threadInfo);

ExitCode threadWaitGroup(Dword count, pThreadInfo threadInfo, Bool all);

static pThreadHandle threadInfoToHandles(Dword count, pThreadInfo threadInfo);
