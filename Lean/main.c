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
};

Void threadPacketFill(pThreadPacket threadPacket, Int number, Int currentEvenSum, Int currentPrimeSum) {
	threadPacket->number = number;
	threadPacket->currentEvenSum = currentEvenSum;
	threadPacket->currentPrimeSum = currentPrimeSum;
}

Dword WINAPI threadEvenFunction(pVoid args) {
	Int evenCount = 0;
	pThreadPacket threadPacket = (pThreadPacket)args;

	for (Int i = 1; i <= threadPacket->number; ++i) {
		if (i % 2 == 0) {
			threadPacket->currentEvenSum += i;
			++evenCount;

			if (evenCount % 200 == 0) {
				Sleep(1000);
			}
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

			if (primeCount % 15 == 0)
				Sleep(1000);
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

	threadPacketFill(&threadPacket, 1000, 0, 0);

	if (!threadCreate(threadEvenFunction, &threadPacket, &threadInfo[0])) {
		ErrorLog(_T("Thread Creation failed"));
		processExit(1);
	}

	if (!threadCreate(threadPrimeFunction, &threadPacket, &threadInfo[1])) {
		ErrorLog(_T("Thread Creation failed"));
		threadCloseHandle(threadInfo[1].threadHandle);
		processExit(1);
	}

	Dword objectExit;

	objectExit = threadWaitOne(2, threadInfo);
	if (objectExit == ERROR_NOT_ENOUGH_MEMORY) {
		ErrorLog(_T("Thread Waiting failed"));
		processExit(1);
	}

	if (objectExit == WAIT_OBJECT_0) {
		_tprintf(_T("Even Sum: <%d>\n"), threadPacket.currentEvenSum);
		threadWait(threadInfo[1].threadHandle);
	}
	if (objectExit == WAIT_OBJECT_0 + 1) {
		_tprintf(_T("Prime Sum: <%d>\n"), threadPacket.currentPrimeSum);
		threadWait(threadInfo[0].threadHandle);
	}
	

	for (Int i = 0; i < 2; ++i) {
		threadGetExitCode(threadInfo[i].threadHandle, &threadExit);
		_tprintf(_T("Thread exit code is <%d:%d>\n"), i, threadExit);
	}

	for (Int i = 0; i < 2; ++i) {
		if (!threadCloseHandle(threadInfo[i].threadHandle)) {
			ErrorLog(_T("Error closing thread handle"));
			processExit(1);
		}
	}

	_tprintf(_T("Final sum is: <%d:%d>\n"), threadPacket.currentPrimeSum, threadPacket.currentEvenSum);
	processExit(1);

#endif
}