#pragma once

#include "types.h"
#include <windows.h>
#include <tchar.h>

typedef LPTSTR pStr;
typedef LSTATUS ErrCode;
typedef HANDLE Handle;
typedef DWORD ExitCode;

typedef PROCESS_INFORMATION ProcessInfo;
typedef LPPROCESS_INFORMATION pProcessInfo;

ErrCode process_create(pStr command_line, pProcessInfo pi);
//ExitCode process_wait(Handle handle);
