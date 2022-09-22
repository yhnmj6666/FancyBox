#pragma once

#include <Windows.h>

#define __thiscall __fastcall
#define this _this
#define __usercall __fastcall

struct FancyStr
{
	char* buffer;
	int len;
	int capacity;
};

char* __thiscall FancyStrIsEmpty(FancyStr* this);
void __thiscall FancyStrDtor(FancyStr* this);
void __thiscall FancyStrCtor(FancyStr* this);
void __thiscall FancyStrSetCStr(FancyStr* this, const char* a2, int a3);
int __thiscall FancyStrFindNextChar(FancyStr* this, char a2, int a3);
char* __usercall find_cstr(char* result, const char* a2);
int __thiscall FancyStrFind(FancyStr* this, const char* a2, int start);
signed int __thiscall FancyStrToLower(FancyStr* this);
void __thiscall FancyStrInsertCStrAt(FancyStr* this, int, const char*);
void __thiscall FancyStrInsert(FancyStr* this, int, char);
void __thiscall FancyStrAppend(FancyStr* this, FancyStr* a2);
void __thiscall FancyStrAppendCStr(FancyStr* this, const char*);
char __thiscall FancyStrCharAt(FancyStr* this, int a2);
BOOL __thiscall FancyStrEquals(FancyStr* this, const char* a2);
BOOL __thiscall FancyStrNotEquals(FancyStr* this, FancyStr* a2);
BOOL __thiscall FancyStrNotEqual(FancyStr* this, const char* a2);
void __thiscall FancyStrReplace(FancyStr* this, const char* a2, const char* a3);
void __thiscall FancyStrRemove(FancyStr* this, int index, int size);
int __cdecl Cstr_to_int(char*);
void __thiscall FancyStrResize(FancyStr* this, int a2);
char* __thiscall FancyStrAlloc(FancyStr* this, int);
void __thiscall FancyStrShrink(FancyStr* this);
int __thiscall FancyStrTrimTailChar(FancyStr* this, char a2);
BOOL __thiscall FancyStrStartsWith(FancyStr* this, const char* a2);
FancyStr* __thiscall FancyStrSetStr(FancyStr* this, const char**);
void __thiscall FancyStrCtorFromCStr(FancyStr* this, char* a2);
void FancyStrSetVAStr(FancyStr*, LPCSTR arg4, ...);
void __thiscall FancyStrSet(FancyStr* this, const char**);
void __thiscall FancyStrFromCStr(FancyStr* this, const char*);
int __thiscall FancyStrSubstring(FancyStr* this, FancyStr* a2, char separator, char a4, int a5);
int __thiscall FancyStrGetInteger(FancyStr* this, int nDefault, char separator);
FancyStr* __thiscall FancyStrSubString(FancyStr* this, FancyStr* a2, int a3, int a4);
int InitialzeHexMap();

extern char* emptyString;