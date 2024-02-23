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

ErrorCode registryCloseKey(KeyHandle keyHandle) {
	return RegCloseKey(keyHandle);
}

ErrorCode registryOpenKey(pKeyHandle keyHandle, pStr subKey) {
	return RegOpenKeyEx(HKEY_CURRENT_USER, subKey, 0, KEY_ALL_ACCESS, keyHandle);
}

ErrorCode registryDeleteKey(pStr subKey) {
	return RegDeleteKey(HKEY_CURRENT_USER, subKey);
}

ErrorCode registrySetValue(KeyHandle keyHandle, pStr valueName, KeyDataType keyDataType, pKeyDataValue keyDataValue, KeyDataSize keyDataSize) {
	return RegSetValueEx(keyHandle, valueName, 0, keyDataType, keyDataValue, keyDataSize);
}

ErrorCode registryQueryValue(KeyHandle keyHandle, pStr valueName, pKeyDataType keyDataType, pKeyDataValue keyDataValue, pKeyDataSize keyDataSize) {
	return RegQueryValueEx(keyHandle, valueName, 0, keyDataType, keyDataValue, keyDataSize);
}