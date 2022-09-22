#define _CRT_SECURE_NO_WARNINGS

#include "FancyLinedText.hpp"
#include "FancyStr.hpp"
#include "FancyBoxFile.hpp"
#include "common.hpp"

#include <stdlib.h>
#include <string.h>

FancyLinedText* (__thiscall* off_412660)(FancyLinedText* this, char) = &FancyLinedTextRelease; // weak

//----- (00407D80) --------------------------------------------------------
FancyLinedText* __thiscall FancyLinedTextCtor(FancyLinedText* this)
{
    FancyLinedText* result; // eax

    result = this;
    this->__vftbl = (int)&off_412660;
    this->size = 0;
    this->count = 0;
    this->line = 0;
    return result;
}
// 412660: using guessed type int (__thiscall *off_412660)(void *, char);

//----- (00407DA0) --------------------------------------------------------
void __thiscall FancyLinedTextAddLine(FancyLinedText* this, const char* a2)
{
    int count; // eax
    int v5; // eax
    char** v6; // ebp

    if (a2)
    {
        if (!this->line)
        {
            this->count = 50;
            this->line = (char**)operator new(0xC8u);
        }
        count = this->count;
        if (this->size >= count - 1)
        {
            v5 = count + 50;
            this->count = v5;
            v6 = (char**)operator new(4 * v5);
            qmemcpy(v6, this->line, 4 * this->size);
            free(this->line);
            this->line = v6;
        }
        this->line[this->size] = (char*)operator new(strlen(a2) + 2);
        strcpy(this->line[this->size++], a2);
    }
}

//----- (00407E70) --------------------------------------------------------
void __thiscall FancyLinedTextClear(FancyLinedText* this)
{
    int i; // edi

    if (this->line)
    {
        for (i = 0; i < this->size; ++i)
            free(this->line[i]);
        free(this->line);
        this->line = 0;
    }
    this->count = 0;
    this->size = 0;
}

//----- (00407EC0) --------------------------------------------------------
char* __thiscall FancyLinedTextGetLine(FancyLinedText* this, int a2)
{
    if (a2 < 0 || a2 >= this->size)
        return 0;
    else
        return this->line[a2];
}

//----- (00407EE0) --------------------------------------------------------
int __thiscall FancyLinedTextSize(FancyLinedText* this)
{
    return this->size;
}

//----- (00407EF0) --------------------------------------------------------
void __thiscall FancyLinedTextFillFromBuffer(FancyLinedText* this, char* a2)
{
    int v3; // esi
    int v4; // edi
    FancyStr* v5; // eax
    char* buffer; // eax
    FancyStr* v7; // eax
    char* v8; // eax
    FancyStr v9; // [esp+10h] [ebp-30h] BYREF
    FancyStr v10; // [esp+1Ch] [ebp-24h] BYREF
    FancyStr v11; // [esp+28h] [ebp-18h] BYREF
    int v12; // [esp+3Ch] [ebp-4h]

    FancyStrCtorFromCStr(&v10, a2);
    v3 = 0;
    v12 = 0;
    FancyStrCtor(&v9);
    LOBYTE(v12) = 1;
    FancyLinedTextClear(this);
    v4 = FancyStrFind(&v10, "\r\n", 0);
    if (v4 >= 0)
    {
        do
        {
            v5 = FancyStrSubString(&v10, &v11, v3, v4 - v3);
            LOBYTE(v12) = 2;
            FancyStrSet(&v9, (const char**)&v5->buffer);
            LOBYTE(v12) = 1;
            FancyStrDtor(&v11);
            if (v9.len < 1 || (buffer = v9.buffer) == 0)
                buffer = emptyString;
            FancyLinedTextAddLine(this, buffer);
            v3 = v4 + 2;
            v4 = FancyStrFind(&v10, "\r\n", v4 + 2);
        } while (v4 >= v3);
    }
    v7 = FancyStrSubString(&v10, &v11, v3, v10.len - v3);
    LOBYTE(v12) = 3;
    FancyStrSet(&v9, (const char**)&v7->buffer);
    LOBYTE(v12) = 1;
    FancyStrDtor(&v11);
    if (v9.len < 1 || (v8 = v9.buffer) == 0)
        v8 = emptyString;
    FancyLinedTextAddLine(this, v8);
    LOBYTE(v12) = 0;
    FancyStrDtor(&v9);
    v12 = -1;
    FancyStrDtor(&v10);
}

//----- (00408040) --------------------------------------------------------
void __thiscall FancyLinedTextDtor(FancyLinedText* this)
{
    this->__vftbl = (int)&off_412660;
    FancyLinedTextClear(this);
}
// 412660: using guessed type int (__thiscall *off_412660)(void *, char);

//----- (00408050) --------------------------------------------------------
int __thiscall FancyLinedTextFillFromFile(FancyLinedText* this, FancyBoxFile* a2)
{
    char* buffer; // eax
    FancyStr v5; // [esp+4h] [ebp-18h] BYREF
    int v6; // [esp+18h] [ebp-4h]

    FancyStrCtor(&v5);
    v6 = 0;
    if (FancyBoxFileReadStr(a2, &v5))
    {
        if (v5.len < 1 || (buffer = v5.buffer) == 0)
            buffer = emptyString;
        FancyLinedTextFillFromBuffer(this, buffer);
        v6 = -1;
        FancyStrDtor(&v5);
        return 1;
    }
    else
    {
        v6 = -1;
        FancyStrDtor(&v5);
        return 0;
    }
}

//----- (00408100) --------------------------------------------------------
int __thiscall FancyLinedTextFillFromPath(FancyLinedText* this, char* a1)
{
    FancyBoxFile v4; // [esp+4h] [ebp-20h] BYREF
    int v5; // [esp+20h] [ebp-4h]

    FancyBoxFileInitialize(&v4);
    v5 = 0;
    if (FancyBoxFileOpen(&v4, a1, 0))
    {
        FancyLinedTextFillFromFile(this, &v4);
        FancyBoxFileClose(&v4);
        v5 = -1;
        FancyBoxFileDtor(&v4);
        return 1;
    }
    else
    {
        v5 = -1;
        FancyBoxFileDtor(&v4);
        return 0;
    }
}

//----- (004081B0) --------------------------------------------------------
FancyLinedText* __thiscall FancyLinedTextRelease(FancyLinedText* this, char a2)
{
    this->__vftbl = (int)&off_412660;
    FancyLinedTextClear(this);
    if ((a2 & 1) != 0)
        free(this);
    return this;
}
// 412660: using guessed type int (__thiscall *off_412660)(void *, char);

