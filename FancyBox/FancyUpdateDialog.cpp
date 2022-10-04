#include "FancyUpdateDialog.hpp"

#include "common.hpp"

#include <commctrl.h>
#include <stdlib.h>

#define __thiscall __fastcall
#define this _this

FancyBaseDialogVtbl stru_412618 = {
    (void(__thiscall*)(FancyBaseDialog * _this)) &nullsub_1,
    &sub_405C70,
    &nullsub_2,
    &FancyBaseDialogRelease,
    (int(__fastcall*)(FancyBaseDialog * _this, int, int, int, int)) &sub_405AE0
}; // weak
FancyBaseDialogVtbl stru_41263C =
{
  (void(__fastcall*)(FancyBaseDialog * _this)) & FancyUpdateDialogInitAndShow,
  &sub_405C70,
  &nullsub_2,
  (FancyBaseDialog * (__fastcall*)(FancyBaseDialog * _this, char)) & FancyUpdateDialogDtor,
  (int(__fastcall*)(FancyBaseDialog*, int, int, int, int)) & FancyUpdateDialogOnMessage
}; // weak


//----- (00405BD0) --------------------------------------------------------
void __thiscall FancyUpdateDialogCreateInternal(FancyUpdateDialog* this, HINSTANCE hInstance, HWND hWndParent)
{
    unsigned __int16 v4; // ax
    HWND hDialog; // eax
    HLOCAL v6; // eax
    char* v7; // eax
    const DLGTEMPLATE* v8; // [esp-10h] [ebp-18h]

    v4 = this->field_14;
    this->hWndParent = hWndParent;
    if (v4)
    {
        hDialog = CreateDialogParamA(hInstance, (LPCSTR)v4, hWndParent, (DLGPROC)DialogFunc, 0);
    }
    else
    {
        v6 = sub_4059D0(this->field_4);
        this->field_8 = (int)v6;
        v8 = (const DLGTEMPLATE*)LocalLock(v6);
        hDialog = CreateDialogIndirectParamA(hInstance, v8, hWndParent, (DLGPROC)DialogFunc, 0);
    }
    this->hDialog = hDialog;
    if (hDialog)
    {
        SetWindowLongA(hDialog, -21, (LONG)this);
        ((void(__thiscall*)(FancyUpdateDialog*))this->__vftbl->InitialzeComponent)(this);
    }
    else
    {
        v7 = FormatErrorMessage();
        MessageBoxA(this->hWndParent, v7, "dlg create err!", 0);
    }
}

//----- (00405C70) --------------------------------------------------------
int __thiscall sub_405C70(FancyBaseDialog* this)
{
    int result; // eax

    result = 0;
    this->hDialog = 0;
    this->hWndParent = 0;
    return result;
}

//----- (00405C80) --------------------------------------------------------
BOOL __thiscall FancyBoxHideOrDeactiveWindow(FancyBaseDialog* this, int a2)
{
    if (a2)
        return ShowWindow(this->hDialog, 4);
    else
        return ShowWindow(this->hDialog, 0);
}

//----- (00405CB0) --------------------------------------------------------
void __thiscall FancyBaseDialogDtor(FancyBaseDialog* this)
{
    HWND hDialog; // eax

    hDialog = this->hDialog;
    this->__vftbl = &stru_412618;
    if (hDialog)
    {
        SetWindowLongA(hDialog, -21, 0);
        DestroyWindow(this->hDialog);
        this->hDialog = 0;
        this->hWndParent = 0;
    }
    if (this->field_8)
    {
        LocalUnlock((HLOCAL)this->field_8);
        LocalFree((HLOCAL)this->field_8);
        this->field_8 = 0;
    }
}
// 412618: using guessed type FancyBaseDialogVtbl stru_412618;

//----- (00405D10) --------------------------------------------------------
FancyBaseDialog* __thiscall FancyBaseDialogRelease(FancyBaseDialog* this, char a2)
{
    FancyBaseDialogDtor(this);
    if ((a2 & 1) != 0)
        free(this);
    return this;
}

//----- (00405D30) --------------------------------------------------------
void __thiscall FancyUpdateDialogCtor(FancyUpdateDialog* this)
{
    sub_405AB0(this);
    this->downloadingTextControl = 0;
    this->downloadProgressControl = 0;
    this->updateProgressControl = 0;
    this->field_24 = 0;
    this->__vftbl = &stru_41263C;
    LOWORD(this->field_14) = 135;
    this->width = 345;
    this->height = 230;
}
// 41263C: using guessed type FancyBaseDialogVtbl stru_41263C;

//----- (00405D70) --------------------------------------------------------
void __thiscall FancyUpdateDialogRelease(FancyUpdateDialog* this)
{
    this->__vftbl = &stru_41263C;
    FancyBaseDialogDtor(this);
}
// 41263C: using guessed type int (*off_41263C)();

//----- (00405D80) --------------------------------------------------------
int __thiscall FancyUpdateDialogOnMessage(
    FancyUpdateDialog* this,
    HWND hWnd,
    UINT Msg,
    WPARAM wParam,
    unsigned int lParam)
{
    int result; // eax

    if (Msg == WM_CLOSE)
    {
        this->field_24 = 1;
        return 0;
    }
    if (Msg != WM_COMMAND)
        return 0;
    result = 1;
    if (wParam == 1014)
        this->field_24 = 1;
    return result;
}

//----- (00405DC0) --------------------------------------------------------
void __thiscall FancyUpdateDialogInitAndShow(FancyUpdateDialog* this)
{
    int screenWidth; // ebx
    int screenHeight; // eax
    HWND hDialog; // edx
    LONG bottom; // ecx
    HWND DlgItem; // eax
    HWND v7; // eax
    HWND v8; // eax
    struct tagRECT Rect; // [esp+Ch] [ebp-10h] BYREF

    screenWidth = GetSystemMetrics(16);
    screenHeight = GetSystemMetrics(17);
    MoveWindow(
        this->hDialog,
        (screenWidth - this->width) / 2,
        (screenHeight - this->height) / 2,
        this->width,
        this->height,
        1);
    SetWindowPos(this->hDialog, 0, 0, 2, 1, 1, 3u);
    FancyBoxHideOrDeactiveWindow(this, this->field_28);
    UpdateWindow(this->hDialog);
    GetClientRect(this->hDialog, &Rect);
    hDialog = this->hDialog;
    bottom = Rect.bottom;
    this->width = Rect.right - Rect.left;
    this->height = bottom - Rect.top;
    DlgItem = GetDlgItem(hDialog, 1013);
    this->downloadingTextControl = DlgItem;
    SetWindowTextA(DlgItem, "Update...");
    v7 = GetDlgItem(this->hDialog, 1015);
    this->downloadProgressControl = v7;
    SendMessageA(v7, 0x401u, 0, 0x640000);
    SendMessageA(this->downloadProgressControl, 0x402u, 0x32u, 0);
    v8 = GetDlgItem(this->hDialog, 1012);
    this->updateProgressControl = v8;
    SendMessageA(v8, 0x401u, 0, 0x640000);
    SendMessageA(this->updateProgressControl, 0x402u, 0x32u, 0);
}

//----- (00405F00) --------------------------------------------------------
void __thiscall FancyUpdateDialogCreate(FancyUpdateDialog* this, HINSTANCE hInstance, HWND hWndParent, int a4)
{
    this->field_28 = a4;
    FancyUpdateDialogCreateInternal(this, hInstance, hWndParent);
}

//----- (00405F20) --------------------------------------------------------
BOOL __thiscall FancyBoxHideWindow(FancyBaseDialog* this)
{
    return FancyBoxHideOrDeactiveWindow(this, 0);
}

//----- (00405F30) --------------------------------------------------------
void __thiscall FancyUpdateDialogSetDownloadingText(FancyUpdateDialog* this, LPCSTR lpString, int a3)
{
    SetWindowTextA(this->downloadingTextControl, lpString);
    if (a3)
        SendMessageA(this->downloadProgressControl, 0x402u, 0, 0);
}

//----- (00405F70) --------------------------------------------------------
void __thiscall FancyUpdateDialogSetDownloadPercentage(FancyUpdateDialog* this, WPARAM wParam)
{
    SendMessageA(this->downloadProgressControl, PBM_SETPOS, wParam, 0);
}

//----- (00405F90) --------------------------------------------------------
void __thiscall FancyUpdateDialogSetUpdatePercentage(FancyUpdateDialog* this, WPARAM wParam)
{
    SendMessageA(this->updateProgressControl, PBM_SETPOS, wParam, 0);
}

//----- (00405FB0) --------------------------------------------------------
FancyUpdateDialog* __thiscall FancyUpdateDialogDtor(FancyUpdateDialog* this, char a2)
{
    FancyUpdateDialogRelease(this);
    if ((a2 & 1) != 0)
        free(this);
    return this;
}

//----- (00405AB0) --------------------------------------------------------
FancyBaseDialog* __thiscall sub_405AB0(FancyBaseDialog* this)
{
    FancyBaseDialog* result; // eax

    result = this;
    this->__vftbl = &stru_412618;
    this->hDialog = 0;
    this->hWndParent = 0;
    this->field_8 = 0;
    LOWORD(this->field_14) = 0;
    this->field_4 = 0x80CC0000;
    return result;
}
// 412618: using guessed type FancyBaseDialogVtbl stru_412618;

//----- (00405AF0) --------------------------------------------------------
BOOL __stdcall DialogFunc(HWND hWnd, UINT Msg, WPARAM wParam, unsigned int lParam)
{
    FancyUpdateDialog* v1; // ecx

    v1 = (FancyUpdateDialog*)GetWindowLongA(hWnd, -21);
    if (!v1)
        return DefWindowProcA(hWnd, Msg, wParam, lParam);
    if (Msg == 2)
    {
        v1->__vftbl->Release(v1);
        PostQuitMessage(0);
        return 0;
    }
    else if (Msg == 5)
    {
        ((void(__thiscall*)(FancyUpdateDialog*, _DWORD, unsigned int))v1->__vftbl->nullsub)(
            v1,
            (unsigned __int16)lParam,
            HIWORD(lParam));
        return 0;
    }
    else
    {
        return ((int(__thiscall*)(FancyUpdateDialog*, HWND, UINT, WPARAM, unsigned int))v1->__vftbl->OnMessage)(
            v1,
            hWnd,
            Msg,
            wParam,
            lParam);
    }
}

//----- (004059D0) --------------------------------------------------------
HLOCAL __cdecl sub_4059D0(DWORD a1)
{
    unsigned int v1; // ebp
    HLOCAL v2; // eax MAPDST
    DWORD* v4; // eax
    char* v6; // eax
    char* v7; // eax
    unsigned int v8; // [esp+Ch] [ebp-18h]

    v1 = 2 * wcslen(L"dlg") + 2;
    v8 = 2 * wcslen(L"ARIAL") + 2;
    v2 = LocalAlloc(0x42u, (v8 + v1 + 27) & 0xFFFFFFFC);
    if (!v2)
        return 0;
    v4 = (DWORD*)LocalLock(v2);
    if (!v4)
    {
        LocalFree(v2);
        return 0;
    }
    *v4 = a1;
    v4[1] = 0;
    v4[2] = 0;
    v4[3] = 0;
    *((_WORD*)v4 + 8) = 0;
    *((_WORD*)v4 + 9) = 0;
    v6 = (char*)v4 + 18;
    *(_WORD*)(v6 + 1) = 0;
    v6 += 4;
    qmemcpy(v6, L"dlg", v1);
    v7 = &v6[v1];
    *(_WORD*)v7 = 11;
    qmemcpy(v7 + 2, L"ARIAL", v8);
    LocalUnlock(v2);
    return v2;
}

//----- (00405AE0) --------------------------------------------------------
int __thiscall sub_405AE0(void* this, int a1, int a2, int a3, int a4)
{
    return 0;
}

