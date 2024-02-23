#include "process.h"

ErrCode process_create(pStr command_line, pProcessInfo pi) {
	STARTUPINFO si;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	return CreateProcess(NULL, command_line, NULL, NULL, FALSE, 0, NULL, NULL, &si, pi);
}
/*
ExitCode process_wait(Handle handle) {
	return WaitForSingleObject(handle, INFINITE);
}
*/