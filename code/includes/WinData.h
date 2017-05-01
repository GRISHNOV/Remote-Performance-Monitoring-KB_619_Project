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
	void addtoquery(double * proc, CONST TCHAR * name, int id);
	PDH_HQUERY hq;
	typedef struct CountersList
	{
		PDH_HCOUNTER hc;
		double *c;
	} pdhc;
	list<pdhc> cl;
	void initPDH();
	int GetProcMem(int id);
	void GetProcUser(char * user, int id);
	void countCPU();
public:
	int GetProcList();
	list<PrInfo> Prlist;
};


//Это не нужно, если запускать от системной учетки
BOOL SetPrivilege(
	HANDLE hToken,          // access token handle
	LPCTSTR lpszPrivilege,  // name of privilege to enable/disable
	BOOL bEnablePrivilege   // to enable or disable privilege
);//

  //Это не нужно, если запускать от системной учетки
BOOL EnableDebugPrivilages();
//