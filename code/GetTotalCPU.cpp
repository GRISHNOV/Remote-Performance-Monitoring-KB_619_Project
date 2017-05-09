#include "WinData.h"

double GetTotalCPU()
{
	PDH_HQUERY hq;
	PDH_COUNTER_PATH_ELEMENTS pc;
	PDH_HCOUNTER hc;
	DWORD bufsize = PDH_MAX_COUNTER_PATH;
	TCHAR buf[PDH_MAX_COUNTER_PATH];
	PDH_FMT_COUNTERVALUE val;

	PdhOpenQuery(NULL, 0, &hq);
	pc.szCounterName = "% Processor Time";
	pc.szObjectName = "Processor";
	pc.szInstanceName = "_Total";
	pc.szMachineName = NULL;
	pc.szParentInstance = NULL;
	pc.dwInstanceIndex = 0;

	PdhMakeCounterPath(&pc, buf, &bufsize, 0);
	PdhAddEnglishCounter(hq, buf, 0, &hc);

	PdhCollectQueryData(hq);
	Sleep(1000);
	PdhCollectQueryData(hq);

	PdhGetFormattedCounterValue(hc, PDH_FMT_DOUBLE, NULL, &val);

	PdhCloseQuery(hq);

	return val.doubleValue;
}