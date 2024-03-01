#include "Lean.h"

//#define PROCESS
//#define REGISTRY
#define THREAD

typedef struct _ThreadPacket ThreadPacket;
typedef struct _ThreadPacket* pThreadPacket;

struct _ThreadPacket{
	Int number;
	Int currentEvenSum;
	Int currentPrimeSum;
	pMutexInfo mutexInfo;
};

Void threadPacketFill(pThreadPacket threadPacket, Int number, Int currentEvenSum, Int currentPrimeSum, pMutexInfo mutexInfo) {
	threadPacket->number = number;
	threadPacket->currentEvenSum = currentEvenSum;
	threadPacket->currentPrimeSum = currentPrimeSum;
	threadPacket->mutexInfo = mutexInfo;
}

Dword WINAPI threadEvenFunction(pVoid args) {
	Int evenCount = 0;
	pThreadPacket threadPacket = (pThreadPacket)args;

	for (Int i = 1; i <= threadPacket->number; ++i) {
		if (i % 2 == 0) {
			threadPacket->currentEvenSum += i;
			++evenCount;
		}
	}

	threadExit(1);
}

DWORD IsPrime(DWORD num) {
	if (num <= 1)  
		return 0;

	for (DWORD i = 2; i < num; i++) {
		if (num % i == 0) {
			return 0;
		}
	}
	return 1; // se devolver 1 é numero primo
}

Dword WINAPI threadPrimeFunction(pVoid args) {
	Int primeCount = 0;
	pThreadPacket threadPacket = (pThreadPacket)args;

	for (Int i = 1; i <= threadPacket->number; ++i) {
		if (IsPrime(i)) {
			threadPacket->currentPrimeSum += i;
			++primeCount;
		}
	}

	threadExit(1);
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
	ThreadPacket threadPacket;
	MutexInfo mutexInfo;

	_tcscpy_s(mutexInfo.name, MAX_PATH - 1, _T("Nome"));

	mutexCreate(&mutexInfo);

	threadPacketFill(&threadPacket, 1000, 0, 0, &mutexInfo);

	if (!threadCreate(threadEvenFunction, &threadPacket, &threadInfo[0])) {
		ErrorLog(_T("Thread Creation failed"));
		processExit(1);
	}

	if (!threadCreate(threadPrimeFunction, &threadPacket, &threadInfo[1])) {
		ErrorLog(_T("Thread Creation failed"));
		threadCloseHandle(threadInfo[1].handle);
		processExit(1);
	}

	threadWaitGroup(2, threadInfo, 0);

	for (int i = 0; i < 2; ++i) {
		_tprintf(_T("Exit code: <%d>\n"), threadInfo[i].exitCode);
	}

	for (Int i = 0; i < 2; ++i) {
		if (!threadCloseHandle(&threadInfo[i])) {
			ErrorLog(_T("Error closing thread handle"));
			processExit(1);
		}
	}

	mutexCloseHandle(&mutexInfo);

	_tprintf(_T("Final sum is: <%d:%d>\n"), threadPacket.currentPrimeSum, threadPacket.currentEvenSum);
	processExit(1);

#endif
}