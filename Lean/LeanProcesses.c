#include "LeanProcesses.h"

Bool processCreate(pProcessInfo processInfo, pStr commandLine) {
	Bool processCreationResult;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	processCreationResult = CreateProcess(NULL, commandLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

	processInfo->processHandle = pi.hProcess;
	processInfo->processId = pi.dwProcessId;
	processInfo->threadHandle = pi.hThread;
	processInfo->threadId = pi.dwThreadId;
	processInfo->exitCode = STILL_ACTIVE;

	return processCreationResult;
}

ExitCode processWait(pProcessInfo processInfo) {
	ExitCode waitCodeResult, exitCodeResult, exitCode;
	waitCodeResult = WaitForSingleObject(processInfo->processHandle, INFINITE);
	exitCodeResult = GetExitCodeProcess(processInfo->processHandle, &exitCode);
	if (exitCodeResult) {
		processInfo->exitCode = exitCode;
	}

	return waitCodeResult;
}

Void processExit(uInt exitCode) {
	ExitProcess(exitCode);
}

Bool processClose(pProcessInfo processInfo) {
	Bool closeProcessResult, closeThreadResult;
	
	closeProcessResult = CloseHandle(processInfo->processHandle);
	closeThreadResult = CloseHandle(processInfo->threadHandle);

	return closeProcessResult || closeThreadResult;
}

Void processGetPseudoHandle(pProcessInfo processInfo) {
	processInfo->processHandle = GetCurrentProcess();
}

Void processGetId(pProcessInfo processInfo) {
	processInfo->processId = GetCurrentProcessId();
}
