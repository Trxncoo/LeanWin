#pragma once

#include "LeanTypes.h"

typedef struct _EventInfo EventInfo; 
typedef struct _EventInfo* pEventInfo;

typedef HANDLE EventHandle;

struct _EventInfo {
	Str name[MAX_PATH];
	EventHandle handle;
};

Bool eventCreate(pEventInfo eventInfo, Bool initialState, Bool manualReset, pStr name);

Bool eventSet(pEventInfo eventInfo);

Bool eventReset(pEventInfo eventInfo);

Bool eventClose(pEventInfo eventInfo);

ExitCode eventWait(pEventInfo eventInfo);