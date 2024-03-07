# LeanWin Documentation

This library provides functions for working with windows.h in C.

## Prerequisites

Before using this library, ensure that you have:

- A C compiler compatible with the Windows environment.
- Included "LeanTypes.h" header file.

## Mutexes

### Defining Mutexes

```c
// Define MutexInfo structure
MutexInfo mutexInfo;
```

### Creating a Mutex

To create a mutex, call `mutexCreate()`.

```c
// Define a mutex
MutexInfo mutexInfo;

// Create the mutex
Bool success = mutexCreate(&mutexInfo, _T("Chipi"));
if (!success) {
    // Handle error
}
```

### Locking and Unlocking a Mutex

To protect a critical section of code with a mutex, use `mutexLock()` and `mutexUnlock()`.

```c
// Lock the mutex
mutexLock(&mutexInfo);

// Critical section

// Unlock the mutex
mutexUnlock(&mutexInfo);
```

### Closing a Mutex Handle

When you're done with the mutex, close its handle using `mutexCloseHandle()`.

```c
// Close the mutex handle
Bool success = mutexCloseHandle(&mutexInfo);
if (!success) {
    // Handle error
}
```

### Debugging Mutexes

It only works if `LEAN_DEBUG` is defined in `LeanTypes.h`

```c
// Print mutex Information
mutexDebug(&mutexInfo);
```

## Notes

- Always check the return values of the functions for errors.
- Ensure proper error handling is implemented in case of failures.
