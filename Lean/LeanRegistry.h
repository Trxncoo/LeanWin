#pragma once

#include "LeanTypes.h"

typedef struct RegistryData RegistryData;
typedef struct RegistryData* pRegistryData;

struct RegistryData {
	KeyDataType keyDataType;
	pVoid keyDataValue;
	KeyDataSize keyDataSize;
};

Void registrySetDataType(pRegistryData registryData, KeyDataType keyDataType);

Void registrySetDataSize(pRegistryData registryData, KeyDataSize keyDataSize);

Void registrySetDataValue(pRegistryData registryData, pVoid keyDataValue);

Void registryFill(pRegistryData registryData, pVoid keyDataValue, KeyDataType keyDataType, KeyDataSize keyDataSize);

ErrorCode registryCreateKey(pKeyHandle keyHandle, pStr subKey);

ErrorCode registryDeleteKey(pStr subKey);

ErrorCode registryDeleteKeyTree(pStr subKey);

ErrorCode registryOpenKey(pKeyHandle keyHandle, pStr subKey);

ErrorCode registryCloseKey(KeyHandle keyHandle);

ErrorCode registrySetValue(KeyHandle keyHandle, pStr valueName, pRegistryData registryData);

ErrorCode registryQueryValue(KeyHandle keyHandle, pStr valueName, pRegistryData registryData);

ErrorCode registryDeleteValue(KeyHandle keyHandle, pStr valueName);

pStr registryBaseKey(pStr subKey);