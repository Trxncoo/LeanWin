#pragma once

#include "LeanTypes.h"

typedef struct _ProcessInfo ProcessInfo;
typedef struct _ProcessInfo* pProcessInfo;

typedef HANDLE ProcessHandle, ThreadHandle;
typedef DWORD ProcessId, ThreadId;

struct _ProcessInfo {
	ProcessHandle processHandle;
	ProcessId processId;
	ThreadHandle threadHandle;
	ThreadId threadId;
	ExitCode exitCode;
};

Bool processCreate(pProcessInfo processInfo, pStr commandLine);

ExitCode processWait(pProcessInfo processInfo);

Void processExit(uInt exitCode);

Bool processClose(pProcessInfo processInfo);

Void processGetPseudoHandle(pProcessInfo processInfo);

Void processGetId(pProcessInfo processInfo);
