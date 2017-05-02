#include "WinData.h"

char filt_str[MAX_PATH];
DWORD sort_flag;

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
/*
template <class T> class cmp : public std::unary_function<T, bool>
{
public:
	bool LsProcess::cmp(const PrInfo & a, const PrInfo & b)
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
};

template <class T> class pred : public std::unary_function<T, bool>
{
public:
	bool LsProcess::pred(const PrInfo & a)
	{
		if (strcmp(a.user, filt_str) == 0)
			return false;
		return true;
	}
};*/