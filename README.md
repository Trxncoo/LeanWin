# LeanWin Documentation

This library provides functions for working with windows.h in C.

## Prerequisites

Before using this library, ensure that you have:

- A C compiler compatible with the Windows environment.
- Included "LeanTypes.h" header file.


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
