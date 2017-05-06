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
#define SORT_BY_MEM 0x10
#define SORT_BY_CPU 0x20
#define SORT_BY_NAME 0x30
#define SORT_UP 0x00
#define SORT_DOWN 0x01
#define FILTER_USER 0x100

using namespace std;

typedef struct ProcessInfo
{
	int id;
	char name[MAX_PATH] = "";
	char user[MAX_PATH] = "";
	double CpuUsage;
	int Memory;
} PrInfo;

bool pred(const PrInfo& a);
bool cmp(const PrInfo& a, const PrInfo& b);

class LsProcess
{
private:
	//char filt_str[MAX_PATH];
	//bool pred(const PrInfo& a);
	//DWORD sort_flag;
	//bool cmp(const PrInfo& a, const PrInfo& b);
	void addtoquery(double * proc, CONST TCHAR * name, int id);
	PDH_HQUERY hq;
	typedef struct CountersList
	{
		PDH_HCOUNTER hc;
		double *c;
		int id;
	} pdhc;
	list<pdhc> cl;
	void initPDH();
	int GetProcMem(int id);
	void GetProcUser(char * user, int id);
	void countCPU();
public:
	void filter(CONST DWORD flags, char * filt_opt);
	int GetProcList();
	list<PrInfo> Prlist;
};

DWORD ConvStrToFl(char * str);

//��� �� �����, ���� ��������� �� ��������� ������
BOOL SetPrivilege(
	HANDLE hToken,          // access token handle
	LPCTSTR lpszPrivilege,  // name of privilege to enable/disable
	BOOL bEnablePrivilege   // to enable or disable privilege
);//

  //��� �� �����, ���� ��������� �� ��������� ������
BOOL EnableDebugPrivilages();
//