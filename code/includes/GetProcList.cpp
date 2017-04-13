#include "WinData.h"

list<PrInfo> GetProcList()
{
	list<PrInfo> Prlist;
	PrInfo tmp;
	HANDLE h;
	PROCESSENTRY32 p;
	int i = 0;

	p.dwSize = sizeof(p);
	h = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (h == INVALID_HANDLE_VALUE)
	{
		tmp.id = -1;
		return Prlist;
	}

	Process32First(h, &p);
	do
	{
		tmp.id = p.th32ProcessID;
		strcpy_s(tmp.name, p.szExeFile);
		//Место для вашей рекламы
		Prlist.push_back(tmp);
	} while (Process32Next(h, &p));
	CloseHandle(h);
	return Prlist;
}