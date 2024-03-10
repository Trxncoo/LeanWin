#include "Lean.h"

#define PROCESS
//#define REGISTRY
//#define THREAD

typedef struct _ThreadPacket ThreadPacket;
typedef struct _ThreadPacket* pThreadPacket;

struct _ThreadPacket{
	Int number;
	Int currentEvenSum;
	Int currentPrimeSum;
	pCriticalSectionInfo criticalSectionInfo;
};

Void threadPacketFill(pThreadPacket threadPacket, Int number, Int currentEvenSum, Int currentPrimeSum, pCriticalSectionInfo criticalSectionInfo) {
	threadPacket->number = number;
	threadPacket->currentEvenSum = currentEvenSum;
	threadPacket->currentPrimeSum = currentPrimeSum;
	threadPacket->criticalSectionInfo = criticalSectionInfo;
}

Dword WINAPI threadEvenFunction(pVoid args) {
	Int evenCount = 0;
	pThreadPacket threadPacket = (pThreadPacket)args;

	criticalSectionEnter(threadPacket->criticalSectionInfo);

	for (Int i = 1; i <= threadPacket->number; ++i) {
		if (i % 2 == 0) {
			threadPacket->currentEvenSum += i;
			++evenCount;
		}
	}

	criticalSectionLeave(threadPacket->criticalSectionInfo);

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

	criticalSectionEnter(threadPacket->criticalSectionInfo);

	for (Int i = 1; i <= threadPacket->number; ++i) {
		if (IsPrime(i)) {
			threadPacket->currentPrimeSum += i;
			++primeCount;
		}
	}

	criticalSectionLeave(threadPacket->criticalSectionInfo);

	threadExit(1);
}

int _tmain(int argc, pStr argv[]) {
	LeanInit();

#ifdef PROCESS
	ProcessInfo newProcess, currentProcess;
	Bool processCreated;
	
	processCreated = processCreate(&newProcess, argv[1]);
	if (!processCreated) {
		ErrorLog(_T("Process Creation Failed"));
		processExit(1);
	}

	processWait(&newProcess);

	_tprintf(_T("The process exit code was <%d>\n"), newProcess.exitCode);

	processClose(&newProcess);

	processGetId(&currentProcess);

	_tprintf(_T("The current ProcessId = <%d>\n"), currentProcess.processId);

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
	CriticalSectionInfo criticalSectionInfo;

	criticalSectionCreate(&criticalSectionInfo);

	criticalSectionDebug(&criticalSectionInfo);

	threadPacketFill(&threadPacket, 1000, 0, 0, &criticalSectionInfo);

	if (!threadCreate(threadEvenFunction, &threadPacket, &threadInfo[0])) {
		ErrorLog(_T("Thread Creation failed"));
		processExit(1);
	}

	if (!threadCreate(threadPrimeFunction, &threadPacket, &threadInfo[1])) {
		ErrorLog(_T("Thread Creation failed"));
		threadCloseHandle(threadInfo[1].handle);
		processExit(1);
	}

	threadWaitGroup(2, threadInfo, 1);

	for (int i = 0; i < 2; ++i) {
		_tprintf(_T("Exit code: <%d>\n"), threadInfo[i].exitCode);
	}

	for (Int i = 0; i < 2; ++i) {
		if (!threadCloseHandle(&threadInfo[i])) {
			ErrorLog(_T("Error closing thread handle"));
			processExit(1);
		}
	}

	criticalSectionClose(&criticalSectionInfo);

	_tprintf(_T("Final sum is: <%d:%d>\n"), threadPacket.currentPrimeSum, threadPacket.currentEvenSum);
	processExit(1);

#endif
}