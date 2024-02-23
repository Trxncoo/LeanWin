#pragma once

#include "LeanTypes.h"

Bool processCreate(pStr commandLine, pProcessInfo pi);

ExitCode processWait(ProcessHandle processHandle);

void processExit(uInt exitCode);

Bool processGetExitCode(ProcessHandle processHandle, pExitCode exitCode);

Bool processCloseHandle(ProcessHandle processHandle);

ProcessHandle processGetPseudoHandle();

ProcessId processGetId();
