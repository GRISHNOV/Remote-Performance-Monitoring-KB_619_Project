#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <WinBase.h>
#include <fileapi.h>
#include <psapi.h>
#include <TCHAR.h>
#include <Pdh.h>
#include <list>
#include <Winnt.h>


using namespace std;

typedef struct ProcessInfo
{
	int id;
	char name[MAX_PATH];
	char user[MAX_PATH];
	float CpuUsage;
	int Memory;
} PrInfo;

class LsProcess
{
	private:
		int GetProcMem(int id);
		void GetProcUser(char * user, int id);
		void countCPU();
	public:
		int GetProcList();
		list<PrInfo> Prlist;
};