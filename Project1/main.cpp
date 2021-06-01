#include <Windows.h>
#include <iostream>


/*
* 
sw33tLie's Find Jack
Author:
sw33tLie

Language:
C/C++

Upload:
10:12 PM 03/23/2019

Platform
Windows

Difficulty:
2.0

Quality:
4.0

Description

I lost my friend Jack...help me to find him!

*/


//.text:0040165D call ds:??6?$basic_ostream@DU?$char_traits@D@std@@@std@@QAEAAV01@P6AAAV01@AAV01@@Z@Z ; std::basic_ostream<char,std::char_traits<char>>::operator<<(std::basic_ostream<char,std::char_traits<char>> & (*)(std::basic_ostream<char,std::char_traits<char>> &))
//.text:00401663 call sub_401580 // <- replace 
//.text:00401668 mov  ecx, ds:?cin@std@@3V?$basic_istream@DU?$char_traits@D@std@@@1@A ; std::basic_istream<char,std::char_traits<char>> std::cin



int __cdecl main()
{
	//0x004015B0 entry addr valid func
	HWND hwnd = FindWindowA(NULL, "Find Jack.exe");

	if (!hwnd)
	{
		printf("FindWindow is failed");
		return EXIT_FAILURE;
	}

	DWORD pID = 0;
	GetWindowThreadProcessId(hwnd, &pID);
	if (!pID)
	{
		printf("GetWindowThreadProcessId is failed");
		return EXIT_FAILURE;
	}

	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
	if (!hProc)
	{
		printf("OpenProcess is failed: 0x%X", GetLastError());
		return EXIT_FAILURE;
	}

	DWORD patch[] = { 0xE8, 0x48, 0xFF, 0xFF, 0xFF }; //jmp to 0x0x004015B0

	if (!WriteProcessMemory(hProc, (void*)0x00401663, patch, sizeof(patch), NULL))
	{
		printf("WriteProcessMemory is failed: 0x%X", GetLastError());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}