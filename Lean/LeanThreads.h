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

// Fills threadInfo with 
Bool threadCreate(ThreadFunction threadFunction, pVoid threadArgs, pThreadInfo threadInfo);

// Returns thread ExitCode and also stores it in threadInfo
ExitCode threadWait(pThreadInfo threadInfo);

// Closes threadInfo Handle
Bool threadClose(pThreadInfo threadInfo);

// Exits a thread, returning exitCode
Void threadExit(Dword exitCode);

// Fills threadInfo->handle with current Thread Pseudo Handle
Void threadGetPseudoHandle(pThreadInfo threadInfo);

// Fills threadInfo->id with current Thread Id
Void threadGetId(pThreadInfo threadInfo);

// Blocks until all/one thread(s) return(s)
ExitCode threadWaitGroup(Dword count, pThreadInfo threadInfo, Bool all);

static pThreadHandle threadInfoToHandles(Dword count, pThreadInfo threadInfo);
