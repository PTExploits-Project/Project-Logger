#include "Main.h"

int main()
{
	srand(time(NULL));

	for (int i = 0; i < 8; i++)
		randstring[i] = randchar[rand() % (strlen(randchar) + 1)];

	SetConsoleTitle(randstring);

	while (true)
	{
		if (clock() - UpdateTime > 3000)
		{
			UpdateTime = clock();
			system("cls");

			printf("%s\n\n", sGameStatus.c_str());
			printf("%08X\n", AoBScan((char*)"\x56\x57\x8b\x7c\x24\x10", 0x4A8000));
		}

		Pid = GetPid();

		if (Pid > 0)
		{
			sGameStatus = "Game Status -> ID do processo pego com sucesso!";

			if (hProc == 0)
				hProc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_READ, false, Pid);
		}
		else
			sGameStatus = "Game Status -> Aguardando Priston Tale ser aberto";
	}

	return 0;
}