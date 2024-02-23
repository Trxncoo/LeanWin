#pragma once

#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

typedef LSTATUS ErrCode;
typedef LPTSTR pStr;
typedef TCHAR Str;
typedef PROCESS_INFORMATION ProcessInfo;
typedef LPPROCESS_INFORMATION pProcessInfo;
typedef STARTUPINFO StartupInfo;
typedef DWORD ExitCode;
typedef LSTATUS ErrorCode;
typedef LPDWORD pExitCode;
typedef DWORD ProcessId;
typedef HANDLE ProcessHandle;
typedef HKEY KeyHandle;
typedef DWORD KeyDataType;
typedef LPDWORD pKeyDataSize;
typedef LPDWORD pKeyDataType;
typedef BYTE KeyDataValue;
typedef LPBYTE pKeyDataValue;
typedef DWORD KeyDataSize;
typedef PHKEY pKeyHandle;
typedef BOOL Bool;
typedef UINT uInt;

#define True 1;
#define False 0;