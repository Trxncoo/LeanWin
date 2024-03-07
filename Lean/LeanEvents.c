#include "LeanEvents.h"

Bool eventCreate(pEventInfo eventInfo, Bool initialState, Bool manualReset, pStr name) {
	EventHandle eventHandle;

	eventHandle = CreateEvent(NULL, manualReset, initialState, eventInfo->name);
	if (eventHandle == NULL) {
		return 0;
	}

	eventInfo->handle = eventHandle;
	eventInfo->state = initialState;
	_tcscpy_s(eventInfo->name, MAX_PATH - 1, name);

	return 1;
}

Bool eventSet(pEventInfo eventInfo) {
	Bool setResult;
	
	setResult = SetEvent(eventInfo->handle);
	if (setResult) {
		eventInfo->state = setResult;
	}
	
	return setResult;
}

Bool eventReset(pEventInfo eventInfo) {
	Bool resetResult;

	resetResult = ResetEvent(eventInfo->handle);
	if (resetResult) {
		eventInfo->state = resetResult;
	}

	return resetResult;
}

Bool eventClose(pEventInfo eventInfo) {
	return CloseHandle(eventInfo->handle);
}

ExitCode eventWait(pEventInfo eventInfo) {
	return WaitForSingleObject(eventInfo->handle, INFINITE);
}