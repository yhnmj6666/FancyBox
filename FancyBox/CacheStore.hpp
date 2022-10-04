#pragma once
#include "FancyStr.hpp"

#include <Windows.h>

#define __thiscall __fastcall
#define this _this
#define __usercall __fastcall

/* 68 */
struct CacheStore
{
	FancyStr strPath;
	FancyStr strBufferUnused;
	FancyStr strDrive;
	FancyStr strFullPath;
	FancyStr strSystem;
};

CacheStore* __thiscall CacheStoreInitialize(CacheStore* this);
void __thiscall EnsureCache(CacheStore* this, const char* a2);

// Done
void EnsureDirectory(LPCSTR);
BOOL __stdcall TestWriteToPath(char*);
void __stdcall RemoveEmptyDirectoryRecursively(LPCSTR);

#undef __thiscall
#undef this
