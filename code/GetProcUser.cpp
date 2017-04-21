#include "WinData.h"

void LsProcess::GetProcUser(char * user, int id)
{
	HANDLE h, t;
	TOKEN_USER tu;
	int n;
	h = OpenProcess();
	OpenProcessToken(h, TOKEN_ALL_ACCESS, &t);
	GetTokenInformation(t, TokenUser, &tu, sizeof(tu), (PDWORD)&n);
}