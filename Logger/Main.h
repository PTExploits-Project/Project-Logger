#include <Windows.h>
#include <TlHelp32.h>
#include <time.h>
#include <stdio.h>
#include <string>

using namespace std;

char randstring[50];
char randchar[] = {
"0123456789"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz" };

HANDLE hProc = 0;
int UpdateTime = clock(), Pid;
string sGameStatus;

#include "Func.h"