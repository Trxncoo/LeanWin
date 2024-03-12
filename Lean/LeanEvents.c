#include "LeanEvents.h"

Bool eventCreate(pEventInfo eventInfo, Bool initialState, Bool manualReset, pStr name) {
	EventHandle eventHandle;

	eventHandle = CreateEvent(NULL, manualReset, initialState, eventInfo->name);
	if (eventHandle == NULL) {
		return 0;
	}

	eventInfo->handle = eventHandle;
	_tcscpy_s(eventInfo->name, MAX_PATH - 1, name);

	return 1;
}

Bool eventSet(pEventInfo eventInfo) {	
	return SetEvent(eventInfo->handle);
}

Bool eventReset(pEventInfo eventInfo) {
	return ResetEvent(eventInfo->handle);
}

Bool eventClose(pEventInfo eventInfo) {
	return CloseHandle(eventInfo->handle);
}

ExitCode eventWait(pEventInfo eventInfo) {
	return WaitForSingleObject(eventInfo->handle, INFINITE);
}