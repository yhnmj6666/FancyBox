#pragma once
#include "FancyBoxFileContent.hpp"

#include <fdi.h>

#define __thiscall __fastcall
#define this _this
#define __usercall __fastcall

struct FancyCab
{
	int __vftbl;
	__int16 files;
	__int16 folders;
	int cabSize;
	char field_C[256];
	char field_10C[256];
	char field_20C[256];
	int field_30C;
	int field_310;
	HFDI hFDI;
	char** filenames;
	int filenameSize;
};

FancyBoxFileContent* __cdecl pfnopen(const char* pszFile);
UINT __cdecl pfnwrite(INT_PTR hf, void* pv, UINT cb); // idb
int __cdecl pfnclose();
int __cdecl pfnseek(FancyBoxFileContent* hf, int dist, int seektype);
void __thiscall FDISafeDestroy(void* this);
FancyCab* __thiscall FancyCabCtor(FancyCab* this);
void __thiscall FancyCabFree(FancyCab* this);
void __thiscall pfnfdinotifyCopyFileName(FancyCab* this, const char* a2);
FancyBoxFileContent* __cdecl pfnfdinotifyCopyFile(FDINOTIFICATION* a1);
INT_PTR __cdecl pfnfdinotify(int fdint, PFDINOTIFICATION pfdin);
void __thiscall FancyCabDtor(FancyCab* this);
int __thiscall FancyCabExtract(FancyCab* this, int a2);
FancyCab* __thiscall FancyCabDtor2(FancyCab* this, char);
int __thiscall FancyCabInitialize(FancyCab* this, FancyBoxFileContent* a2, FancyBoxFileContent* a3);
