#define _CRT_SECURE_NO_WARNINGS
#include "WinData.h"
#include <stdio.h>
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "rus");
	LsProcess a;
	PrInfo t;
	//��� �� �����, ���� ��������� �� ��������� ������
	EnableDebugPrivilages();
	//
	
	printf("--------------------------------------------------------------------------------\n");
		a.GetProcList();
		while (!a.Prlist.empty())
		{
			t = a.Prlist.front();
			printf("UserName: %-15s %6i %-25s %3.5f %7iKB\n", t.user, t.id, t.name, t.CpuUsage, t.Memory);
			a.Prlist.pop_front();
		}
	
	system("pause");
	return 0;
}
