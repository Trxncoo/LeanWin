#include "LeanProcesses.h"


Bool processCreate(pStr commandLine, pProcessInfo pi) {
	StartupInfo si;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);

	return CreateProcess(NULL, commandLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, pi);
}

ExitCode processWait(Handle processHandle) {
	return WaitForSingleObject(processHandle, INFINITE);
}

void processExit(uInt exitCode) {
	ExitProcess(exitCode);
}

Bool processGetExitCode(Handle processHandle, pExitCode exitCode) {
	return GetExitCodeProcess(processHandle, exitCode);
}

Bool processCloseHandle(Handle processHandle) {
	return CloseHandle(processHandle);
}

Handle processGetPseudoHandle() {
	return GetCurrentProcess();
}

ProcessId processGetId() {
	return GetCurrentProcessId();
}
