#include "WinData.h"

char filt_str[MAX_PATH];
DWORD sort_flag;

void LsProcess::filter(CONST DWORD flags, char * filt_opt)
{
	strcpy(filt_str, filt_opt);
	if ((flags & 0xf00) == FILTER_USER)
	{
		Prlist.remove_if(pred);
	}
	sort_flag = flags;
	Prlist.sort(cmp);
	if (flags & 0x1)
		Prlist.reverse();
}

bool cmp(const PrInfo & a, const PrInfo & b)
{
	DWORD tmp = sort_flag & 0xf0;
	switch (tmp)
	{
	case 0x10:
		if (a.Memory < b.Memory)
			return true;
		break;
	case 0x20:
		if (a.CpuUsage < b.CpuUsage)
			return true;
		break;
	case 0x30:
		if (strcmp(a.name, b.name) < 0)
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