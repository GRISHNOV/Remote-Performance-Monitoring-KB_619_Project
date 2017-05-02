#define _CRT_SECURE_NO_WARNINGS
#include "WinData.h"
#include <stdio.h>
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "rus");
	LsProcess a;
	PrInfo t;
	//Это не нужно, если запускать от системной учетки
	EnableDebugPrivilages();
	//
	
	printf("--------------------------------------------------------------------------------\n");
		a.GetProcList(SORT_BY_CPU | SORT_UP | FILTER_USER, "Ivan");
		while (!a.Prlist.empty())
		{
			t = a.Prlist.front();
			printf("UserName: %-15s %6i %-25s %3.1f%% %7iKB\n", t.user, t.id, t.name, t.CpuUsage, t.Memory);
			a.Prlist.pop_front();
		}
	
	system("pause");
	return 0;
}
