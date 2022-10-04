#pragma once

#include <Windows.h>

#include "FancyStr.hpp"
#include "FancyUpdateDialog.hpp"
#include "CacheStore.hpp"

#define __thiscall __fastcall
#define this _this
#define __usercall __fastcall

/* 66 */
struct FancyBox
{
	HMODULE hObjsys;
	int(__cdecl* fStdInitFancyBox)(HMODULE hModule, HWND hWnd, int, int);
	void(__cdecl* fStdCmdFancyBox)(int a1, char* a2);
	HINSTANCE hInstance;
	HWND hWnd;
	FancyStr strCommandDll;
	FancyStr strCommandRaw;
	FancyStr field_2C;
	FancyStr field_38;
	FancyStr objsysDllPath;
	FancyStr field_50;
	FancyStr strCommandSystem;
	int field_68;
	int objsysReady;
	int field_70;
	int field_74;
	FancyStr cmdLine;
	FancyStr strCommandSV;
	FancyStr strCommandC;
	FancyStr strCommandI;
	char field_A8;
	int field_AC[382];
	int field_6A4;
	int field_6A8;
	int field_6AC[383];
	int field_CA8;
	int field_CAC[3];
	int field_CB8[3];
	FancyStr updateMessage;
	int field_CD0;
	int field_CD4;
	int field_CD8;
	int field_CDC;
	int field_CE0;
	FancyUpdateDialog* updateDialog;
	CacheStore field_CE8;
};

HWND __thiscall GetMostParentWindow(FancyBox* this);
HMODULE __thiscall FancyBoxFreeObjsys(FancyBox* this);
void __thiscall FancyBoxSaveCmdline(FancyBox* this, char*);
void __thiscall FancyBoxNotifyObjsys(FancyBox* this);
char* __thiscall sub_402090(FancyBox* this, unsigned int a2);
char* __thiscall sub_4021D0(FancyBox* this, unsigned int a2);
void __thiscall FancyBoxCtor(FancyBox* this);
void __thiscall sub_402900(FancyBox* this, FancyStr* a2);
int __thiscall FancyBoxUpdateSystem(FancyBox* this, HWND hWnd);
int __thiscall InitializeCache(FancyBox* this); // idb
void __thiscall FancyBoxInitObjsys(FancyBox* this, HINSTANCE, HWND);

extern FancyBox fancyBox;

BYTE* __cdecl FancyRegReadString(LPCSTR lpString2, LPCSTR lpValueName, BYTE* lpDefault);
BOOL __cdecl CompareTime(LPCSTR lpFileName, int a2, int a3, FILETIME* a4);
int FancyBoxHideAndErrorMessageBox(FancyBaseDialog* a1, HWND hWnd, LPCSTR a3, ...);
BOOL __cdecl VerifyFileSizeAndTime(LPCSTR lpFileName, unsigned int filetime, int filesize);
int __usercall sub_401D30(CHAR*, FancyStr*, char*);
time_t __cdecl GetLastWriteTime(LPCSTR lpFileName);
void __cdecl UpdateProgress(int, unsigned int);
BOOL __cdecl sub_405230(char*, char*, int, int, void(__cdecl*)(int, unsigned int));
int FancyBoxErrorMessageBox(FancyBox* a1, LPCSTR a2, ...);

#undef __thiscall
#undef this