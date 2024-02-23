#include "Lean.h"

int _tmain(int argc, TCHAR* argv[]) {
	LeanInit();

	KeyHandle keyHandle;
	ErrorCode createKeyCode = registryOpenKey(&keyHandle, _T("Teste123\\ff\\"));

	if (createKeyCode != ERROR_SUCCESS) {
		ErrorLog(_T("Error"));
		processExit(1);
	}

	KeyDataType dataType;
	
	TCHAR str[200];

	KeyDataSize dataSize;

	registryQueryValue(keyHandle, _T("codiso"), &dataType, (pKeyDataValue) str, &dataSize);

	_tprintf(_T("%s\n"), str);

	_tprintf(_T("Key Created Successfully\n"));
	processExit(0);
}