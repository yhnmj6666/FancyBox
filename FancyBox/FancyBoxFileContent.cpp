#include "FancyBoxFileContent.hpp"
#include "FancyBoxFile.hpp"
#include "common.hpp"

//----- (00406700) --------------------------------------------------------
void __thiscall FancyBoxFileContentCtor(FancyBoxFileContent* this)
{
    this->buffer = 0;
    this->fileSize = 0;
    this->readSize = 0;
    this->capacity = 0;
    this->paddingSize = 128;
}

//----- (00406720) --------------------------------------------------------
unsigned int __thiscall pfnreadInternal(FancyBoxFileContent* this, void* a2, unsigned int a3)
{
    unsigned int result; // eax
    int readSize; // edi

    result = a3;
    readSize = this->readSize;
    if (readSize + a3 > this->fileSize)
        return 0;
    qmemcpy(a2, (const void*)(readSize + this->buffer), a3);
    this->readSize += a3;
    return result;
}

//----- (00406770) --------------------------------------------------------
int __thiscall FancyBoxFileContentRead(FancyBoxFileContent* this, FancyBoxFile* a2)
{
    FancyBoxFile* v3; // ebx
    HANDLE hFile; // eax
    DWORD FileSize; // edi
    HANDLE v6; // eax
    HANDLE v7; // eax
    bool v8; // zf
    DWORD v9; // eax
    DWORD v11; // [esp-4h] [ebp-10h]
    DWORD v12; // [esp+10h] [ebp+4h] FORCED BYREF

    if (this->buffer && this->capacity)
        free((void*)this->buffer);
    v3 = a2;
    this->buffer = 0;
    this->fileSize = 0;
    this->readSize = 0;
    this->capacity = 0;
    hFile = v3->hFile;
    if (!hFile)
        return 0;
    if (!v3->bOpened)
        return 0;
    FileSize = GetFileSize(hFile, 0);
    if (!FileSize)
        return 0;
    v11 = FileSize + this->paddingSize;
    this->capacity = v11;
    this->buffer = (int)operator new(v11);
    v6 = v3->hFile;
    if (v6 && v3->bOpened)
        SetFilePointer(v6, 0, 0, 0);
    v7 = v3->hFile;
    if (v7 && v3->bOpened)
    {
        v8 = !ReadFile(v7, (LPVOID)this->buffer, FileSize, &v12, 0);
        v9 = v12;
        if (!v8)
            goto LABEL_15;
        if (v12 == FileSize)
            goto LABEL_18;
    }
    v9 = 0;
LABEL_15:
    if (v9 != FileSize)
    {
        free((void*)this->buffer);
        this->buffer = 0;
        return 0;
    }
LABEL_18:
    this->fileSize = FileSize;
    this->readSize = FileSize;
    return 1;
}

//----- (00406850) --------------------------------------------------------
unsigned int __thiscall pfnwriteInternal(FancyBoxFileContent* this, const void* a2, unsigned int a3)
{
    void* v5; // eax
    unsigned int result; // eax
    int readSize; // eax
    char* v8; // eax
    int v9; // esi
    unsigned int fileSize; // ecx
    unsigned int v11; // edx
    void* buffer; // [esp-8h] [ebp-18h]
    SIZE_T v13; // [esp-4h] [ebp-14h]
    SIZE_T v14; // [esp-4h] [ebp-14h]
    int v15; // [esp+18h] [ebp+8h]

    if (this->buffer)
    {
        readSize = this->readSize;
        if (readSize + a3 < this->capacity)
        {
            qmemcpy((void*)(readSize + this->buffer), a2, a3);
            fileSize = this->fileSize;
            v11 = a3 + this->readSize;
            this->readSize = v11;
            if (v11 > fileSize)
                this->fileSize = v11;
            return a3;
        }
        else
        {
            v14 = this->fileSize + this->paddingSize + a3;
            this->capacity = v14;
            v8 = (char*)operator new(v14);
            qmemcpy(v8, (const void*)this->buffer, this->fileSize);
            v15 = (int)v8;
            qmemcpy(&v8[this->fileSize], a2, a3);
            v9 = a3 + this->readSize;
            buffer = (void*)this->buffer;
            this->readSize = v9;
            this->fileSize = v9;
            free(buffer);
            result = a3;
            this->buffer = v15;
        }
    }
    else
    {
        v13 = a3 + this->paddingSize;
        this->capacity = v13;
        v5 = operator new(v13);
        this->buffer = (int)v5;
        qmemcpy(v5, a2, a3);
        this->fileSize = a3;
        this->readSize = a3;
        return a3;
    }
    return result;
}

//----- (00406950) --------------------------------------------------------
BOOL __thiscall FancyBoxFileContentWrite(FancyBoxFileContent* this, FancyBoxFile* a2)
{
    int fileSize; // esi
    HANDLE hFile; // eax
    const void* buffer; // ecx
    bool v7; // zf
    int v8; // eax

    fileSize = this->fileSize;
    if (!fileSize)
        return 0;
    hFile = a2->hFile;
    buffer = (const void*)this->buffer;
    if (!hFile
        || !a2->bOpened
        || (v7 = !WriteFile(hFile, buffer, fileSize, (LPDWORD)&a2, 0), v8 = (int)a2, v7) && a2 != (FancyBoxFile*)fileSize)
    {
        v8 = 0;
    }
    return v8 == this->fileSize;
}

//----- (004069B0) --------------------------------------------------------
int __thiscall pfnseekInternal(FancyBoxFileContent* this, int a2, int a3)
{
    int result; // eax

    if (a3)
    {
        if (a3 == 1)
        {
            result = a2 + this->readSize;
            this->readSize = result;
            return result;
        }
        if (a3 == 2)
        {
            result = a2 + this->fileSize;
            this->readSize = result;
            return result;
        }
    }
    else
    {
        this->readSize = a2;
    }
    return this->readSize;
}

//----- (00406C60) --------------------------------------------------------
void __thiscall FancyBoxFileContentDtor(FancyBoxFileContent* this)
{
    if (this->buffer && this->capacity)
        free((void*)this->buffer);
    this->buffer = 0;
    this->fileSize = 0;
    this->readSize = 0;
    this->capacity = 0;
}

