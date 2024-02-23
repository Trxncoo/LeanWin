#include "process.h"

int _tmain(int argc, TCHAR* argv[]) {
	//leanWinInit();
	ProcessInfo pi;

	process_create(argv[1], &pi);

	return 0;
}
