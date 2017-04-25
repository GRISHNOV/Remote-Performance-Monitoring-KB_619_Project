#include "WinData.h"

void LsProcess::countCPU(double * proc, TCHAR * name, int id)
{
	PDH_COUNTER_PATH_ELEMENTS pc;
	PDH_FMT_COUNTERVALUE val;
	PDH_HQUERY hq;
	PDH_HCOUNTER hc;
	DWORD bufsize = PDH_MAX_COUNTER_PATH;
	TCHAR buf[PDH_MAX_COUNTER_PATH];
	PdhOpenQuery(NULL, 0, &hq);

	pc.szCounterName = "% загруженности процессора";
	pc.szObjectName = "Процесс";
	pc.szInstanceName = name;
	pc.szMachineName = NULL;
	pc.szParentInstance = NULL;
	pc.dwInstanceIndex = id;

	PdhMakeCounterPath(&pc, buf, &bufsize, 0);

	PdhAddCounter(hq, buf, 0, &hc);
	PdhCollectQueryData(hq);
	PdhGetFormattedCounterValue(hc, PDH_FMT_DOUBLE, &bufsize, &val);
	*proc = val.doubleValue;
	PdhCloseQuery(hq);
}