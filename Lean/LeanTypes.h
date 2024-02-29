#pragma once

#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

typedef LPTSTR pStr;
typedef TCHAR Str;

typedef INT Int;

typedef PROCESS_INFORMATION ProcessInfo;
typedef LPPROCESS_INFORMATION pProcessInfo;

typedef STARTUPINFO StartupInfo;

typedef DWORD Dword, ExitCode, ProcessId, ThreadId, KeyDataType, KeyDataSize;
typedef LPDWORD pExitCode, pKeyDataSize, pKeyDataType, pThreadId;

typedef LSTATUS ErrorCode;
typedef HANDLE ProcessHandle, ThreadHandle, MutexHandle;
typedef LPHANDLE pThreadHandle;

typedef LPTHREAD_START_ROUTINE ThreadFunction;
typedef void Void;
typedef LPVOID pVoid;

typedef HKEY KeyHandle;
typedef PHKEY pKeyHandle;
typedef BYTE KeyDataValue;
typedef LPBYTE pKeyDataValue;

typedef BOOL Bool;
typedef UINT uInt;

typedef struct _ThreadInfo ThreadInfo;
typedef struct _ThreadInfo* pThreadInfo;

struct _ThreadInfo {
	ThreadHandle threadHandle;
	ThreadId threadId;
};

typedef struct _MutexInfo MutexInfo;
typedef struct _MutexInfo* pMutexInfo;

struct _MutexInfo {
	Str mutexName[MAX_PATH];
	MutexHandle mutexHandle;
};

// Probably can just use ERROR_NOT_ENOUGH_MEMORY, but who cares tbh, use it if u want
//#define WAIT_ALLOCATION_FAILED (WAIT_FAILED - 1)