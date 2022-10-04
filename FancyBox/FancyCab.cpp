#define _CRT_SECURE_NO_WARNINGS

#include "FancyCab.hpp"
#include "common.hpp"

#include <stdlib.h>

#define __thiscall __fastcall
#define this _this

FancyBoxFileContent* dword_4181CC;
FancyBoxFileContent* dword_4181D0;
HFDI(__cdecl* MyFDICreate)(PFNALLOC pfnalloc, PFNFREE pfnfree, PFNOPEN pfnopen, PFNREAD pfnread, PFNWRITE pfnwrite, PFNCLOSE pfnclose, PFNSEEK pfnseek, int cpuType, PERF perf);
BOOL(__cdecl* MyFDIIsCabinet)(HFDI hfdi, INT_PTR hf, PFDICABINETINFO pfdici);
BOOL(__cdecl* MyFDICopy)(HFDI hfdi, LPSTR pszCabinet, LPSTR pszCabPath, int flags, PFNFDINOTIFY pfnfdin, PFNFDIDECRYPT pfnfdid, void* pvUser); // idb
int(__cdecl* MyFDIDestroy)(HFDI); // weak
HMODULE hLibModule; // idb
FancyCab* dword_4181E8;

FancyCab* (__thiscall* off_4125F4)(FancyCab* this, char a2) = &FancyCabDtor2; // weak

//----- (00405320) --------------------------------------------------------
FancyBoxFileContent* __cdecl pfnopen(const char* pszFile)
{
    FancyBoxFileContent* result; // eax

    if (strcmp(pszFile, "cab"))
        return 0;
    result = dword_4181CC;
    dword_4181CC->readSize = 0;
    return result;
}

//----- (00405350) --------------------------------------------------------
UINT __cdecl pfnread(FancyBoxFileContent* hf, void* pv, UINT cb)
{
    if (hf)
        return pfnreadInternal(hf, pv, cb);
    else
        return 0;
}

//----- (00405370) --------------------------------------------------------
UINT __cdecl pfnwrite(INT_PTR hf, void* pv, UINT cb)
{
    return pfnwriteInternal(dword_4181D0, pv, cb);
}

//----- (00405390) --------------------------------------------------------
int __cdecl pfnclose()
{
    return 0;
}

//----- (004053A0) --------------------------------------------------------
int __cdecl pfnseek(FancyBoxFileContent* hf, int dist, int seektype)
{
    if (hf)
        return pfnseekInternal(hf, dist, seektype);
    else
        return 0;
}

//----- (004053C0) --------------------------------------------------------
HFDI __cdecl FDISafeCreate(
    PFNALLOC pfnalloc,
    PFNFREE pfnfree,
    PFNOPEN pfnopen,
    PFNREAD pfnread,
    PFNWRITE pfnwrite,
    PFNCLOSE pfnclose,
    PFNSEEK pfnseek,
    int cpuType,
    PERF perf)
{
    HFDI result; // eax
    BOOL(__cdecl * v1)(HFDI); // eax
    HFDI v11; // esi

    result = LoadLibraryA("CABINET");
    hLibModule = (HMODULE)result;
    if (result)
    {
        MyFDICreate = (HFDI(__cdecl*)(PFNALLOC, PFNFREE, PFNOPEN, PFNREAD, PFNWRITE, PFNCLOSE, PFNSEEK, int, PERF))GetProcAddress((HMODULE)result, "FDICreate");
        MyFDICopy = (BOOL(__cdecl*)(HFDI, LPSTR, LPSTR, int, PFNFDINOTIFY, PFNFDIDECRYPT, void*))GetProcAddress(
            hLibModule,
            "FDICopy");
        MyFDIIsCabinet = (BOOL(__cdecl*)(HFDI, INT_PTR, PFDICABINETINFO))GetProcAddress(hLibModule, "FDIIsCabinet");
        v1 = (BOOL(__cdecl*)(HFDI))GetProcAddress(hLibModule, "FDIDestroy");
        MyFDIDestroy = (int(__cdecl*)(HFDI))v1;
        if (MyFDICreate && MyFDICopy && MyFDIIsCabinet && v1)
        {
            v11 = MyFDICreate(pfnalloc, pfnfree, pfnopen, pfnread, pfnwrite, pfnclose, pfnseek, cpuType, perf);
            if (!v11)
                FreeLibrary(hLibModule);
            return v11;
        }
        else
        {
            FreeLibrary(hLibModule);
            return 0;
        }
    }
    return result;
}
// 4181E0: using guessed type int (__cdecl *FDIDestroy)(_DWORD);

//----- (004054A0) --------------------------------------------------------
void __thiscall FDISafeDestroy(void* this)
{
    if (MyFDIDestroy)
    {
        if (MyFDIDestroy(this) == 1)
            FreeLibrary(hLibModule);
    }
}
// 4181E0: using guessed type int (__cdecl *FDIDestroy)(_DWORD);

//----- (004054D0) --------------------------------------------------------
FancyCab* __thiscall FancyCabCtor(FancyCab* this)
{
    this->__vftbl = (int)&off_4125F4;
    memset(this->field_C, 0, sizeof(this->field_C));
    memset(this->field_10C, 0, sizeof(this->field_10C));
    memset(this->field_20C, 0, sizeof(this->field_20C));
    this->hFDI = 0;
    this->cabSize = 0;
    this->folders = 0;
    this->files = 0;
    this->filenames = 0;
    this->filenameSize = 0;
    this->field_30C = 1;
    this->field_310 = 1;
    return this;
}
// 4125F4: using guessed type int (__thiscall *off_4125F4)(void *, char);

//----- (00405540) --------------------------------------------------------
void __thiscall FancyCabFree(FancyCab* this)
{
    int v2; // edi
    char** filenames; // [esp-4h] [ebp-10h]

    if (this->filenames)
    {
        v2 = 0;
        if (this->files)
        {
            do
            {
                if (this->filenames[v2])
                    free(this->filenames[v2]);
                this->filenames[v2++] = 0;
            } while (v2 < (unsigned __int16)this->files);
        }
        filenames = this->filenames;
        this->files = 0;
        free(filenames);
        this->filenames = 0;
        this->filenameSize = 0;
    }
    if (this->hFDI)
    {
        if (!MyFDIDestroy || MyFDIDestroy(this->hFDI) != 1)
        {
            this->hFDI = 0;
            return;
        }
        FreeLibrary(hLibModule);
    }
    this->hFDI = 0;
    if (this != (FancyCab*)-12)
        memset(this->field_C, 0, sizeof(this->field_C));
    this->cabSize = 0;
    this->folders = 0;
    this->files = 0;
    dword_4181E8 = 0;
}
// 4181E0: using guessed type int (__cdecl *FDIDestroy)(_DWORD);

//----- (00405610) --------------------------------------------------------
void __thiscall pfnfdinotifyCopyFileName(FancyCab* this, const char* a2)
{
    unsigned __int16 files; // ax

    if (a2)
    {
        if (*a2)
        {
            files = this->files;
            if (files)
            {
                if (this->filenameSize < files)
                {
                    this->filenames[this->filenameSize] = (char*)operator new(0x100u);
                    strcpy(this->filenames[this->filenameSize++], a2);
                }
            }
        }
    }
}

//----- (00405680) --------------------------------------------------------
FancyBoxFileContent* __cdecl pfnfdinotifyCopyFile(FDINOTIFICATION* a1)
{
    if (!dword_4181E8)
        return 0;
    if (!dword_4181E8->field_310)
        return dword_4181D0;
    pfnfdinotifyCopyFileName(dword_4181E8, a1->psz1);
    return 0;
}
// 4181D0: using guessed type int dword_4181D0;

//----- (004056C0) --------------------------------------------------------
INT_PTR __cdecl pfnfdinotify(int fdint, PFDINOTIFICATION pfdin)
{
    INT_PTR result; // eax

    switch (fdint)
    {
    case fdintCOPY_FILE:
        result = (INT_PTR)pfnfdinotifyCopyFile(pfdin);
        break;
    case fdintCLOSE_FILE_INFO:
        result = 1;
        break;
    default:
        result = 0;
        break;
    }
    return result;
}

//----- (00405700) --------------------------------------------------------
void __thiscall FancyCabDtor(FancyCab* this)
{
    this->__vftbl = (int)&off_4125F4;
    FancyCabFree(this);
    dword_4181E8 = 0;
}
// 4125F4: using guessed type int (__thiscall *off_4125F4)(void *, char);

//----- (00405720) --------------------------------------------------------
int __thiscall FancyCabExtract(FancyCab* this, int a2)
{
    char* v3; // ebx
    void* v4; // esi
    char* v5; // eax
    char* v6; // ecx
    char v7; // dl
    int v8; // esi
    char v10[7]; // [esp+1h] [ebp-20Bh]
    HFDI hFDI; // [esp+8h] [ebp-204h]
    char v12[256]; // [esp+Ch] [ebp-200h] BYREF
    char v13[256]; // [esp+10Ch] [ebp-100h] BYREF

    v3 = this->field_C;
    if (this == (FancyCab*)-12 || !*v3 || this == (FancyCab*)-268 || !this->field_10C[0])
        return 0;
    hFDI = this->hFDI;
    v4 = hFDI;
    if (!hFDI)
        return 0;
    this->field_310 = a2;
    v5 = strrchr(this->field_C, '\\');
    if (v5)
    {
        v6 = v5 + 1;
        do
        {
            v7 = *v6;
            v6[v13 - (v5 + 1)] = *v6;
            ++v6;
        } while (v7);
        v8 = v5 - (char*)this;
        strncpy(v12, v3, v5 - (char*)this - 11);
        v10[v8] = 0;
        v4 = hFDI;
    }
    else
    {
        strcpy(v13, v3);
        v12[0] = 0;
    }
    if (!MyFDICopy || !MyFDICopy(v4, v13, v12, 0, (PFNFDINOTIFY)pfnfdinotify, 0, 0))
    {
        FDISafeDestroy(v4);
        return 0;
    }
    return 1;
}
// 405720: using guessed type char var_20B[7];

//----- (00405840) --------------------------------------------------------
FancyCab* __thiscall FancyCabDtor2(FancyCab* this, char a2)
{
    this->__vftbl = (int)&off_4125F4;
    FancyCabFree(this);
    dword_4181E8 = 0;
    if ((a2 & 1) != 0)
        free(this);
    return this;
}
// 4125F4: using guessed type int (__thiscall *off_4125F4)(void *, char);

//----- (00405870) --------------------------------------------------------
int __thiscall FancyCabInitialize(FancyCab* this, FancyBoxFileContent* a2, FancyBoxFileContent* a3)
{
    HFDI hFDI; // edi
    int erfOper; // edx
    BOOL fError; // ecx
    unsigned __int16 cFiles; // ax
    bool v9; // zf
    int cbCabinet; // edx
    char** v11; // eax
    unsigned int v12; // edx
    ERF perf; // [esp+8h] [ebp-24h] BYREF
    FDICABINETINFO pfdici; // [esp+14h] [ebp-18h] BYREF
    static ERF stru_4181C0;

    dword_4181CC = a2;
    dword_4181D0 = a3;
    if (!a2 || !a3)
        return 0;
    if (this->hFDI)
        FancyCabFree(this);
    dword_4181E8 = this;
    hFDI = FDISafeCreate(
        (PFNALLOC)(malloc),
        (PFNFREE)(free),
        (PFNOPEN)pfnopen,
        (PFNREAD)pfnread,
        pfnwrite,
        (PFNCLOSE)pfnclose,
        (PFNSEEK)pfnseek,
        1,
        &perf);
    if (!hFDI)
        return 0;
    if (!MyFDIIsCabinet || !MyFDIIsCabinet(hFDI, (INT_PTR)a2, &pfdici))
    {
        FDISafeDestroy(hFDI);
        return 0;
    }
    erfOper = perf.erfOper;
    fError = perf.fError;
    stru_4181C0.erfType = perf.erfType;
    this->folders = pfdici.cFolders;
    cFiles = pfdici.cFiles;
    v9 = pfdici.cFiles == 0;
    stru_4181C0.erfOper = erfOper;
    cbCabinet = pfdici.cbCabinet;
    this->hFDI = hFDI;
    stru_4181C0.fError = fError;
    *(_DWORD*)this->field_C = 'bac';
    this->cabSize = cbCabinet;
    this->files = cFiles;
    if (!v9)
    {
        v11 = (char**)operator new(4 * cFiles);
        v12 = 4 * (unsigned __int16)this->files;
        this->filenames = v11;
        memset(v11, 0, v12);
    }
    strcpy(this->field_10C, "c:\\temp\\");
    FancyCabExtract(this, 1);
    return 1;
}

