#pragma once

#define __thiscall __fastcall
#define this _this
#define __usercall __fastcall

/* 236 */
struct FancyLinedText
{
	int __vftbl;
	int size;
	int count;
	char** line;
};

FancyLinedText* __thiscall FancyLinedTextCtor(FancyLinedText* this);
void __thiscall FancyLinedTextAddLine(FancyLinedText* this, const char* a2);
void __thiscall FancyLinedTextClear(FancyLinedText* this);
char* __thiscall FancyLinedTextGetLine(FancyLinedText* this, int);
int __thiscall FancyLinedTextSize(FancyLinedText* this);
void __thiscall FancyLinedTextFillFromBuffer(FancyLinedText* this, char* a2);
void __thiscall FancyLinedTextDtor(FancyLinedText* this);
int __thiscall FancyLinedTextFillFromPath(FancyLinedText* this, char* a1);
FancyLinedText* __thiscall FancyLinedTextRelease(FancyLinedText* this, char a2);