#include "LeanTime.h"

Void timeSetRelative(pTimeInfo timeInfo, Dword seconds) {
	timeInfo->QuadPart = -(seconds * 10000000LL);
}