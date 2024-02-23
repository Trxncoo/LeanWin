#pragma once

#include "LeanTypes.h"

// if key exists, returns NULL and doesn't open it
ErrorCode registryCreateKey(pKeyHandle keyHandle, pStr subKey);

ErrorCode registryOpenKey(pKeyHandle keyHandle, pStr subKey);

ErrorCode registryCloseKey(KeyHandle keyHandle);

ErrorCode registryDeleteKey(pStr subKey);

ErrorCode registrySetValue(KeyHandle keyHandle, pStr valueName, KeyDataType keyDataType, pKeyDataValue keyDataValue, KeyDataSize keyDataSize);

ErrorCode registryQueryValue(KeyHandle keyHandle, pStr valueName, pKeyDataType keyDataType, pKeyDataValue keyDataValue, pKeyDataSize keyDataSize);
