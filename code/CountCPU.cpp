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

	pc.szCounterName = "% Processor Time";
	pc.szObjectName = "Process";
	pc.szInstanceName = tname;
	pc.szMachineName = NULL;
	pc.szParentInstance = NULL;
	pc.dwInstanceIndex = 0;

	PdhMakeCounterPath(&pc, buf, &bufsize, 0);
	PdhAddEnglishCounter(hq, buf, 0, &hc);

	pdhc tmp;
	tmp.hc = hc;
	tmp.c = proc;

	cl.push_front(tmp);
}

/*
BOOL
WINAPI
EnumProcesses_PerfData(
	IN LPCTSTR pszMachineName,
	IN PFNENUMPROC pfnEnumProc,
	IN LPARAM lParam
)
{
	PDH_STATUS Status;
	WCHAR szCounterPath[1024];

	// формируем путь к счетчику производительностиDWORD bufsize = PDH_MAX_COUNTER_PATH;
	PDH_COUNTER_PATH_ELEMENTS pc;
	DWORD bs1 = PDH_MAX_COUNTER_PATH, bs2 = PDH_MAX_COUNTER_PATH;
	TCHAR buf1[PDH_MAX_COUNTER_PATH], buf2[PDH_MAX_COUNTER_PATH];
	TCHAR *t, tname[MAX_PATH];

	

	pc.szCounterName = "ID Process";
	pc.szObjectName = "Process";
	pc.szInstanceName = "*";
	pc.szMachineName = NULL;
	pc.szParentInstance = NULL;
	pc.dwInstanceIndex = 0;

	PdhMakeCounterPath(&pc, buf1, &bs1, 0);

	pc.szCounterName = "% Processor Time";
	pc.szObjectName = "Process";
	pc.szInstanceName = "*";
	pc.szMachineName = NULL;
	pc.szParentInstance = NULL;
	pc.dwInstanceIndex = 0;

	PdhMakeCounterPath(&pc, buf2, &bs2, 0);

	HQUERY hQuery;
	HCOUNTER hC1, hC2;

	// открываем запрос
	Status = PdhOpenQuery(NULL, 0, &hQuery);
	if (Status != ERROR_SUCCESS)
	{
		return SetLastError(Status), FALSE;
	}

	// добавл€ем счетчик к запросу
	Status = PdhAddCounter(hQuery, buf1, 0, &hC1);
	if (Status != ERROR_SUCCESS)
	{
		PdhCloseQuery(hQuery);
		return SetLastError(Status), FALSE;
	}

	Status = PdhAddCounter(hQuery, buf2, 0, &hC2);
	if (Status != ERROR_SUCCESS)
	{
		PdhCloseQuery(hQuery);
		return SetLastError(Status), FALSE;
	}

	// получаем текущие значени€ счетчика
	Status = PdhCollectQueryData(hQuery);
	if (Status != ERROR_SUCCESS)
	{
		PdhCloseQuery(hQuery);
		return SetLastError(Status), FALSE;
	}

	DWORD cbSize1 = 0, cbSize2 = 0;
	DWORD cItems1 = 0, cItems2 = 0;
	HANDLE hHeap = GetProcessHeap();

	// определ€ем необходимый размер буфера
	Status = PdhGetRawCounterArray(hC1, &cbSize1, &cItems1, NULL);
	if (Status != ERROR_SUCCESS)
	{
		PdhCloseQuery(hQuery);
		return SetLastError(Status), FALSE;
	}
	Status = PdhGetRawCounterArray(hC2, &cbSize2, &cItems2, NULL);
	if (Status != ERROR_SUCCESS)
	{
		PdhCloseQuery(hQuery);
		return SetLastError(Status), FALSE;
	}

	// выдел€ем пам€ть дл€ буфера
	PDH_RAW_COUNTER_ITEM * pRaw1 =
		(PDH_RAW_COUNTER_ITEM *)HeapAlloc(hHeap, 0, cbSize1);
	PDH_RAW_COUNTER_ITEM * pRaw2 =
		(PDH_RAW_COUNTER_ITEM *)HeapAlloc(hHeap, 0, cbSize1);
	if (pRaw1 == NULL || pRaw2 == NULL)
	{
		PdhCloseQuery(hQuery);
		return SetLastError(ERROR_NOT_ENOUGH_MEMORY), FALSE;
	}

	// получаем значени€ счетчика
	Status = PdhGetRawCounterArray(hC1, &cbSize1, &cItems1, pRaw1);
	if (Status != ERROR_SUCCESS)
	{
		HeapFree(hHeap, 0, pRaw1);
		return SetLastError(Status), FALSE;
	}
	Status = PdhGetRawCounterArray(hC2, &cbSize2, &cItems2, pRaw2);

	// закрываем запрос
	PdhCloseQuery(hQuery);

	if (Status != ERROR_SUCCESS)
	{
		HeapFree(hHeap, 0, pRaw2);
		return SetLastError(Status), FALSE;
	}

	// перечисл€ем все экземпл€ры
	for (DWORD i = 0; i < cItems1; i++)
	{
		DWORD dwProcessId = (DWORD)pRaw[i].RawValue.FirstValue;
		LPCTSTR pszProcessName;

#ifdef UNICODE
		pszProcessName = pRaw[i].szName;
#else
		CHAR szProcessName[MAX_PATH];
		WideCharToMultiByte(CP_ACP, 0, pRaw[i].szName, -1,
			szProcessName, MAX_PATH, NULL, NULL);
		pszProcessName = szProcessName;
#endif

		// исключаем экземпл€р с именем _Total
		if (dwProcessId == 0 && lstrcmp(pszProcessName, _T("_Total")) == 0)
			continue;

		if (!pfnEnumProc(dwProcessId, pszProcessName, lParam))
			break;
	}

	HeapFree(hHeap, 0, pRaw);
	FreeLibrary(hPdh);

	return TRUE;
}*/