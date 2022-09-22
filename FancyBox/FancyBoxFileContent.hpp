#pragma once

#include "FancyBoxFile.hpp"

#include <Windows.h>

#define __thiscall __fastcall
#define this _this
#define __usercall __fastcall

/* 77 */
struct FancyBoxFileContent
{
	int buffer;
	int capacity;
	int fileSize;
	int readSize;
	int paddingSize;
};

void __thiscall FancyBoxFileContentCtor(FancyBoxFileContent* this);
unsigned int __thiscall pfnreadInternal(FancyBoxFileContent* this, void* a2, unsigned int a3);
int __thiscall FancyBoxFileContentRead(FancyBoxFileContent* this, FancyBoxFile* a2);
unsigned int __thiscall pfnwriteInternal(FancyBoxFileContent* this, const void* a2, unsigned int a3);
BOOL __thiscall FancyBoxFileContentWrite(FancyBoxFileContent* this, FancyBoxFile* a2);
int __thiscall pfnseekInternal(FancyBoxFileContent* this, int a2, int a3);
void __thiscall FancyBoxFileContentDtor(FancyBoxFileContent* this);
