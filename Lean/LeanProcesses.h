#pragma once

#include "LeanTypes.h"

Bool processCreate(pStr commandLine, pProcessInfo pi);

ExitCode processWait(Handle processHandle);

void processExit(uInt exitCode);

Bool processGetExitCode(Handle processHandle, pExitCode exitCode);

Bool processCloseHandle(Handle processHandle);

Handle processGetPseudoHandle();

ProcessId processGetId();
