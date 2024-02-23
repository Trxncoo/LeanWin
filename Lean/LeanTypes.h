#pragma once

#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

typedef LSTATUS ErrCode;
typedef LPTSTR pStr;
typedef PROCESS_INFORMATION ProcessInfo;
typedef LPPROCESS_INFORMATION pProcessInfo;
typedef STARTUPINFO StartupInfo;
typedef DWORD ExitCode;
typedef LPDWORD pExitCode;
typedef DWORD ProcessId;
typedef HANDLE Handle;
typedef BOOL Bool;
typedef UINT uInt;

#define True 1;
#define False 0;