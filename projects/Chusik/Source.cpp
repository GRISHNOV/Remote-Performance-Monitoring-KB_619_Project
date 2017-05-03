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
	char str[] = "cd система";
	
	printf("--------------------------------------------------------------------------------\n");
		a.GetProcList();
		a.filter(ConvStrToFl(str), str);
		while (!a.Prlist.empty())
		{
			t = a.Prlist.front();
			printf("UserName: %-15s %6i %-25s %3.1f%% %7iKB\n", t.user, t.id, t.name, t.CpuUsage, t.Memory);
			a.Prlist.pop_front();
		}
	
	system("pause");
	return 0;
}

DWORD ConvStrToFl(char * str)
{
	char stmp[MAX_PATH] = "", t;
	BOOL fl = FALSE;
	DWORD tmp = 0;
	int i = 0;
	while ((str[i] > 'a') && (str[i] < 'z'))
	{
		switch (str[i])
		{
		case 'c':
			tmp = tmp | SORT_BY_CPU;
			break;
		case 'm':
			tmp = tmp | SORT_BY_MEM;
			break;
		case 'n':
			tmp = tmp | SORT_BY_NAME;
			break;
		case 'u':
			tmp = tmp | SORT_UP;
			break;
		case 'd':
			tmp = tmp | SORT_DOWN;
			break;
		case 'f':
			tmp = tmp | FILTER_USER;
			fl = true;
			break;
		default:
			break;
		}
		i++;
	}
	if (fl)
	{
		sscanf(str, "%s%s", stmp, stmp);
		strcpy(str, stmp);
	}
	return tmp;
}