# LeanWin Documentation

This library provides functions for working with windows.h in C.

## Prerequisites

Before using this library, ensure that you have:

- A C compiler compatible with the Windows environment.
- Included "LeanTypes.h" header file.

## Process

### Defining a Process

To define a process, make a `ProcessInfo` structure.

```c
// Define ProcessInfo structure
ProcessInfo process;
```

### Creating a Process

To create a new process, use the `processCreate()` function and pass it the process to create and a pointer to a `ProcessInfo` structure.
It returns `Bool`, indicating its success.

```c
// Define a Process
ProcessInfo processInfo;

Bool success = processCreate(argv[1], &processInfo);
if (!success) {
    // Handle error
}
```

### Waiting for a Process

To wait for a process to finish, use the `processWait()` function and pass it a pointer to a `ProcessInfo` structure.
The `processWait()` function automatically stores the process exit code in the `ProcessInfo.exitCode` field upon process termination.
It returns the value that `WaitForSingleObject()` would return.
For currently running processes, the `ProcessInfo.exitCode` field is set to `STILL_ACTIVE`.

```c
// Wait for a process to finish
processWait(&processInfo);
```

### Exiting a Process with a return value

To exit a process and return a value, use the `processExit()` function and pass it a `uInt` value.

```c
// Exit a process returning a value
processExit(1);
```

### Closing an active Process

To close an active process, use the `processClose()` function and pass it a pointer to a `ProcessInfo` structure.
The `processClose()` function closes the `ProcessInfo.processHandle` and `ProcessInfo.threadHandle` fields.
It returns `Bool`, indicating its success determined by the `or` evaluation of both `CloseHandle()` calls.

```c
// Close a currently active process
processClose(&processInfo);
```

### Getting a pseudo handle to the current Process

To get a pseudo handle to the current process, use the `processGetPseudoHandle()` function and pass it a pointer to a `ProcessInfo` structure.
The `processGetPseudoHandle()` function fills the `ProcessInfo.processHandle` field with a pseudo handle to the current process.
Pseudo handles only work in the current process.

```c
// Get a pseudo handle to the current process
processGetPseudoHandle(&processInfo);
```

### Gettin the current Process Id

To get the current process Id, use the `processGetId()` function and pass it a pointer to a `ProcessInfo` struture.
The `processGetId()` function fills the `ProcessInfo.processId` field with the current process Id.

```c
// Get the current process Id
processGetId(&processInfo);
```

### Process Program Example

```c
ProcessInfo newProcess, currentProcess;
Bool processCreated;

processCreated = processCreate(argv[1], &newProcess);
if (!processCreated) {
    ErrorLog(_T("Process Creation Failed"));
	processExit(1);
}

processWait(&newProcess);

_tprintf(_T("The process exit code was <%d>\n"), newProcess.exitCode);

processClose(&newProcess);

processGetId(&currentProcess);

_tprintf(_T("The current ProcessId = <%d>\n"), currentProcess.processId);

ExitProcess(0);
```

## Event

### Defining an Event

```c
// Define EventInfo structure
EventInfo eventInfo;
```

### Creating an Event

To create an Event, call `eventCreate()`.

```c
// Define an Event
EventInfo eventInfo;

// Create the Event
Bool success = eventCreate(&eventInfo,
            1,    // initialState
            1,    // manualReset
            _T("Chipi"));
if (!success) {
    // Handle error
}
```

### Setting an Event

To set/reset an Event, call `eventSet()` and `eventReset()`.

```c
// Set an Event
Bool setSuccess = eventSet(&eventinfo);
if (!setSuccess) {
    // Handle error
}

// Reset an Event
Bool resetSuccess = eventReset(&eventInfo);
if (!resetSuccess) {
    // Handle error
}
```

### Waiting on an Event

To wait on an Event, call `eventWait()`.

```c
// Wait on an Event
eventWait(&eventInfo);
```

### Closing an Event

To close an Event, call `eventClose()`.

```c
// Close an Event
Bool success = eventClose(&eventinfo);
if (!success) {
    // Handle error
}
```



## CriticalSection

A CriticalSection works like a Mutex but only in the current process
Use it when you need to protect a critical section in the current process

### Defining a CriticalSection

```c
// Define CriticalSectionInfo structure
CriticalSectionInfo criticalSectionInfo;
```

### Creating a CriticalSection

To create a CriticalSection, call `criticalSectionCreate()`.

```c
// Define a CriticalSection
CriticalSectionInfo criticalSectionInfo;

// Create the CriticalSection
criticalSectionCreate(&criticalSectionInfo);
```

### Entering and Leaving a CriticalSection

To protect a critical section of code with a CriticalSection, use `criticalSectionEnter()` and `criticalSectionLeave()`.

```c
// Enter the CriticalSection
criticalSectionEnter(&criticalSectionInfo);

// Critical section

// Leave the CriticalSection
criticalSectionLeave(&criticalSectionInfo);
```

### Closing a CriticalSection

When you're done with the CriticalSection, close it using `criticalSectionClose()`.

```c
// Close the CriticalSection
criticalSectionClose(&criticalSectionInfo);
```

### Debugging a CriticalSection

It only works if `LEAN_DEBUG` is defined in `LeanTypes.h`
Sometimes there might be a race condition in `mutexInfo.state`, specially when a thread is waiting on a mutex.
The printing of the state might be affected by a locking/unlocking of a mutex in another thread.

```c
// Print CriticalSection information
criticalSectionDebug(&criticalSectionInfo);
```



## Mutex

A Mutex protects a critical section in various processes
Use it when you need to protect a critical section in various processes, usually with shared memory

### Defining a Mutex

```c
// Define MutexInfo structure
MutexInfo mutexInfo;
```

### Creating a Mutex

To create a Mutex, call `mutexCreate()`.

```c
// Define a Mutex
MutexInfo mutexInfo;

// Create the Mutex
Bool success = mutexCreate(&mutexInfo, _T("Chipi"));
if (!success) {
    // Handle error
}
```

### Locking and Unlocking a Mutex

To protect a critical section of code with a Mutex, use `mutexLock()` and `mutexUnlock()`.

```c
// Lock the Mutex
mutexLock(&mutexInfo);

// Critical section

// Unlock the Mutex
mutexUnlock(&mutexInfo);
```

### Closing a Mutex

When you're done with the Mutex, close it using `mutexClose()`.

```c
// Close the Mutex
Bool success = mutexClose(&mutexInfo);
if (!success) {
    // Handle error
}
```

### Debugging Mutexes

It only works if `LEAN_DEBUG` is defined in `LeanTypes.h`
Sometimes there might be a race condition in `mutexInfo.state`, specially when a thread is waiting on a mutex.
The printing of the state might be affected by a locking/unlocking of a mutex in another thread.

```c
// Print Mutex information
mutexDebug(&mutexInfo);
```

## Notes

- Always check the return values of the functions for errors.
- Ensure proper error handling is implemented in case of failures.
