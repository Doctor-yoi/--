#include <string>
#include <comdef.h>
#include <Windows.h>

using namespace std;

bool startProcess(string executablePath) {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));

	_bstr_t _t(executablePath.c_str());
	LPTSTR cl = (LPTSTR)_t;

	if (CreateProcess(NULL, cl, NULL, NULL, false, 0, NULL, NULL, &si, &pi)) {
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		return true;
	}

	return false;
}