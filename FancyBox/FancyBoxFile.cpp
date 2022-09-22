#define _CRT_SECURE_NO_WARNINGS

#include "FancyBoxFile.hpp"
#include "common.hpp"

#include <stdlib.h>
#include <time.h>

//----- (004060D0) --------------------------------------------------------
void __thiscall FancyBoxFileInitialize(FancyBoxFile* this)
{
    FancyStrCtor(&this->Filename);
    this->hFile = 0;
    this->bOpened = 0;
}

//----- (00406310) --------------------------------------------------------
void __thiscall FancyBoxFileClose(FancyBoxFile* this)
{
    if (this->hFile && this->bOpened)
        CloseHandle(this->hFile);
    this->hFile = 0;
    this->bOpened = 0;
}

//----- (00406340) --------------------------------------------------------
int __thiscall FancyBoxFileRead(FancyBoxFile* this, LPVOID lpBuffer, int nNumberOfBytesToRead)
{
    HANDLE hFile; // eax
    int v4; // esi
    bool v5; // zf
    int result; // eax

    hFile = this->hFile;
    if (!hFile || !this->bOpened)
        return 0;
    v4 = nNumberOfBytesToRead;
    v5 = !ReadFile(hFile, lpBuffer, nNumberOfBytesToRead, (LPDWORD)&nNumberOfBytesToRead, 0);
    result = nNumberOfBytesToRead;
    if (v5 && nNumberOfBytesToRead != v4)
        return 0;
    return result;
}

//----- (00406380) --------------------------------------------------------
int __thiscall FancyBoxFileWrite(FancyBoxFile* this, LPCVOID lpBuffer, int nNumberOfBytesToWrite)
{
    HANDLE hFile; // eax
    int v4; // esi
    bool v5; // zf
    int result; // eax

    hFile = this->hFile;
    if (!hFile || !this->bOpened)
        return 0;
    v4 = nNumberOfBytesToWrite;
    v5 = !WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, (LPDWORD)&nNumberOfBytesToWrite, 0);
    result = nNumberOfBytesToWrite;
    if (v5 && nNumberOfBytesToWrite != v4)
        return 0;
    return result;
}

//----- (004069F0) --------------------------------------------------------
int __thiscall FancyBoxFileReadStr(FancyBoxFile* this, FancyStr* a2)
{
    HANDLE hFile; // eax
    HANDLE v4; // eax
    int FileSize; // esi
    char* v7; // ebx

    hFile = this->hFile;
    if (!hFile || !this->bOpened)
        return 0;
    SetFilePointer(hFile, 0, 0, 0);
    v4 = this->hFile;
    if (!v4)
        return 0;
    if (!this->bOpened)
        return 0;
    FileSize = GetFileSize(v4, 0);
    if (!FileSize)
        return 0;
    v7 = FancyStrAlloc(a2, FileSize + 1);
    if (FancyBoxFileRead(this, v7, FileSize) != FileSize)
        return 0;
    v7[FileSize] = 0;
    FancyStrShrink(a2);
    return 1;
}

//----- (00406B50) --------------------------------------------------------
void __thiscall FancyBoxFileDtor(FancyBoxFile* this)
{
    if (this->hFile && this->bOpened)
    {
        CloseHandle(this->hFile);
        this->hFile = 0;
        this->bOpened = 0;
    }
    FancyStrDtor(&this->Filename);
}

//----- (00406B80) --------------------------------------------------------
int __thiscall FancyBoxFileOpen(FancyBoxFile* this, char* a2, unsigned int a3)
{
    FancyStr* p_Filename; // esi
    bool v5; // zf
    DWORD v6; // ebx
    DWORD v7; // ebp
    char* buffer; // eax
    char* v9; // eax
    HANDLE FileA; // eax

    if (this->hFile && this->bOpened)
        CloseHandle(this->hFile);
    p_Filename = &this->Filename;
    this->hFile = 0;
    this->bOpened = 0;
    FancyStrFromCStr(&this->Filename, a2);
    if (a3 > 2)
    {
        v5 = a3 == 4096;
    LABEL_11:
        if (!v5)
            return 0;
        v6 = 0x40000000;
        goto LABEL_13;
    }
    if (a3 != 2)
    {
        if (!a3)
        {
            v6 = 0x80000000;
            v7 = 3;
            goto LABEL_17;
        }
        v5 = a3 == 1;
        goto LABEL_11;
    }
    v6 = -1073741824;
LABEL_13:
    v7 = 2;
    if (this->Filename.len < 1 || (buffer = p_Filename->buffer) == 0)
        buffer = emptyString;
    FancyBoxChangeAndCreateDirectory(buffer);
LABEL_17:
    if (this->Filename.len < 1 || (v9 = p_Filename->buffer) == 0)
        v9 = emptyString;
    FileA = CreateFileA(v9, v6, 1u, 0, v7, 0x80u, 0);
    this->hFile = FileA;
    if (FileA && FileA != (HANDLE)-1)
    {
        this->bOpened = 1;
        return 1;
    }
    return 0;
}

//----- (004060F0) --------------------------------------------------------
void __cdecl FancyBoxChangeAndCreateDirectory(LPCSTR lpString2)
{
    signed int i; // eax
    char v2; // cl
    char* v3; // eax
    int v4; // ebp
    FancyStr* v5; // edi
    int NextChar; // esi
    int v7; // edi
    FancyStr* v8; // esi
    char* buffer; // eax
    char* v10; // eax
    FancyStr lpPathName; // [esp+4h] [ebp-308h] BYREF
    struct _SECURITY_ATTRIBUTES SecurityAttributes; // [esp+10h] [ebp-2FCh] BYREF
    char String1[260]; // [esp+1Ch] [ebp-2F0h] BYREF
    FancyStr v14; // [esp+120h] [ebp-1ECh] BYREF
    char v15; // [esp+12Ch] [ebp-1E0h] BYREF
    int v16; // [esp+308h] [ebp-4h]

    lstrcpyA(String1, lpString2);
    for (i = strlen(String1) - 1; i > 2; --i)
    {
        if (String1[i] == 92)
            break;
    }
    v2 = String1[i];
    v3 = &String1[i];
    if (v2 == '\\')
    {
        *v3 = 0;
        if (!SetCurrentDirectoryA(String1))
        {
            v4 = 0;
            FancyStrCtor(&lpPathName);
            v16 = 0;
            vector_constructor((char*)&v14, 0xCu, 40, (void(__thiscall*)(void*))FancyStrCtor, (void(__thiscall*)(void*))FancyStrDtor);
            LOBYTE(v16) = 1;
            FancyStrFromCStr(&lpPathName, String1);
            if (lpPathName.len >= 1)
            {
                v5 = &v14;
                do
                {
                    NextChar = FancyStrFindNextChar(&lpPathName, '\\', 0);
                    if (NextChar <= 0)
                    {
                        FancyStrSet(v5, (const char**)&lpPathName.buffer);
                        if (lpPathName.buffer)
                            free(lpPathName.buffer);
                        memset(&lpPathName, 0, sizeof(lpPathName));
                    }
                    else
                    {
                        FancyStrSet(v5, (const char**)&lpPathName.buffer);
                        FancyStrResize(v5, NextChar);
                        FancyStrRemove(&lpPathName, 0, NextChar + 1);
                    }
                    ++v4;
                    ++v5;
                } while (lpPathName.len >= 1);
            }
            FancyStrSet(&lpPathName, (const char**)&v14.buffer);
            if (v4 > 1)
            {
                v7 = v4 - 1;
                v8 = (FancyStr*)&v15;
                do
                {
                    FancyStrAppendCStr(&lpPathName, "\\");
                    FancyStrAppend(&lpPathName, v8);
                    if (lpPathName.len < 1 || (buffer = lpPathName.buffer) == 0)
                        buffer = emptyString;
                    if (!SetCurrentDirectoryA(buffer))
                    {
                        SecurityAttributes.nLength = 12;
                        SecurityAttributes.lpSecurityDescriptor = 0;
                        SecurityAttributes.bInheritHandle = 0;
                        if (lpPathName.len < 1 || (v10 = lpPathName.buffer) == 0)
                            v10 = emptyString;
                        CreateDirectoryA(v10, &SecurityAttributes);
                    }
                    ++v8;
                    --v7;
                } while (v7);
            }
            LOBYTE(v16) = 0;
            vector_destructor((char*)&v14, 0xCu, 40, (void(__thiscall*)(void*))FancyStrDtor);
            v16 = -1;
            FancyStrDtor(&lpPathName);
        }
    }
}
// 4060F0: using guessed type CHAR String1[260];

//----- (00406470) --------------------------------------------------------
BOOL __cdecl Time_tToFileTime(time_t a1, LPFILETIME lpFileTime)
{
    WORD* v2; // eax
    struct _FILETIME FileTime; // [esp+0h] [ebp-18h] BYREF
    SYSTEMTIME SystemTime; // [esp+8h] [ebp-10h] BYREF

    v2 = (WORD*)localtime(&a1);
    if (v2
        && (SystemTime.wYear = v2[10] + 1900,
            SystemTime.wMonth = v2[8] + 1,
            SystemTime.wDay = v2[6],
            SystemTime.wHour = v2[4],
            SystemTime.wMinute = v2[2],
            SystemTime.wSecond = *v2,
            SystemTime.wMilliseconds = 0,
            SystemTimeToFileTime(&SystemTime, &FileTime)))
    {
        return LocalFileTimeToFileTime(&FileTime, lpFileTime);
    }
    else
    {
        return 0;
    }
}

//----- (004063C0) --------------------------------------------------------
time_t __thiscall FileTimeToTime_t(FILETIME* lpFileTime)
{
    struct _FILETIME LocalFileTime; // [esp+0h] [ebp-3Ch] BYREF
    struct _SYSTEMTIME SystemTime; // [esp+8h] [ebp-34h] BYREF
    struct tm v4; // [esp+18h] [ebp-24h] BYREF

    if (!FileTimeToLocalFileTime(lpFileTime, &LocalFileTime) || !FileTimeToSystemTime(&LocalFileTime, &SystemTime))
        return 0;
    v4.tm_wday = 0;
    v4.tm_yday = 0;
    v4.tm_sec = SystemTime.wSecond;
    v4.tm_min = SystemTime.wMinute;
    v4.tm_hour = SystemTime.wHour;
    v4.tm_mday = SystemTime.wDay;
    v4.tm_mon = SystemTime.wMonth - 1;
    v4.tm_year = SystemTime.wYear - 1900;
    v4.tm_isdst = -1;
    return mktime(&v4);
}

//----- (00406500) --------------------------------------------------------
BOOL __cdecl FancySetFileTime(LPCSTR lpFileName, time_t a2)
{
    BOOL result; // eax
    HANDLE FileA; // esi
    FILETIME CreationTime; // [esp+0h] [ebp-8h] BYREF

    result = Time_tToFileTime(a2, &CreationTime);
    if (result)
    {
        FileA = CreateFileA(lpFileName, 0xC0000000, 1u, 0, 3u, 0x80u, 0);
        return FileA != (HANDLE)-1 && SetFileTime(FileA, &CreationTime, &CreationTime, &CreationTime) && CloseHandle(FileA);
    }
    return result;
}

//----- (00406A80) --------------------------------------------------------
void __cdecl GetPathAndFilenameFromCstr(FancyStr* a1, FancyStr* a2, char* a3)
{
    signed int v3; // esi
    char v4; // al
    char v5[2048]; // [esp+8h] [ebp-800h] BYREF

    strcpy(v5, a3);
    v3 = strlen(v5) - 1;
    if (v3 < 0)
    {
    LABEL_7:
        if (a1->buffer)
            free(a1->buffer);
        a1->buffer = 0;
        a1->len = 0;
        a1->capacity = 0;
        FancyStrFromCStr(a2, a3);
    }
    else
    {
        while (1)
        {
            v4 = v5[v3];
            if (v4 == '\\' || v4 == '/')
                break;
            if (--v3 < 0)
                goto LABEL_7;
        }
        v5[v3] = 0;
        FancyStrFromCStr(a1, v5);
        FancyStrAppendCStr(a1, "\\");
        FancyStrFromCStr(a2, &v5[v3 + 1]);
    }
}
// 406ACB: conditional instruction was optimized away because esi.4>=0

