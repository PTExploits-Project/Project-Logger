DWORD GetPid()
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(pe);

	if (Process32First(hSnap, &pe))
	{
		do
		{
			if (!strcmp(pe.szExeFile, "Game.exe"))
			{
				CloseHandle(hSnap);
				return pe.th32ProcessID;
			}
		} while (Process32Next(hSnap, &pe));
		CloseHandle(hSnap);
	}
	return 0;
}

DWORD GetpPid(char pName[])
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(pe);
	
	DWORD pPid = 0;
	
	if (Process32First(hSnap, &pe))
	{
		do
		{
			if (!strcmp(pe.szExeFile, pName))
				pPid = th32ProcessID;
		} while (Process32Next(hSnap, &pe));
		
		if (pPid != 0){
			pPid = pe.th32ParentProcessID;
			CloseHandle(hSnap);
		}
	}
	return pPid;
}

DWORD GetModule(int Pid)
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, Pid);
	MODULEENTRY32 me;
	me.dwSize = sizeof(me);

	if (Module32First(hSnap, &me))
	{
		do
		{
			if (!strcmp(me.szModule, "Game.exe"))
			{
				CloseHandle(hSnap);
				return (DWORD)me.modBaseAddr;
			}
		} while (Module32Next(hSnap, &me));
		CloseHandle(hSnap);
	}
	return 0;
}

DWORD AoBScan(char* Reference, int size)
{
	void* pData = 0;
	MEMORY_BASIC_INFORMATION mbi;

	int Addr_Start = 0;
	pData = malloc(0x7FFFFF);

	if (pData != 0)
	{
		while (true)
		{
			VirtualQueryEx(hProc, (void*)Addr_Start, &mbi, sizeof(mbi));

			if (mbi.RegionSize != size)
				Addr_Start += mbi.RegionSize;
			else
			{
				ReadProcessMemory(hProc, (void*)Addr_Start, pData, size, NULL);

				for (int i = 0; i < size - strlen(Reference); i++)
				{
					bool found = true;
					for (int j = 0; j < strlen(Reference); j++)
					{
						found &= Reference[j] == *(char*)(DWORD(pData) + i + j);
					}
					if (found)
						return Addr_Start + i;
				}
			}
		}
	}

	free(pData);
	return 0;
}
