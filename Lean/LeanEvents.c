#include "LeanEvents.h"

Bool eventCreate(pEventInfo eventInfo, Bool initialState) {
	EventHandle eventHandle;

	eventHandle = CreateEvent(NULL, TRUE, initialState, eventInfo->name);
	if (eventHandle == NULL) {
		return 0;
	}

	eventInfo->handle = eventHandle;
	eventInfo->state = initialState;

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

Bool eventCloseHandle(pEventInfo eventInfo) {
	return CloseHandle(eventInfo->handle);
}

ExitCode eventWait(pEventInfo eventInfo) {
	return WaitForSingleObject(eventInfo->handle, INFINITE);
}