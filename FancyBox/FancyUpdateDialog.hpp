#pragma once
#include <Windows.h>	

#define __thiscall __fastcall
#define this _this
#define __usercall __fastcall

struct FancyBaseDialog;

/* 238 */
struct FancyBaseDialogVtbl
{
	void(__thiscall* InitialzeComponent)(FancyBaseDialog* this);
	int(__thiscall* Release)(FancyBaseDialog* this);
	void* nullsub;
	FancyBaseDialog* (__thiscall* field_C)(FancyBaseDialog* this, char);
	int(__thiscall* OnMessage)(FancyBaseDialog* this, int, int, int, int);
};

/* 69 */
struct FancyBaseDialog
{
	FancyBaseDialogVtbl* __vftbl;
	int field_4;
	int field_8;
	HWND hDialog;
	HWND hWndParent;
	int field_14;
};

/* 70 */
struct FancyUpdateDialog : FancyBaseDialog
{
	HWND downloadingTextControl;
	HWND downloadProgressControl;
	HWND updateProgressControl;
	int field_24;
	int field_28;
	int width;
	int height;
};

void __thiscall FancyUpdateDialogCreateInternal(FancyUpdateDialog* this, HINSTANCE hInstance, HWND hWndParent);
int __thiscall sub_405C70(FancyBaseDialog* this);
BOOL __thiscall FancyBoxHideOrDeactiveWindow(FancyBaseDialog* this, int a2);
void __thiscall FancyBaseDialogDtor(FancyBaseDialog* this);
FancyBaseDialog* __thiscall FancyBaseDialogRelease(FancyBaseDialog* this, char);
void __thiscall FancyUpdateDialogCtor(FancyUpdateDialog* this);
void __thiscall FancyUpdateDialogRelease(FancyUpdateDialog* this);
int __thiscall FancyUpdateDialogOnMessage(FancyUpdateDialog* this, HWND hWnd, UINT Msg, WPARAM wParam, unsigned int lParam);
void __thiscall FancyUpdateDialogInitAndShow(FancyUpdateDialog* this);
void __thiscall FancyUpdateDialogCreate(FancyUpdateDialog* this, HINSTANCE hInstance, HWND hWndParent, int);
BOOL __thiscall FancyBoxHideWindow(FancyBaseDialog* this);
void __thiscall FancyUpdateDialogSetDownloadingText(FancyUpdateDialog* this, LPCSTR lpString, int a3);
void __thiscall FancyUpdateDialogSetDownloadPercentage(FancyUpdateDialog* this, WPARAM wParam);
void __thiscall FancyUpdateDialogSetUpdatePercentage(FancyUpdateDialog* this, WPARAM wParam);
FancyUpdateDialog* __thiscall FancyUpdateDialogDtor(FancyUpdateDialog* this, char);
FancyBaseDialog* __thiscall sub_405AB0(FancyBaseDialog* this);

BOOL __stdcall DialogFunc(HWND hWnd, UINT Msg, WPARAM wParam, unsigned int lParam);
HLOCAL __cdecl sub_4059D0(DWORD a1);
int __thiscall sub_405AE0(void*, int, int, int, int);
