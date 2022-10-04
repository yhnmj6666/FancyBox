#pragma once

#include <Windows.h>
#include "FancyStr.hpp"

#define __thiscall __fastcall
#define this _this
#define __usercall __fastcall

/* 79 */
struct FancyBoxFile
{
	int bOpened;
	FancyStr Filename;
	HANDLE hFile;
};

void __thiscall FancyBoxFileInitialize(FancyBoxFile* this);
void __thiscall FancyBoxFileClose(FancyBoxFile* this);
int __thiscall FancyBoxFileRead(FancyBoxFile* this, LPVOID lpBuffer, int nNumberOfBytesToRead);
int __thiscall FancyBoxFileWrite(FancyBoxFile* this, LPCVOID lpBuffer, int nNumberOfBytesToWrite);
int __thiscall FancyBoxFileReadStr(FancyBoxFile* this, FancyStr* a2);
void __thiscall FancyBoxFileDtor(FancyBoxFile* this);
int __thiscall FancyBoxFileOpen(FancyBoxFile* this, char* a2, unsigned int a3);

void __cdecl FancyBoxChangeAndCreateDirectory(LPCSTR lpString2);
BOOL __cdecl Time_tToFileTime(time_t, LPFILETIME lpFileTime);
time_t __thiscall FileTimeToTime_t(FILETIME* lpFileTime);
BOOL __cdecl FancySetFileTime(LPCSTR lpFileName, time_t);
void __cdecl GetPathAndFilenameFromCstr(FancyStr*, FancyStr*, char*);

#undef __thiscall
#undef this