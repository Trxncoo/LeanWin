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

typedef DWORD Dword, ExitCode;
typedef LPDWORD pExitCode;

typedef LSTATUS ErrorCode;

typedef void Void;
typedef LPVOID pVoid;

typedef BOOL Bool;
typedef UINT uInt;


// Probably can just use ERROR_NOT_ENOUGH_MEMORY, but who cares tbh, use it if u want
//#define WAIT_ALLOCATION_FAILED (WAIT_FAILED - 1)