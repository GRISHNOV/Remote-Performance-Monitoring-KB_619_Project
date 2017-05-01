#include "WinData.h"

void LsProcess::countCPU()
{
	PdhCollectQueryData(hq);
	Sleep(1000);
	PDH_FMT_COUNTERVALUE val;
	pdhc tmp;
	PdhCollectQueryData(hq);
	while (!cl.empty())
	{
		tmp = cl.front();
		cl.pop_front();

		PdhGetFormattedCounterValue(tmp.hc, PDH_FMT_DOUBLE, NULL, &val);
		*(tmp.c) = val.doubleValue;
	}

	PdhCloseQuery(hq);
}

void LsProcess::initPDH()
{
	PdhOpenQuery(NULL, 0, &hq);
}

void LsProcess::addtoquery(double * proc,CONST TCHAR * name, int id)
{
	PDH_COUNTER_PATH_ELEMENTS pc;
	PDH_HCOUNTER hc;
	DWORD bufsize = PDH_MAX_COUNTER_PATH;
	TCHAR buf[PDH_MAX_COUNTER_PATH];
	TCHAR *t, tname[MAX_PATH];

	_tcscpy(tname, name);
	if ((t = _tcsstr(tname, ".exe")) != NULL)
		*((int *)t) = 0;

	pc.szCounterName = "% загруженности процессора";
	pc.szObjectName = "Процесс";
	pc.szInstanceName = tname;
	pc.szMachineName = NULL;
	pc.szParentInstance = NULL;
	pc.dwInstanceIndex = 0;

	PdhMakeCounterPath(&pc, buf, &bufsize, 0);
	PdhAddCounter(hq, buf, 0, &hc);

	pdhc tmp;
	tmp.hc = hc;
	tmp.c = proc;

	cl.push_front(tmp);
}