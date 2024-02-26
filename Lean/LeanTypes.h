#pragma once

#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

typedef LPTSTR pStr;
typedef TCHAR Str;

typedef PROCESS_INFORMATION ProcessInfo;
typedef LPPROCESS_INFORMATION pProcessInfo;

typedef struct ThreadInfo ThreadInfo;
typedef ThreadInfo* pThreadInfo;

typedef STARTUPINFO StartupInfo;

typedef DWORD Dword, ExitCode, ProcessId, ThreadId, KeyDataType, KeyDataSize;
typedef LPDWORD pExitCode, pKeyDataSize, pKeyDataType, pThreadId;

typedef LSTATUS ErrorCode;
typedef HANDLE ProcessHandle, ThreadHandle;

typedef LPTHREAD_START_ROUTINE ThreadFunction;
typedef void Void;
typedef LPVOID pVoid;

typedef HKEY KeyHandle;
typedef PHKEY pKeyHandle;
typedef BYTE KeyDataValue;
typedef LPBYTE pKeyDataValue;

typedef BOOL Bool;
typedef UINT uInt;

struct ThreadInfo {
	ThreadHandle threadHandle;
	ThreadId threadId;
};

#define True 1;
#define False 0;