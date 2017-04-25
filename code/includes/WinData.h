#pragma once
#pragma comment(lib, "pdh.lib")
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <TlHelp32.h>
#include <WinBase.h>
#include <fileapi.h>
#include <psapi.h>
#include <TCHAR.h>
#include <Pdh.h>
#include <list>
#include <Winnt.h>
#include <Sddl.h>
#include <string.h>

using namespace std;

typedef struct ProcessInfo
{
	int id;
	char name[MAX_PATH] = "";
	char user[MAX_PATH] = "";
	double CpuUsage;
	int Memory;
} PrInfo;

class LsProcess
{
	private:
		int GetProcMem(int id);
		void GetProcUser(char * user, int id);
		void countCPU(double * proc, TCHAR * name, int id);
	public:
		int GetProcList();
		list<PrInfo> Prlist;
};


BOOL SetPrivilege(
	HANDLE hToken,          // access token handle
	LPCTSTR lpszPrivilege,  // name of privilege to enable/disable
	BOOL bEnablePrivilege   // to enable or disable privilege
);

BOOL EnableDebugPrivilages();
