#include "LeanRegistry.h"

Void registrySetDataType(pRegistryData registryData, KeyDataType keyDataType) {
	registryData->keyDataType = keyDataType;
}

Void registrySetDataSize(pRegistryData registryData, KeyDataSize keyDataSize) {
	registryData->keyDataSize = keyDataSize;
}

Void registrySetDataValue(pRegistryData registryData, pVoid keyDataValue) {
	registryData->keyDataValue = keyDataValue;
}

Void registryFill(pRegistryData registryData, pVoid keyDataValue, KeyDataType keyDataType, KeyDataSize keyDataSize) {
	registrySetDataValue(registryData, keyDataValue);
	registrySetDataType(registryData, keyDataType);
	registrySetDataSize(registryData, keyDataSize);
}

ErrorCode registryCreateKey(pKeyHandle keyHandle, pStr subKey) {
	ExitCode state;
	ErrorCode keyState = RegCreateKeyEx(HKEY_CURRENT_USER, subKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, keyHandle, &state);

	if (keyState != ERROR_SUCCESS) {
		return !ERROR_SUCCESS;
	}

	if (state == REG_OPENED_EXISTING_KEY) {
		registryCloseKey(*keyHandle);
		return !ERROR_SUCCESS;
	}

	return keyState;
}

ErrorCode registryDeleteKey(pStr subKey) {	
	return RegDeleteKey(HKEY_CURRENT_USER, subKey);
}

ErrorCode registryDeleteKeyTree(pStr subKey) {
	ErrorCode deleteCode;
	pStr keyBuffer = registryBaseKey(subKey);

	deleteCode = RegDeleteTree(HKEY_CURRENT_USER, keyBuffer);

	free(keyBuffer);

	return deleteCode;
}


ErrorCode registryOpenKey(pKeyHandle keyHandle, pStr subKey) {
	return RegOpenKeyEx(HKEY_CURRENT_USER, subKey, 0, KEY_ALL_ACCESS, keyHandle);
}

ErrorCode registryCloseKey(KeyHandle keyHandle) {
	return RegCloseKey(keyHandle);
}

ErrorCode registrySetValue(KeyHandle keyHandle, pStr valueName, pRegistryData registryData) {
	return RegSetValueEx(keyHandle, valueName, 0, registryData->keyDataType, registryData->keyDataValue, registryData->keyDataSize);
}

ErrorCode registryQueryValue(KeyHandle keyHandle, pStr valueName, pRegistryData registryData) {
	KeyDataType dataType;
	KeyDataSize dataSize = 0;
	ErrorCode queryResult;
	
	queryResult = RegQueryValueEx(keyHandle, valueName, 0, &dataType, NULL, &dataSize);
	if (queryResult != ERROR_SUCCESS) {
		return queryResult;
	}

	if (dataType != REG_SZ) {
		queryResult = RegQueryValueEx(keyHandle, valueName, 0, &dataType, (pKeyDataValue) &registryData->keyDataValue, &dataSize);
		if (queryResult != ERROR_SUCCESS) {
			return queryResult;
		}
	}
	else {
		registryData->keyDataValue = malloc(dataSize);
		if (registryData->keyDataValue == NULL) {
			return ERROR_NOT_ENOUGH_MEMORY;
		}

		queryResult = RegQueryValueEx(keyHandle, valueName, 0, &dataType, (pKeyDataValue)registryData->keyDataValue, &dataSize);
		if (queryResult != ERROR_SUCCESS) {
			free(registryData->keyDataValue);
			return queryResult;
		}
	}

	registryData->keyDataSize = dataSize;
	registryData->keyDataType = dataType;

	return ERROR_SUCCESS;
}

ErrorCode registryDeleteValue(KeyHandle keyHandle, pStr valueName) {
	return RegDeleteValue(keyHandle, valueName);
}

pStr registryBaseKey(pStr subKey) {
	pStr subString, keyBuffer;
	uInt length;

	subString = _tcsstr(subKey, _T("\\"));
	if (subString == NULL) {
		return NULL;
	}

	length = (uInt)(subString - subKey);

	keyBuffer = (pStr)malloc((length + 1) * sizeof(TCHAR));
	if (keyBuffer == NULL) {
		return NULL;
	}

	_tcsnccpy_s(keyBuffer, length + 1, subKey, length);
	keyBuffer[length] = _T('\0');

	return keyBuffer;
}