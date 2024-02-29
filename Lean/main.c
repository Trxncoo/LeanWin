#include "Lean.h"

//#define PROCESS
#define REGISTRY
//#define THREAD

int a = 2;
int b = 1;

Dword WINAPI threadFunction(pVoid args) {
	a++;
	_tprintf(_T("A\n"));
	threadExit(a);
}

Dword WINAPI threadFunction2(pVoid args) {
	b++;
	_tprintf(_T("B\n"));
	threadExit(b);
}

int _tmain(int argc, pStr argv[]) {
	LeanInit();

#ifdef PROCESS
	ProcessHandle processHandle;
	ProcessInfo processInfo;
	Bool processCreated;
	ProcessId processId;
	ExitCode processExitCode;

	ZeroMemory(&processInfo, sizeof(processInfo));
	
	processCreated = processCreate(argv[1], &processInfo);

	if (!processCreated) {
		ErrorLog("Process Creation Failed");
		processExit(1);
	}

	processWait(processInfo.hProcess);

	processGetExitCode(processInfo.hProcess, &processExitCode);

	_tprintf(_T("The process exit code was <%d>\n"), processExitCode);

	processCloseHandle(processInfo.hProcess);
	processCloseHandle(processInfo.hThread);

	processId = processGetId();

	_tprintf(_T("The current ProcessId = <%d>\n"), processId);

	ExitProcess(0);
#endif

#ifdef REGISTRY
	pStr key = _T("12345678909876543212345\\1");
	pStr valueName = _T("Value1");
	KeyHandle keyHandle;
	DWORD dataValue = 1023;
	RegistryData registryData;
	RegistryData newData;
	ErrorCode createKeyCode;

	createKeyCode = registryCreateKey(&keyHandle, key);
	if (createKeyCode != ERROR_SUCCESS) {
		ErrorLog(_T("Error Creating the Key"));
		processExit(1);
	}

	_tprintf(_T("Key Created\n"));

	registryFill(&registryData, &dataValue, REG_DWORD, sizeof(DWORD));

	if (registrySetValue(keyHandle, valueName, &registryData) != ERROR_SUCCESS) {
		ErrorLog(_T("Error Setting a Value"));
		registryCloseKey(keyHandle);
		processExit(1);
	}

	_tprintf(_T("Value set\n"));

	if (registryQueryValue(keyHandle, valueName, &newData) != ERROR_SUCCESS) {
		ErrorLog(_T("Error Querying a Value"));
		registryCloseKey(keyHandle);
		processExit(1);
	}

	_tprintf(_T("The Key <%s> has the name <%s> with the value: <%d>\n"), key, valueName, newData.keyDataValue);

	registryDeleteKeyTree(key);	
	registryCloseKey(keyHandle);
	processExit(0);
#endif

#ifdef THREAD
	ThreadInfo threadInfo[2];
	ErrorCode threadExit = 0;

	if (!threadCreate(threadFunction, NULL, &threadInfo[0])) {
		ErrorLog(_T("Thread Creation failed"));
		processExit(1);
	}

	if (!threadCreate(threadFunction2, NULL, &threadInfo[1])) {
		ErrorLog(_T("Thread Creation failed"));
		threadCloseHandle(threadInfo[1].threadHandle);
		processExit(1);
	}

	if (threadWaitAll(2, threadInfo) == WAIT_ALLOCATION_FAILED) {
		ErrorLog(_T("Thread Waiting failed"));
		processExit(1);
	}

	_tprintf(_T("C\n"));

	for (int i = 0; i < 2; ++i) {
		threadGetExitCode(threadInfo[i].threadHandle, &threadExit);
		_tprintf(_T("Thread exit code is <%d:%d>\n"), i, threadExit);
	}

	for (int i = 0; i < 2; ++i) {
		if (!threadCloseHandle(threadInfo[i].threadHandle)) {
			ErrorLog(_T("Error closing thread handle"));
			processExit(1);
		}
	}

	_tprintf(_T("Thread Created successfully\n"));
	processExit(1);

#endif
}