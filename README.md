# Mutexes

For named mutexes, fill mutexInfo.name with a name 
```c
Bool mutexCreate(pMutexInfo mutexInfo);
```

Ex:
```c
  MutexInfo mutexInfo;
  pStr name[MAX_PATH] = _T("Chipi");
  mutexSetName(&mutexInfo, name); 
  mutexCreate(&mutexInfo);
```
