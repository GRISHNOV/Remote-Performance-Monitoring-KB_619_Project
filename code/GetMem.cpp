#include "WinData.h"

DWORD GetMem(DWORD flag)
{
	MEMORYSTATUSEX s;
	s.dwLength = sizeof(s);
	GlobalMemoryStatusEx(&s);
	switch (flag)
	{
	case TOTAL_MEM:
		return s.ullTotalPhys / 1024;
	case AVAIL_MEM:
		return s.ullAvailPhys / 1024;
	case USED_MEM:
		return (s.ullTotalPhys - s.ullAvailPhys) / 1024;
	case MEM_LOAD_P:
		return s.dwMemoryLoad;
	default:
		break;
	}
	return 0x48f07a;
}