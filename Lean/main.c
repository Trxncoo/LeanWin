#include "Lean.h"

//#define PROCESS
#define REGISTRY

int _tmain(int argc, TCHAR* argv[]) {
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
	KeyDataType dataType = REG_DWORD;
	KeyDataType dataTypeQueried;
	DWORD dataValue = 20;
	DWORD dataQueried;
	KeyDataSize dataSize = sizeof(DWORD);
	KeyDataSize dataSizeQueried;
	ErrorCode createKeyCode = registryCreateKey(&keyHandle, key);

	if (createKeyCode != ERROR_SUCCESS) {
		ErrorLog(_T("Error Creating the Key"));
		processExit(1);
	}

	_tprintf(_T("Key Created\n"));

	if (registrySetValue(keyHandle, valueName, dataType, (pKeyDataValue)&dataValue, dataSize) != ERROR_SUCCESS) {
		ErrorLog(_T("Error Setting a Value"));
		registryCloseKey(keyHandle);
		processExit(1);
	}

	_tprintf(_T("Value set\n"));

	if (registryQueryValue(keyHandle, valueName, &dataTypeQueried, (pKeyDataValue)&dataQueried, &dataSizeQueried) != ERROR_SUCCESS) {
		ErrorLog(_T("Error Querying a Value"));
		registryCloseKey(keyHandle);
		processExit(1);
	}

	_tprintf(_T("The Key <%s> has the name <%s> with the value: <%d>\n"), key, valueName, dataQueried);

	registryDeleteKeyTree(key);	
	registryCloseKey(keyHandle);
	processExit(0);
#endif
}