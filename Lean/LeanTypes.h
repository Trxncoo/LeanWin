#pragma once

#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

typedef LPTSTR pStr;
typedef TCHAR Str;

typedef INT Int;

typedef PROCESS_INFORMATION ProcessInfo;
typedef LPPROCESS_INFORMATION pProcessInfo;

typedef STARTUPINFO StartupInfo;

typedef DWORD Dword, ExitCode, ProcessId, KeyDataType, KeyDataSize;
typedef LPDWORD pExitCode, pKeyDataSize, pKeyDataType;

typedef LSTATUS ErrorCode;
typedef HANDLE ProcessHandle;

typedef void Void;
typedef LPVOID pVoid;

typedef HKEY KeyHandle;
typedef PHKEY pKeyHandle;
typedef BYTE KeyDataValue;
typedef LPBYTE pKeyDataValue;

typedef BOOL Bool;
typedef UINT uInt;


// Probably can just use ERROR_NOT_ENOUGH_MEMORY, but who cares tbh, use it if u want
//#define WAIT_ALLOCATION_FAILED (WAIT_FAILED - 1)