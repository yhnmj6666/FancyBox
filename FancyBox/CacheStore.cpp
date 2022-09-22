#define _CRT_SECURE_NO_WARNINGS

#include "CacheStore.hpp"
#include "common.hpp"

#include <stdio.h>

//----- (004022A0) --------------------------------------------------------
CacheStore* __thiscall CacheStoreInitialize(CacheStore* this)
{
    FancyStrCtor(&this->strPath);
    FancyStrCtor(&this->strBufferUnused);
    FancyStrCtor(&this->strDrive);
    FancyStrCtor(&this->strFullPath);
    FancyStrCtor(&this->strSystem);
    FancyStrFromCStr(&this->strPath, "Program Files\\FancyBoxII Games\\");
    FancyStrFromCStr(&this->strBufferUnused, "fcbox2");
    return this;
}

//----- (00403C00) --------------------------------------------------------
void __thiscall EnsureCache(CacheStore* this, const char* a2)
{
    char* buffer; // eax
    char i; // bl
    char v5; // al
    char* v6; // eax
    char* v7; // edx
    char* v8; // ecx
    char* v9; // eax
    char* v10; // eax
    DWORD FileAttributesA; // eax
    char* v12; // eax
    char v13; // al
    char* v14; // eax
    char* v15; // eax
    char* v16; // eax
    DWORD v17; // eax
    char v18; // al
    char* v19; // edx
    char* v20; // ecx
    char* v21; // eax
    char* v22; // eax
    char* v23; // edx
    char* v24; // ecx
    char* v25; // eax
    char v26; // [esp+13h] [ebp-41h]
    DWORD SectorsPerCluster; // [esp+14h] [ebp-40h] BYREF
    DWORD BytesPerSector; // [esp+18h] [ebp-3Ch] BYREF
    DWORD NumberOfFreeClusters; // [esp+1Ch] [ebp-38h] BYREF
    DWORD TotalNumberOfClusters; // [esp+20h] [ebp-34h] BYREF
    FancyStr lpFileName; // [esp+24h] [ebp-30h] BYREF
    FancyStr lpRootPathName; // [esp+30h] [ebp-24h] BYREF
    FancyStr v33; // [esp+3Ch] [ebp-18h] BYREF
    int v34; // [esp+50h] [ebp-4h]

    FancyStrCtor(&lpRootPathName);
    v34 = 0;
    FancyStrCtor(&lpFileName);
    LOBYTE(v34) = 1;
    FancyStrCtor(&v33);
    LOBYTE(v34) = 2;
    v26 = 0;
    if (a2 && strlen(a2) > 2)
    {
        buffer = (char*)a2;
    }
    else if (this->strBufferUnused.len < 1 || (buffer = this->strBufferUnused.buffer) == 0)
    {
        buffer = emptyString;
    }
    FancyStrFromCStr(&v33, buffer);
    for (i = 'C'; i <= 'Z'; ++i)
    {
        if (i == 'C')
        {
            v5 = 'D';
        }
        else
        {
            v5 = 'C';
            if (i != 'D')
                v5 = i;
        }
        FancyStrSetVAStr(&lpRootPathName, "%c:\\", v5);
        if (lpRootPathName.len < 1 || (v6 = lpRootPathName.buffer) == 0)
            v6 = emptyString;
        if (GetDriveTypeA(v6) == 3)
        {
            if (v33.len < 1 || (v7 = v33.buffer) == 0)
                v7 = emptyString;
            if (this->strPath.len < 1 || (v8 = this->strPath.buffer) == 0)
                v8 = emptyString;
            if (lpRootPathName.len < 1 || (v9 = lpRootPathName.buffer) == 0)
                v9 = emptyString;
            FancyStrSetVAStr(&lpFileName, "%s%s%s\\", v9, v8, v7);
            if (lpFileName.len < 1 || (v10 = lpFileName.buffer) == 0)
                v10 = emptyString;
            FileAttributesA = GetFileAttributesA(v10);
            if (FileAttributesA == -1 || (FileAttributesA & 0x10) == 0)
            {
                if (lpRootPathName.len < 1 || (v14 = lpRootPathName.buffer) == 0)
                    v14 = emptyString;
                if (GetDiskFreeSpaceA(v14, &SectorsPerCluster, &BytesPerSector, &NumberOfFreeClusters, &TotalNumberOfClusters)
                    && !v26
                    && (unsigned int)(unsigned __int64)((double)SectorsPerCluster
                        * (double)BytesPerSector
                        * (double)NumberOfFreeClusters
                        * 0.00000095367431640625) >= 0xC8)// Free Space >=200MB
                {
                    if (lpFileName.len < 1 || (v15 = lpFileName.buffer) == 0)
                        v15 = emptyString;
                    EnsureDirectory(v15);
                    if (lpFileName.len < 1 || (v16 = lpFileName.buffer) == 0)
                        v16 = emptyString;
                    v17 = GetFileAttributesA(v16);
                    if (v17 != -1 && (v17 & 0x10) != 0)
                        v26 = i;
                }
            }
            else
            {
                if (lpFileName.len < 1 || (v12 = lpFileName.buffer) == 0)
                    v12 = emptyString;
                if (TestWriteToPath(v12))
                {
                    FancyStrSet(&this->strDrive, (const char**)&lpRootPathName.buffer);
                    FancyStrSet(&this->strFullPath, (const char**)&lpFileName.buffer);
                    FancyStrSet(&this->strSystem, (const char**)&v33.buffer);
                    v13 = v26;
                    if (v26)
                    {
                        if (v26 == 'C')
                        {
                            v13 = 'D';
                        }
                        else if (v26 == 'D')
                        {
                            v13 = 'C';
                        }
                        FancyStrSetVAStr(&lpRootPathName, "%c:\\", v13);
                        if (v33.len < 1 || (v19 = v33.buffer) == 0)
                            v19 = emptyString;
                        if (this->strPath.len < 1 || (v20 = this->strPath.buffer) == 0)
                            v20 = emptyString;
                        if (lpRootPathName.len < 1 || (v21 = lpRootPathName.buffer) == 0)
                            v21 = emptyString;
                        FancyStrSetVAStr(&lpFileName, "%s%s%s\\", v21, v20, v19);
                        if (lpFileName.len < 1 || (v22 = lpFileName.buffer) == 0)
                            v22 = emptyString;
                        RemoveEmptyDirectoryRecursively(v22);
                    }
                    goto LABEL_54;
                }
            }
        }
    }
    v18 = v26;
    switch (v26)
    {
    case 0:
    LABEL_54:
        LOBYTE(v34) = 1;
        FancyStrDtor(&v33);
        LOBYTE(v34) = 0;
        FancyStrDtor(&lpFileName);
        v34 = -1;
        FancyStrDtor(&lpRootPathName);
        return;
    case 67:
        v18 = 68;
        break;
    case 68:
        v18 = 67;
        break;
    }
    FancyStrSetVAStr(&lpRootPathName, "%c:\\", v18);
    if (v33.len < 1 || (v23 = v33.buffer) == 0)
        v23 = emptyString;
    if (this->strPath.len < 1 || (v24 = this->strPath.buffer) == 0)
        v24 = emptyString;
    if (lpRootPathName.len < 1 || (v25 = lpRootPathName.buffer) == 0)
        v25 = emptyString;
    FancyStrSetVAStr(&lpFileName, "%s%s%s\\", v25, v24, v23);
    FancyStrSet(&this->strDrive, (const char**)&lpRootPathName.buffer);
    FancyStrSet(&this->strFullPath, (const char**)&lpFileName.buffer);
    FancyStrSet(&this->strSystem, (const char**)&v33.buffer);
    LOBYTE(v34) = 1;
    FancyStrDtor(&v33);
    LOBYTE(v34) = 0;
    FancyStrDtor(&lpFileName);
    v34 = -1;
    FancyStrDtor(&lpRootPathName);
}

//----- (00402330) --------------------------------------------------------
void __stdcall EnsureDirectory(LPCSTR lpString2)
{
    signed int v1; // eax
    int v2; // edi
    signed int i; // ecx
    char v4; // cl
    char* v5; // eax
    void(__stdcall * fSetCurrentDirectoryA)(LPCSTR); // ebp
    FancyStr* v7; // esi
    FancyStr* v8; // esi
    int v9; // edi
    char* v10; // eax
    char* v11; // eax
    FancyStr lpPathName; // [esp+0h] [ebp-484h] BYREF
    struct _SECURITY_ATTRIBUTES SecurityAttributes; // [esp+Ch] [ebp-478h] BYREF
    char String1[260]; // [esp+18h] [ebp-46Ch] BYREF
    CHAR Buffer[260]; // [esp+11Ch] [ebp-368h] BYREF
    FancyStr v16[50]; // [esp+220h] [ebp-264h] BYREF
    int v17; // [esp+480h] [ebp-4h]

    lstrcpyA(String1, lpString2);
    v1 = strlen(String1) - 1;
    v2 = 0;
    for (i = 0; i < v1; ++i)
    {
        if (String1[i] == '/')
            String1[i] = '\\';
    }
    for (; v1 > 2; --v1)
    {
        if (String1[v1] == '\\')
            break;
    }
    v4 = String1[v1];
    v5 = &String1[v1];
    if (v4 == '\\')
    {
        *v5 = 0;
        GetCurrentDirectoryA(0x104u, Buffer);
        fSetCurrentDirectoryA = (void(__stdcall*)(LPCSTR))SetCurrentDirectoryA;
        if (SetCurrentDirectoryA(String1))
        {
            SetCurrentDirectoryA(Buffer);
        }
        else
        {
            FancyStrCtor(&lpPathName);
            v17 = 0;
            vector_constructor(
                (char*)v16,
                0xCu,
                50,
                (void(__thiscall*)(void*))FancyStrCtor,
                (void(__thiscall*)(void*))FancyStrDtor);
            LOBYTE(v17) = 1;
            FancyStrFromCStr(&lpPathName, String1);
            if (lpPathName.len)
            {
                v7 = v16;
                do
                {
                    FancyStrSubstring(&lpPathName, v7, '\\', 0, 0);
                    ++v2;
                    ++v7;
                } while (lpPathName.len);
            }
            FancyStrSet(&lpPathName, (const char**)&v16[0].buffer);
            if (v2 > 1)
            {
                v8 = &v16[1];
                v9 = v2 - 1;
                do
                {
                    FancyStrAppendCStr(&lpPathName, "\\");
                    FancyStrAppend(&lpPathName, v8);
                    if (lpPathName.len < 1 || (v10 = lpPathName.buffer) == 0)
                        v10 = emptyString;
                    if (!SetCurrentDirectoryA(v10))
                    {
                        SecurityAttributes.nLength = 12;
                        SecurityAttributes.lpSecurityDescriptor = 0;
                        SecurityAttributes.bInheritHandle = 0;
                        if (lpPathName.len < 1 || (v11 = lpPathName.buffer) == 0)
                            v11 = emptyString;
                        CreateDirectoryA(v11, &SecurityAttributes);
                    }
                    ++v8;
                    --v9;
                } while (v9);
                fSetCurrentDirectoryA = (void(__stdcall*)(LPCSTR))SetCurrentDirectoryA;
            }
            fSetCurrentDirectoryA(Buffer);
            LOBYTE(v17) = 0;
            vector_destructor((char*)v16, 0xCu, 50, (void(__thiscall*)(void*))FancyStrDtor);
            v17 = -1;
            FancyStrDtor(&lpPathName);
        }
    }
}
// 402330: using guessed type CHAR String1[260];


//----- (00402600) --------------------------------------------------------
BOOL __stdcall TestWriteToPath(char* a2)
{
    char* buffer; // eax
    HANDLE FirstFileA; // eax
    char* v3; // eax
    FILE* v4; // esi
    char* v5; // eax
    HANDLE v6; // eax
    char* v8; // eax
    char* v9; // eax
    char* v10; // esi
    FancyStr lpFileName; // [esp+10h] [ebp-160h] BYREF
    char v12[8]; // [esp+1Ch] [ebp-154h] BYREF
    struct _WIN32_FIND_DATAA FindFileData; // [esp+24h] [ebp-14Ch] BYREF
    int v14; // [esp+16Ch] [ebp-4h]

    FancyStrCtorFromCStr(&lpFileName, a2);
    v14 = 0;
    FancyStrAppendCStr(&lpFileName, "fcbox2.ini");
    if (lpFileName.len < 1 || (buffer = lpFileName.buffer) == 0)
        buffer = emptyString;
    FirstFileA = FindFirstFileA(buffer, &FindFileData);
    if (FirstFileA == (HANDLE)-1)
    {
        if (lpFileName.len < 1 || (v3 = lpFileName.buffer) == 0)
            v3 = emptyString;
        v4 = fopen(v3, "wb");
        if (!v4)
            goto LABEL_15;
        strcpy(v12, "ISBCC");
        fwrite(v12, 1u, 6u, v4);
        fclose(v4);
    }
    else
    {
        FindClose(FirstFileA);
    }
    if (lpFileName.len < 1 || (v5 = lpFileName.buffer) == 0)
        v5 = emptyString;
    v6 = FindFirstFileA(v5, &FindFileData);
    if (v6 == (HANDLE)-1)
    {
    LABEL_15:
        v14 = -1;
        FancyStrDtor(&lpFileName);
        return 0;
    }
    FindClose(v6);
    if (lpFileName.len < 1 || (v8 = lpFileName.buffer) == 0)
        v8 = emptyString;
    DeleteFileA(v8);
    if (lpFileName.len < 1 || (v9 = lpFileName.buffer) == 0)
        v9 = emptyString;
    v10 = (char*)FindFirstFileA(v9, &FindFileData);
    FindClose(v10);
    v14 = -1;
    FancyStrDtor(&lpFileName);
    return v10 + 1 == 0;
}

//----- (00402550) --------------------------------------------------------
void __stdcall RemoveEmptyDirectoryRecursively(LPCSTR lpString2)
{
    signed int v1; // esi
    signed int i; // eax
    char String1[260]; // [esp+0h] [ebp-104h] BYREF

    lstrcpyA(String1, lpString2);
    v1 = strlen(String1) - 1;
    for (i = 0; i < v1; ++i)
    {
        if (String1[i] == '/')
            String1[i] = '\\';
    }
    if (v1 <= 2)
    {
    LABEL_8:
        if (String1[v1] != '\\')
            return;
    }
    else
    {
        while (String1[v1] != '\\')
        {
            if (--v1 <= 2)
                goto LABEL_8;
        }
    }
    for (String1[v1] = 0; v1 > 2; String1[v1] = 0)
    {
        if (!RemoveDirectoryA(String1))
            break;
        while (String1[v1] != '\\')
        {
            if (--v1 <= 2)
            {
                if (String1[v1] != '\\')
                    return;
                break;
            }
        }
    }
}
// 4025D1: conditional instruction was optimized away because esi.4>=3
// 402550: using guessed type CHAR String1[260];

