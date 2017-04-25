#include "WinData.h"

void LsProcess::GetProcUser(char * user, int id)
{
	HANDLE h, t;
	PTOKEN_USER tu = NULL;
	SID_NAME_USE trash;
	int n;
	char tmpstr[260] = "";
	h = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, id);
	if (h == NULL)
	{
		strcpy(user, "UNKNOWN");
		return;
	}
	if (!OpenProcessToken(h, TOKEN_QUERY, &t))
	{
		strcpy(user, "TokenERR");
		return;
	}
	GetTokenInformation(t, TokenUser, tu, 0, (PDWORD)&n);
	tu = (PTOKEN_USER)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, n);
	GetTokenInformation(t, TokenUser, tu, n, (PDWORD)&n);
	n = 260;
	LookupAccountSid(NULL, tu->User.Sid, user, (LPDWORD)&n, tmpstr, (LPDWORD)&n, &trash);
	CloseHandle(t);
	CloseHandle(h);
}