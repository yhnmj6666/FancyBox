#pragma once

#include <Windows.h>

#include "FancyStr.hpp"

struct FancyDownloader;

/* 230 */
struct FancyDownloaderSubCallback : IHttpNegotiate
{
	int refCount;
	IBinding* binding;
	IStream* stream;
	FancyDownloader* downloader;
	int completed;
	FancyStr url;
};


/* 197 */
struct FancyDownloaderCallback : IBindStatusCallback, FancyDownloaderSubCallback
{
};

/* 80 */
struct FancyDownloader
{
	FancyDownloaderCallback* callback;
	IMoniker* urlMoniker;
	IBindCtx* bindCtx;
	IStream* iStream;
	FancyStr netPath;
	FancyStr localPath;
	FancyStr filename;
	int buffer;
	int capacity;
	int size;
	int contentLength;
	int lastModified;
	int field_48;
	int field_4C;
	int stage;
	int completed;
	int field_58;
	void(__cdecl* fUpdateProgress)(int, unsigned int);
};

void __thiscall FancyDownloaderCallbackDtor(FancyDownloaderCallback* this);
int __stdcall IBindStatusCallback_AddRef(FancyDownloaderCallback* a1);
int __stdcall IBindStatusCallback_QueryInterface(FancyDownloaderCallback*, const GUID& a2, IUnknown**);
int __stdcall IHttpNegotiate_BeginningTransaction(int, int, int, int, int);
int __stdcall IBindStatusCallback_GetPriority(int, int);
int __stdcall IBindStatusCallback_GetBindInfo(FancyDownloaderCallback* a1, BINDF* a2, BINDINFO* a3);
int __stdcall IBindStatusCallback_OnObjectAvailable(int, int, int);
FancyDownloader* __thiscall FancyDownloaderCtor(FancyDownloader* this);
void __thiscall FancyDownloaderRelease(FancyDownloader* this);
void __thiscall FancyDownloaderAppendBuffer(FancyDownloader* this, const void* a2, unsigned int a3);
bool __thiscall FancyDownloaderHasCompleted(FancyDownloader* this, int contentLength, unsigned int lastModified);
int __thiscall FancyDownloaderWriteToFile(FancyDownloader* this);
int processWindowsMessages();
int __stdcall IHttpNegotiate_QueryInterface(int, const GUID& a2, IUnknown**);
int __stdcall IHttpNegotiate_AddRef(int);
int __stdcall IBindStatusCallback_Release(FancyDownloaderCallback* a1);
int __stdcall IHttpNegotiate_OnResponse(FancyDownloaderSubCallback* a1, DWORD a2, int a3, int a4, int a5);
int __stdcall IBindStatusCallback_OnStartBinding(FancyDownloaderCallback* a1, int a2, IBinding* a3);
int __stdcall IBindStatusCallback_OnProgress(FancyDownloaderCallback* a1, int a2, unsigned int a3, int a4, int a5);
int __stdcall IBindStatusCallback_OnDataAvailable(FancyDownloaderCallback* a1, unsigned int a2, int a3, int a4, STGMEDIUM* a5);
void __thiscall FancyDownloaderDtor(FancyDownloader* this);
int __stdcall IHttpNegotiate_Release(FancyDownloaderCallback* a1);
int __stdcall IBindStatusCallback_OnStopBinding(FancyDownloaderCallback*, int, int);
void __thiscall FancyDownloaderOpen(FancyDownloader* this);

time_t __cdecl SystemTimeToTime_t(SYSTEMTIME SystemTime);
char* __cdecl TrimPath(const char*);
