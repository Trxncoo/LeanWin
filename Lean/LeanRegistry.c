#include "LeanRegistry.h"

ErrorCode registryCreateKey(pKeyHandle keyHandle, pStr subKey) {
	ExitCode state;
	ErrorCode keyState = RegCreateKeyEx(HKEY_CURRENT_USER, subKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, keyHandle, &state);

	if (keyState != ERROR_SUCCESS) {
		return !ERROR_SUCCESS;
	}

	if (state == REG_OPENED_EXISTING_KEY) {
		registryCloseKey(keyHandle);
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

ErrorCode registrySetValue(KeyHandle keyHandle, pStr valueName, KeyDataType keyDataType, pKeyDataValue keyDataValue, KeyDataSize keyDataSize) {
	return RegSetValueEx(keyHandle, valueName, 0, keyDataType, keyDataValue, keyDataSize);
}

ErrorCode registryQueryValue(KeyHandle keyHandle, pStr valueName, pKeyDataType keyDataType, pKeyDataValue keyDataValue, pKeyDataSize keyDataSize) {
	return RegQueryValueEx(keyHandle, valueName, 0, keyDataType, keyDataValue, keyDataSize);
}

ErrorCode registryDeleteValue(KeyHandle keyHandle, pStr valueName) {
	return RegDeleteValue(keyHandle, valueName);
}

pStr registryBaseKey(pStr subKey) {
	pStr subString, keyBuffer;
	uInt length;

	subString = _tcsstr(subKey, _T("\\"));
	if (subString == NULL) {
		return !ERROR_SUCCESS;
	}

	length = subString - subKey;

	keyBuffer = (pStr)malloc((length + 1) * sizeof(TCHAR));
	if (keyBuffer == NULL) {
		return !ERROR_SUCCESS;
	}

	_tcsnccpy_s(keyBuffer, length + 1, subKey, length);
	keyBuffer[length] = _T('\0');

	return keyBuffer;
}