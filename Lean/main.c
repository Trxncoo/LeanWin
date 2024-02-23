#include "Lean.h"

int _tmain(int argc, TCHAR* argv[]) {
	ProcessInfo pi;
	ExitCode waitCode;

	LeanInit();

	if (!processCreate(argv[1], &pi)) {
		ErrorLog(_T("Error creating process\n"));
		processExit(1);
	}

	waitCode = processWait(pi.hProcess);

	if (waitCode == WAIT_FAILED) {
		ErrorLog(_T("Wait Failed"));
		processExit(1);
	}

	processGetExitCode(pi.hProcess, &waitCode);

	_tprintf(_T("%d\n"), waitCode);

	processCloseHandle(pi.hProcess);

	ErrorLog(_T("End"));

	_tprintf(_T("%d\n"), processGetId());

	processExit(1);
}