#include "WinData.h"

int GetProcMem(int id)
{
	PROCESS_MEMORY_COUNTERS mem;
	HANDLE hp;
	mem.cb = sizeof(mem);
	hp = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, id);
	if (hp == NULL)
	{
		return -(int)GetLastError();
	}
	GetProcessMemoryInfo(hp, &mem, sizeof(mem));
	CloseHandle(hp);
	return mem.WorkingSetSize;
}