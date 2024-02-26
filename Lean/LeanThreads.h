#pragma once

#include "LeanTypes.h"

Bool threadCreate(ThreadFunction threadFunction, pVoid threadArgs, pThreadInfo threadInfo);

Bool threadOpen(ThreadId threadId, pThreadInfo threadInfo);

ExitCode threadWait(ThreadHandle threadHandle);

Bool threadCloseHandle(ThreadHandle threadHandle);

Void threadExit(Dword exitCode);

Bool threadGetExitCode(ThreadHandle threadHandle, pExitCode exitCode);

ThreadHandle threadGetPseudoHandle(Void);

ThreadId threadGetId(Void);

Dword threadWaitAll(Dword count, pThreadInfo threadInfos);

Dword threadWaitOne(Dword count, pThreadInfo threadInfos);

pThreadHandle threadInfoToHandles(Dword count, pThreadInfo threadInfo);