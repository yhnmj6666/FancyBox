#pragma once

#include <Windows.h>
#include <string>
#include <stdexcept>

class FPPString
{
private:
	std::string _data;
	inline FPPString(std::string s) :_data(s) {}
public:
	inline FPPString() {}
	inline FPPString(const char* str) : _data(str) {}
	inline const size_t len() {
		return _data.length();
	}
	inline const char* data() {
		return _data.c_str();
	}
	inline void set(const char* data, int length) {
		_data = std::string(data, length);
	}
	inline int find(char ch, int start) {
		return _data.find(ch, start);
	}
	inline int find(const char* str, int start) {
		return _data.find(str, start);
	}
	inline int lower() {
		if (_data.size() >= 1)
			return CharLowerBuffA((char*)_data.c_str(), _data.size());
		return 0;
	}
	inline void insert(int position, const char* str) {
		_data.insert(position, str);
	}
	inline void insert(int position, char ch) {
		_data.insert(position, 1, ch);
	}
	inline void append(const FPPString& s) {
		_data.append(s._data);
	}
	inline void append(const char* str) {
		_data.append(str);
	}
	inline char at(int position) {
		return _data[position];
	}
	inline bool equals(const char* str) {
		return _data == str;
	}
	inline bool not_equals(const char* str) {
		return _data != str;
	}
	inline bool not_equals(const FPPString& s) {
		return _data != s._data;
	}
	inline void replace(const char* source, const char* dest) {
		size_t index = 0;
		size_t source_len = strlen(source);
		while ((index=_data.find(source,index)) != std::string::npos) {
			_data.replace(index, source_len, dest);
		}
	}
	inline void remove(int position, int size) {
		_data.erase(position, size);
	}
	inline void resize(int size) {
		_data.resize(size);
	}
	inline char* alloc(int size) {
		_data.resize(size);
		return (char*)_data.c_str();
	}
	inline void shrink() {
		_data.shrink_to_fit();
	}
	inline int trim_right(char ch) {
		if (_data.size() < 1 || ch != *_data.rbegin())
			return 0;
		_data.erase(_data.end() - 1);
		return 1;
	}
	inline bool starts_with(const char ch) {
		return _data.size() > 0 && _data[0] == ch;
	}
	inline bool starts_with(const char* str) {
		int i = 0;
		if (_data.size() < strlen(str))
			return false;
		while (i < strlen(str)) {
			if (_data[i] != str[i])
				return false;
		}
		return true;
	}
	inline FPPString& set(const char** str) {
		if (**str != '\0')
			_data = std::string(*str);
		return *this;
	}
	// return false for last segment.
	inline bool yield(FPPString& fragment, char separator, char='\0', int=0) {
		size_t sep = _data.find(separator);
		if (sep == std::string::npos) {
			fragment = _data;
			_data.clear();
			return false;
		}
		else {
			fragment = FPPString(_data.substr(0, sep));
			_data.erase(0, sep + 1);
			return true;
		}
	}
	inline int to_int(int nDefault, char separator) {
		FPPString fragment;
		try
		{
			if (yield(fragment, separator)) {
				if (fragment.starts_with('#'))
				{
					return std::strtol(fragment.data() + 1, nullptr, 16);
				}
				if (fragment.starts_with("0x"))
				{
					return std::stoi(fragment._data, nullptr, 16);
				}
				return std::stoi(fragment._data);
			}
			return nDefault;
		}
		catch (const std::invalid_argument&)
		{
			return nDefault;
		}
		catch (const std::out_of_range&)
		{
			return nDefault;
		}
	}
	inline FPPString& substring(FPPString& substring, int start, int len) {
		substring = FPPString(_data.substr(start, len));
		return substring;
	}
};

#define __thiscall __fastcall
#define __usercall __fastcall

struct FancyStr
{
	char* buffer;
	int len;
	int capacity;
};

char* __thiscall FancyStrIsEmpty(FancyStr* This);
void __thiscall FancyStrDtor(FancyStr* This);
void __thiscall FancyStrCtor(FancyStr* This);
void __thiscall FancyStrSetCStr(FancyStr* This, const char* a2, int a3);
int __thiscall FancyStrFindNextChar(FancyStr* This, char a2, int a3);
char* __usercall find_cstr(char* result, const char* a2);
int __thiscall FancyStrFind(FancyStr* This, const char* a2, int start);
signed int __thiscall FancyStrToLower(FancyStr* This);
void __thiscall FancyStrInsertCStrAt(FancyStr* This, int, const char*);
void __thiscall FancyStrInsert(FancyStr* This, int, char);
void __thiscall FancyStrAppend(FancyStr* This, FancyStr* a2);
void __thiscall FancyStrAppendCStr(FancyStr* This, const char*);
char __thiscall FancyStrCharAt(FancyStr* This, int a2);
BOOL __thiscall FancyStrEquals(FancyStr* This, const char* a2);
BOOL __thiscall FancyStrNotEquals(FancyStr* This, FancyStr* a2);
BOOL __thiscall FancyStrNotEqual(FancyStr* This, const char* a2);
void __thiscall FancyStrReplace(FancyStr* This, const char* a2, const char* a3);
void __thiscall FancyStrRemove(FancyStr* This, int index, int size);
int __cdecl Cstr_to_int(char*);
void __thiscall FancyStrResize(FancyStr* This, int a2);
char* __thiscall FancyStrAlloc(FancyStr* This, int);
void __thiscall FancyStrShrink(FancyStr* This);
int __thiscall FancyStrTrimTailChar(FancyStr* This, char a2);
BOOL __thiscall FancyStrStartsWith(FancyStr* This, const char* a2);
FancyStr* __thiscall FancyStrSetStr(FancyStr* This, const char**);
void __thiscall FancyStrCtorFromCStr(FancyStr* This, char* a2);
void FancyStrSetVAStr(FancyStr*, LPCSTR arg4, ...);
void __thiscall FancyStrSet(FancyStr* This, const char**);
void __thiscall FancyStrFromCStr(FancyStr* This, const char*);
// map to yield
int __thiscall FancyStrSubstring(FancyStr* This, FancyStr* a2, char separator, char a4, int a5);
int __thiscall FancyStrGetInteger(FancyStr* This, int nDefault, char separator);
FancyStr* __thiscall FancyStrSubString(FancyStr* This, FancyStr* a2, int a3, int a4);

extern char* emptyString;

int InitialzeHexMap();
#undef __thiscall
