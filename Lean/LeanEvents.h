#pragma once

#include "LeanTypes.h"

typedef struct _EventInfo EventInfo; 
typedef struct _EventInfo* pEventInfo;

typedef HANDLE EventHandle;

struct _EventInfo {
	Str name[MAX_PATH];
	EventHandle handle;
	Bool state;
};

// Must fill eventInfo with event name
Bool eventCreate(pEventInfo eventInfo, Bool initialState);

Bool eventSet(pEventInfo eventInfo);

Bool eventReset(pEventInfo eventInfo);

Bool eventCloseHandle(pEventInfo eventInfo);

ExitCode eventWait(pEventInfo eventInfo);