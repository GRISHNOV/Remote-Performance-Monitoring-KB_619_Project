#include "WinData.h"

int LsProcess::GetProcList()
{
	PrInfo tmp;
	HANDLE h;
	PROCESSENTRY32 p;
	int i = 0;
	p.dwSize = sizeof(p);
	h = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (h == INVALID_HANDLE_VALUE)
	{
		return -1;
	}

	Process32First(h, &p);
	do
	{
		tmp.id = p.th32ProcessID;
		strcpy_s(tmp.name, p.szExeFile);
		tmp.Memory = GetProcMem(tmp.id);
		//
		//
		Prlist.push_back(tmp);
	} while (Process32Next(h, &p));
	CloseHandle(h);
	return 0;
}