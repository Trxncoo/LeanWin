#include "LeanProcesses.h"

Bool processCreate(pStr commandLine, pProcessInfo pi) {
	StartupInfo si;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);

	return CreateProcess(NULL, commandLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, pi);
}

ExitCode processWait(ProcessHandle processHandle) {
	return WaitForSingleObject(processHandle, INFINITE);
}

Void processExit(uInt exitCode) {
	ExitProcess(exitCode);
}

Bool processGetExitCode(ProcessHandle processHandle, pExitCode exitCode) {
	return GetExitCodeProcess(processHandle, exitCode);
}

Bool processCloseHandle(ProcessHandle processHandle) {
	return CloseHandle(processHandle);
}

ProcessHandle processGetPseudoHandle(Void) {
	return GetCurrentProcess();
}

ProcessId processGetId(Void) {
	return GetCurrentProcessId();
}
