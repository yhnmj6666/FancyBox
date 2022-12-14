#define CINTERFACE
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <commctrl.h>
#include <stdarg.h>

#include <stdio.h>
#include <time.h>

//#include "defs.h"
#include "common.hpp"
#include "FancyBox.hpp"

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "urlmon.lib")

//-------------------------------------------------------------------------
// Function declarations

#define __thiscall __fastcall
#define this _this
#define __usercall __fastcall

int __cdecl FancyBoxInitialize(HINSTANCE hInstance, int a2);
void __usercall sub_401120(int, int, HWND, int);
BOOL __usercall ToggleMaximizedWindow(int, HWND);
LRESULT __stdcall WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
ATOM __cdecl MyRegisterClass(HINSTANCE hInstance);
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
BOOL __cdecl FancyRegSetString(LPCSTR lpString2, LPCSTR lpValueName, LPCSTR);
void __cdecl j__free(void*);
int sub_411550();
int sub_411570();
void __cdecl sub_411590(); // idb
void __cdecl sub_4115A0(); // idb

//-------------------------------------------------------------------------
// Data declarations

int nCmdShow = 0; // idb
CHAR Buffer[100] ={}; // idb
HINSTANCE hInstance = NULL; // idb
char byte_416978[1024]; // weak
char byte_4181F0[1024]; // weak

//----- (00401020) --------------------------------------------------------
int __cdecl FancyBoxInitialize(HINSTANCE hInstance, int a2)
{
    int v2; // esi
    int SystemMetrics; // eax
    int result; // eax
    HWND v5; // esi
    CHAR Filename[512]; // [esp+Ch] [ebp-200h] BYREF

    InitCommonControls();
    ::hInstance = hInstance;
    v2 = (GetSystemMetrics(0) - 800) / 2;
    SystemMetrics = GetSystemMetrics(1);
    result = (int)CreateWindowExA(
        0,
        Buffer,
        "FcBox II",
        0xCF0000u,
        v2,
        (SystemMetrics - 600) / 2,
        800,
        600,
        0,
        0,
        hInstance,
        0);
    v5 = (HWND)result;
    if (result)
    {
        fancyBox.field_74 = 3;
        GetModuleFileNameA(hInstance, Filename, 0x200u);
        //FancyRegSetString("fcbox2", "runerpath", Filename);
        FancyBoxInitObjsys(&fancyBox, hInstance, v5);
        nCmdShow = a2;
        ShowWindow(v5, 0);
        SetTimer(v5, 0x3E8u, 0x64u, 0);
        UpdateWindow(v5);
        return 1;
    }
    return result;
}

//----- (00401120) --------------------------------------------------------
void __usercall sub_401120(int a1, int a2, HWND a3, int a4)
{
    LONG WindowLongA; // eax
    int v7; // esi

    WindowLongA = GetWindowLongA(a3, -16);
    v7 = a4 | WindowLongA & ~a2;
    if (WindowLongA != v7)
    {
        SetWindowLongA(a3, -16, v7);
        if (a1)
            SetWindowPos(a3, 0, 0, 0, 0, 0, a1 | 0x17);
    }
}

//----- (00401170) --------------------------------------------------------
BOOL __usercall ToggleMaximizedWindow(int a1, HWND a2)
{
    LONG WindowLongA; // eax
    LONG v3; // eax
    LONG v5; // eax
    LONG v6; // eax

    if (a1)
    {
        WindowLongA = GetWindowLongA(a2, -16);
        if (WindowLongA != (WindowLongA & 0xFF3FFFFF))
            SetWindowLongA(a2, -16, WindowLongA & 0xFF3FFFFF);
        v3 = GetWindowLongA(a2, -16);
        if (v3 != (v3 & 0xFFFBFFFF))
        {
            SetWindowLongA(a2, -16, v3 & 0xFFFBFFFF);
            SetWindowPos(a2, 0, 0, 0, 0, 0, 0x17u);
        }
        return ShowWindow(a2, 3);
    }
    else
    {
        v5 = GetWindowLongA(a2, -16);
        if (v5 != (v5 | 0xC00000))
            SetWindowLongA(a2, -16, v5 | 0xC00000);
        v6 = GetWindowLongA(a2, -16);
        if (v6 != (v6 | 0x40000))
            SetWindowLongA(a2, -16, v6 | 0x40000);
        return ShowWindow(a2, 9);
    }
}

//----- (00401210) --------------------------------------------------------
LRESULT __stdcall WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    LRESULT result; // eax
    LONG WindowLongA; // eax
    LONG v6; // eax
    char Buffer[100]; // [esp+8h] [ebp-64h] BYREF

    LoadStringA(hInstance, 0x6Au, Buffer, 100);
    if (Msg <= 0x14)
    {
        switch (Msg)
        {
        case 0x14u:
            if (!fancyBox.objsysReady)
                return DefWindowProcA(hWnd, 0x14u, wParam, lParam);
            return 0;
        case 2u:
            PostQuitMessage(0);
            return 0;
        case 5u:
            nullsub_1();
            return 0;
        case 6u:
            if (wParam)
            {
                FancyBoxNotifyObjsys(&fancyBox);
                return 0;
            }
            return 0;
        }
        return DefWindowProcA(hWnd, Msg, wParam, lParam);
    }
    if (Msg == 273)
    {
        if ((_WORD)wParam != 105)
            return DefWindowProcA(hWnd, 0x111u, wParam, lParam);
        DestroyWindow(hWnd);
        return 0;
    }
    if (Msg == 275)
    {
        ShowWindow(hWnd, nCmdShow);
        KillTimer(hWnd, 1000u);
        return 0;
    }
    if (Msg != 3024)
        return DefWindowProcA(hWnd, Msg, wParam, lParam);
    switch (wParam)
    {
    case 0u:
        ToggleMaximizedWindow(1, hWnd);
        result = 0;
        break;
    case 1u:
        ToggleMaximizedWindow(0, hWnd);
        result = 0;
        break;
    case 2u:
        WindowLongA = GetWindowLongA(hWnd, -16);
        if (WindowLongA != (WindowLongA & 0xFFFBFFFF))
            SetWindowLongA(hWnd, -16, WindowLongA & 0xFFFBFFFF);
        sub_401120(32, 0xC00000, hWnd, 0);
        result = 0;
        break;
    case 3u:
        v6 = GetWindowLongA(hWnd, -16);
        if (v6 != (v6 | 0x40000))
            SetWindowLongA(hWnd, -16, v6 | 0x40000);
        sub_401120(32, 0, hWnd, 0xC00000);
        result = 0;
        break;
    default:
        return 0;
    }
    return result;
}
// 401210: using guessed type CHAR Buffer[100];

//----- (00401440) --------------------------------------------------------
ATOM __cdecl MyRegisterClass(HINSTANCE hInstance)
{
    char* buffer; // eax
    WNDCLASSEXA v4; // [esp+8h] [ebp-30h] BYREF

    v4.cbSize = 48;
    v4.style = 3;
    v4.lpfnWndProc = WndProc;
    v4.cbClsExtra = 0;
    v4.cbWndExtra = 0;
    v4.hInstance = hInstance;
    if (fancyBox.strCommandI.len <= 0)
    {
    LABEL_8:
        v4.hIcon = LoadIconA(hInstance, (LPCSTR)0x6B);
        goto LABEL_9;
    }
    if (fancyBox.strCommandI.len < 1 || (buffer = fancyBox.strCommandI.buffer) == 0)
        buffer = *(char**)emptyString;
    v4.hIcon = LoadIconA(hInstance, buffer);
    if (!v4.hIcon)
        goto LABEL_8;
LABEL_9:
    v4.hCursor = LoadCursorA(0, (LPCSTR)0x7F00);
    v4.hbrBackground = (HBRUSH)6;
    v4.lpszMenuName = 0;
    v4.lpszClassName = Buffer;
    v4.hIconSm = LoadIconA(v4.hInstance, (LPCSTR)0x6C);
    return RegisterClassExA(&v4);
}

//----- (00401500) --------------------------------------------------------
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    int result; // eax
    struct tagMSG Msg; // [esp+0h] [ebp-1Ch] BYREF

    sub_411550();
    sub_411570();
    fancyBox.field_A8 = 1;
    if (*lpCmdLine)
        FancyBoxSaveCmdline(&fancyBox, lpCmdLine);
    LoadStringA(hInstance, 0x6Du, Buffer, 100);
    MyRegisterClass(hInstance);
    result = FancyBoxInitialize(hInstance, nShowCmd);
    if (result)
    {
        while (GetMessageA(&Msg, 0, 0, 0))
        {
            TranslateMessage(&Msg);
            DispatchMessageA(&Msg);
        }
        FancyBoxFreeObjsys(&fancyBox);
        return Msg.wParam;
    }
    return result;
}

//----- (00401780) --------------------------------------------------------
char* GetLastErrorCStr()
{
    DWORD LastError; // eax
    char* v1; // esi
    char* v2; // eax
    int v3; // edx
    char v4; // cl
    char* Buffer; // [esp+0h] [ebp-4h] BYREF

    LastError = GetLastError();
    if (FormatMessageA(0x1300u, 0, LastError, 0x400u, (LPSTR)&Buffer, 0, 0))// FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER
    {
        v1 = Buffer;
        v2 = Buffer;
        v3 = byte_416978 - Buffer;
        do
        {
            v4 = *v2;
            v2[v3] = *v2;
            ++v2;
        } while (v4);
        LocalFree(v1);
        return byte_416978;
    }
    else
    {
        byte_416978[0] = 0;
        return byte_416978;
    }
}

//----- (00401C80) --------------------------------------------------------
BOOL __cdecl FancyRegSetString(LPCSTR lpString2, LPCSTR lpValueName, LPCSTR a3)
{
    HKEY phkResult; // [esp+0h] [ebp-408h] BYREF
    DWORD dwDisposition; // [esp+4h] [ebp-404h] BYREF
    CHAR String1[1024]; // [esp+8h] [ebp-400h] BYREF

    lstrcpyA(String1, "SOFTWARE\\XXT\\");
    lstrcatA(String1, lpString2);
    RegCreateKeyExA(HKEY_LOCAL_MACHINE, String1, 0, 0, 0, 0x20006u, 0, &phkResult, &dwDisposition);
    lstrcpyA(String1, a3);
    return RegSetValueExA(phkResult, lpValueName, 0, 1u, (const BYTE*)String1, strlen(String1)) == 0;
}

//----- (00405B70) --------------------------------------------------------
char* FormatErrorMessage()
{
    DWORD LastError; // eax
    char* v1; // esi
    char* v2; // eax
    int v3; // edx
    char v4; // cl
    char* Buffer; // [esp+0h] [ebp-4h] BYREF

    LastError = GetLastError();
    if (FormatMessageA(0x1300u, 0, LastError, 0x400u, (LPSTR)&Buffer, 0, 0))
    {
        v1 = Buffer;
        v2 = Buffer;
        v3 = byte_4181F0 - Buffer;
        do
        {
            v4 = *v2;
            v2[v3] = *v2;
            ++v2;
        } while (v4);
        LocalFree(v1);
        return byte_4181F0;
    }
    else
    {
        byte_4181F0[0] = 0;
        return byte_4181F0;
    }
}

//----- (004087B7) --------------------------------------------------------
void __stdcall vector_destructor(char* a1, unsigned int a2, int a3, void(__thiscall* a4)(void*))
{
    char* i; // [esp+30h] [ebp+8h]

    for (i = &a1[a3 * a2]; --a3 >= 0; a4(i))
        i -= a2;
}
// 408803: conditional instruction was optimized away because %var_1C.4==1

//----- (00408817) --------------------------------------------------------
void __stdcall vector_constructor(
    char* a1,
    unsigned int a2,
    int a3,
    void(__thiscall* a4)(void*),
    void(__thiscall* a5)(void*))
{
    int i; // [esp+10h] [ebp-1Ch]

    for (i = 0; i < a3; ++i)
    {
        a4(a1);
        a1 += a2;
    }
}
// 408865: conditional instruction was optimized away because %var_20.4==1

//----- (00411550) --------------------------------------------------------
int sub_411550()
{
    FancyBoxCtor(&fancyBox);
    return atexit(sub_411590);
}

//----- (00411570) --------------------------------------------------------
int sub_411570()
{
    CacheStoreInitialize(&fancyBox.field_CE8);
    return atexit(sub_4115A0);
}

//----- (00411590) --------------------------------------------------------
void __cdecl sub_411590()
{
    FancyStrDtor(&fancyBox.updateMessage);
    FancyStrDtor(&fancyBox.strCommandI);
    FancyStrDtor(&fancyBox.strCommandC);
    FancyStrDtor(&fancyBox.strCommandSV);
    FancyStrDtor(&fancyBox.cmdLine);
    FancyStrDtor(&fancyBox.strCommandSystem);
    FancyStrDtor(&fancyBox.field_50);
    FancyStrDtor(&fancyBox.objsysDllPath);
    FancyStrDtor(&fancyBox.field_38);
    FancyStrDtor(&fancyBox.field_2C);
    FancyStrDtor(&fancyBox.strCommandRaw);
    FancyStrDtor(&fancyBox.strCommandDll);
}

//----- (004115A0) --------------------------------------------------------
void __cdecl sub_4115A0()
{
    FancyStrDtor(&fancyBox.field_CE8.strSystem);
    FancyStrDtor(&fancyBox.field_CE8.strFullPath);
    FancyStrDtor(&fancyBox.field_CE8.strDrive);
    FancyStrDtor(&fancyBox.field_CE8.strBufferUnused);
    FancyStrDtor(&fancyBox.field_CE8.strPath);
}

void nullsub_1()
{
    ;
}

void __thiscall nullsub_2(void* this, int a1, int a2)
{
    ;
}

void __cdecl j__free(void* a1)
{
    free(a1);
}

// nfuncs=384 queued=164 decompiled=164 lumina nreq=0 worse=0 better=0
// ALL OK, 164 function(s) have been successfully decompiled
