#include "WinData.h"

int LsProcess::GetProcMem(int id)
{
	PROCESS_MEMORY_COUNTERS_EX mem;
	HANDLE hp;
	mem.cb = sizeof(mem);
	hp = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, id);
	if (hp == NULL)
	{
		return -(int)GetLastError();
	}
	GetProcessMemoryInfo(hp, (PROCESS_MEMORY_COUNTERS *)&mem, sizeof(mem));
	CloseHandle(hp);
	return mem.PrivateUsage / 1024;
}