#define _CRT_SECURE_NO_WARNINGS
#include "WinData.h"
#include <stdio.h>
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "rus");
	LsProcess a;
	PrInfo t;
	EnableDebugPrivilages();
	
		printf("--------------------------------------------------------------------------------\n");
		a.GetProcList();
		while (!a.Prlist.empty())
		{
			t = a.Prlist.front();
			printf("UserName: %-15s %6i %-25s %3.1f %7iKB\n", t.user, t.id, t.name, t.CpuUsage, t.Memory);
			//printf("UserName: %-25s\n", t.user);
			a.Prlist.pop_front();
		}
	
	system("pause");
	return 0;
}

/*int main()
{
	HANDLE h = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	
	PROCESSENTRY32 p;
	Process32First(h, &p);
	Process32Next(h, &p);

	PROCESS_MEMORY_COUNTERS mem;
	HANDLE hp = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, GetCurrentProcessId());
	
	GetProcessMemoryInfo(hp, &mem, sizeof(PROCESS_MEMORY_COUNTERS));
	

	printf("%u - name: %s --memory: %i\n", p.th32ProcessID, p.szExeFile, mem.WorkingSetSize / 1024);

	CloseHandle(hp);
	CloseHandle(h);
	
	system("pause");
	return 0;
	}*/