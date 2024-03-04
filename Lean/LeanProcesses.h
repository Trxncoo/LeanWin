#pragma once

#include "LeanTypes.h"

typedef PROCESS_INFORMATION ProcessInfo;
typedef LPPROCESS_INFORMATION pProcessInfo;

typedef STARTUPINFO StartupInfo;

typedef HANDLE ProcessHandle;
typedef DWORD ProcessId;

Bool processCreate(pStr commandLine, pProcessInfo pi);

ExitCode processWait(ProcessHandle processHandle);

Void processExit(uInt exitCode);

Bool processGetExitCode(ProcessHandle processHandle, pExitCode exitCode);

Bool processCloseHandle(ProcessHandle processHandle);

ProcessHandle processGetPseudoHandle(Void);

ProcessId processGetId(Void);
