#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <WinBase.h>
#include <fileapi.h>
#include <psapi.h>
#include <TCHAR.h>
#include <Pdh.h>
#include <list>

using namespace std;

typedef struct ProcessInfo
{
	int id;
	char name[MAX_PATH];
	char user[MAX_PATH];
	float CpuUsage;
	int Memory;
} PrInfo;

list<PrInfo> GetProcList();