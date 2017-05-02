#include "WinData.h"

char filt_str[MAX_PATH];
DWORD sort_flag;

int LsProcess::GetProcList(CONST DWORD flags, char * filt_opt)
{
	strcpy(filt_str, filt_opt);
	PrInfo tmp;
	HANDLE h;
	PROCESSENTRY32 p;
	int i = 0;
	p.dwSize = sizeof(p);
	initPDH();
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
		GetProcUser(tmp.user, tmp.id);
		Prlist.push_back(tmp);
		addtoquery(&(Prlist.back()).CpuUsage, tmp.name, tmp.id);
	} while (Process32Next(h, &p));
	CloseHandle(h);
	countCPU();
	filter(flags);
	return 0;
}

void LsProcess::filter(CONST DWORD flags)
{
	if (flags == FILTER_USER)
	{
		Prlist.remove_if(pred);
	}
	sort_flag = flags;
	Prlist.sort(cmp);
}

bool cmp(const PrInfo & a, const PrInfo & b)
{

	switch (sort_flag & 0xf0)
	{
	case 0x10:
		if ((a.Memory < b.Memory) ^ (sort_flag & 0xf))
			return true;
		break;
	case 0x20:
		if ((a.CpuUsage < b.CpuUsage) ^ (sort_flag & 0xf))
			return true;
		break;
	case 0x30:
		if ((strcmp(a.name, b.name) < 0) ^ (sort_flag & 0xf))
			return true;
		break;
	default:
		break;
	}
	return false;
}

bool pred(const PrInfo & a)
{
	if (strcmp(a.user, filt_str) == 0)
		return false;
	return true;
}