#define _CRT_SECURE_NO_WARNINGS
#define CINTERFACE

#include "FancyDownloader.hpp"
#include "FancyBoxFile.hpp"
#include "common.hpp"

#include <stdlib.h>
#include <time.h>

#define __thiscall __fastcall
#define this _this

IHttpNegotiateVtbl stru_412570 =
{
  (HRESULT(__stdcall*)(IHttpNegotiate * This, const IID & riid, void** ppvObject)) & IHttpNegotiate_QueryInterface,
  (ULONG(__stdcall*)(IHttpNegotiate * This)) & IHttpNegotiate_AddRef,
  (ULONG(__stdcall*)(IHttpNegotiate * This)) & IHttpNegotiate_Release,
  (HRESULT(__stdcall*)(IHttpNegotiate * This, LPCWSTR szURL, LPCWSTR szHeaders, DWORD dwReserved, LPWSTR * pszAdditionalHeaders)) & IHttpNegotiate_BeginningTransaction,
  (HRESULT(__stdcall*)(IHttpNegotiate * This, DWORD dwResponseCode, LPCWSTR szResponseHeaders, LPCWSTR szRequestHeaders, LPWSTR * pszAdditionalRequestHeaders)) & IHttpNegotiate_OnResponse
};
IBindStatusCallbackVtbl stru_412584 =
{
  (HRESULT(__stdcall*)(IBindStatusCallback * This, const IID & riid, void** ppvObject)) & IBindStatusCallback_QueryInterface,
  (ULONG(__stdcall*)(IBindStatusCallback * This)) & IBindStatusCallback_AddRef,
  (ULONG(__stdcall*)(IBindStatusCallback * This)) & IBindStatusCallback_Release,
  (HRESULT(__stdcall*)(IBindStatusCallback * This, DWORD dwReserved, IBinding * pib)) & IBindStatusCallback_OnStartBinding,
  (HRESULT(__stdcall*)(IBindStatusCallback * This, LONG * pnPriority)) & IBindStatusCallback_GetPriority,
  (HRESULT(__stdcall*)(IBindStatusCallback * This, DWORD reserved)) & IBindStatusCallback_GetPriority,
  (HRESULT(__stdcall*)(IBindStatusCallback * This, ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, LPCWSTR szStatusText)) & IBindStatusCallback_OnProgress,
  (HRESULT(__stdcall*)(IBindStatusCallback * This, HRESULT hresult, LPCWSTR szError)) & IBindStatusCallback_OnStopBinding,
  (HRESULT(__stdcall*)(IBindStatusCallback * This, DWORD * grfBINDF, BINDINFO * pbindinfo)) & IBindStatusCallback_GetBindInfo,
  (HRESULT(__stdcall*)(IBindStatusCallback * This, DWORD grfBSCF, DWORD dwSize, FORMATETC * pformatetc, STGMEDIUM * pstgmed)) & IBindStatusCallback_OnDataAvailable,
  (HRESULT(__stdcall*)(IBindStatusCallback * This, const IID & riid, IUnknown * punk)) & IBindStatusCallback_OnObjectAvailable
};
GUID CLSID_IStream = { 12u, 0u, 0u, { 192u, 0u, 0u, 0u, 0u, 0u, 0u, 70u } };
GUID CLSID_IWinInetHttpInfo = { 2045430232u, 47866u, 4558u, { 140u, 130u, 0u, 170u, 0u, 75u, 169u, 11u } }; // weak
GUID CLSID_IHttpNegotiate = { 0x79EAC9D2, 0x0BAF9 ,0x11CE ,{0x8C,0x82,0,0xAA,0,0x4B,0xA9,0xB} };
GUID CLSID_IBindStatusCallback = { 0x79EAC9C1, 0x0BAF9 ,0x11CE ,{0x8C,0x82,0,0xAA,0,0x4B,0xA9,0xB} };
GUID CLSID_IUnknown = { 0u, 0u, 0u, { 192u, 0u, 0u, 0u, 0u, 0u, 0u, 70u } };

//----- (00404660) --------------------------------------------------------
void __thiscall FancyDownloaderCallbackDtor(FancyDownloaderCallback* this)
{
    IStream* stream; // eax

    this->IBindStatusCallback::lpVtbl = &stru_412584;
    this->FancyDownloaderSubCallback::IHttpNegotiate::lpVtbl = &stru_412570;
    stream = this->stream;
    if (stream)
        stream->lpVtbl->Release(stream);
    FancyStrDtor(&this->url);
}

//----- (004046C0) --------------------------------------------------------
int __stdcall IBindStatusCallback_AddRef(FancyDownloaderCallback* a1)
{
    int result; // eax

    result = a1->refCount;
    a1->refCount = result + 1;
    return result;
}

//----- (004046D0) --------------------------------------------------------
int __stdcall IBindStatusCallback_QueryInterface(FancyDownloaderCallback* a1, const GUID& a2, IUnknown** a3)
{
    IUnknown* v3; // ecx

    if (!memcmp(&a2, &CLSID_IUnknown, 0x10u) || !memcmp(&a2, &CLSID_IBindStatusCallback, 0x10u))
    {
        v3 = (IUnknown*)a1;
    }
    else
    {
        if (memcmp(&a2, &CLSID_IHttpNegotiate, 0x10u))
        {
            *a3 = 0;
            return E_NOINTERFACE;
        }
        if (a1)
            v3 = (IUnknown*)&a1->FancyDownloaderSubCallback::IHttpNegotiate::lpVtbl;
        else
            v3 = 0;
    }
    *a3 = v3;
    if (!v3)
        return E_NOINTERFACE;
    v3->lpVtbl->AddRef(v3);
    return 0;
}
// 412684: using guessed type GUID CLSID_IHttpNegotiate;
// 412694: using guessed type GUID CLSID_IBindStatusCallback;
// 4126A4: using guessed type GUID CLSID_IUnknown;

//----- (00404760) --------------------------------------------------------
int __stdcall IHttpNegotiate_BeginningTransaction(int a1, int a2, int a3, int a4, int a5)
{
    return 0;
}

//----- (00404810) --------------------------------------------------------
int __stdcall IBindStatusCallback_GetPriority(int a1, int a2)
{
    return E_NOTIMPL;
}

//----- (00404820) --------------------------------------------------------
int __stdcall IBindStatusCallback_GetBindInfo(FancyDownloaderCallback* a1, BINDF* a2, BINDINFO* a3)
{
    *a2 = (BINDF)(BINDF_PRAGMA_NO_CACHE | BINDF_PULLDATA | BINDF_GETNEWESTVERSION | BINDF_ASYNCSTORAGE | BINDF_ASYNCHRONOUS);
    a3->cbSize = 84;
    a3->szExtraInfo = 0;
    a3->stgmedData.tymed = 0;
    a3->stgmedData.hBitmap = 0;
    a3->stgmedData.pUnkForRelease = 0;
    a3->grfBindInfoF = 0;
    a3->dwBindVerb = 0;
    a3->szCustomVerb = 0;
    return 0;
}

//----- (00404860) --------------------------------------------------------
int __stdcall IBindStatusCallback_OnObjectAvailable(int a1, int a2, int a3)
{
    return E_NOTIMPL;
}

//----- (00404870) --------------------------------------------------------
FancyDownloader* __thiscall FancyDownloaderCtor(FancyDownloader* this)
{
    FancyStrCtor(&this->netPath);
    FancyStrCtor(&this->localPath);
    FancyStrCtor(&this->filename);
    this->stage = 0;
    this->fUpdateProgress = 0;
    this->callback = 0;
    this->urlMoniker = 0;
    this->bindCtx = 0;
    this->iStream = 0;
    this->field_58 = 0;
    this->contentLength = 0;
    this->lastModified = 0;
    this->field_48 = 0;
    this->completed = 0;
    this->buffer = 0;
    this->capacity = 0;
    this->size = 0;
    this->field_4C = 0;
    return this;
}

//----- (004048F0) --------------------------------------------------------
void __thiscall FancyDownloaderRelease(FancyDownloader* this)
{
    FancyDownloaderCallback* callback; // eax
    IBinding* binding; // eax
    IMoniker* urlMoniker; // eax
    void* buffer; // eax

    callback = this->callback;
    if (this->callback)
    {
        callback->downloader = 0;
        binding = callback->binding;
        if (binding)
            binding->lpVtbl->Abort(binding);
    }
    urlMoniker = this->urlMoniker;
    this->callback = 0;
    if (urlMoniker)
    {
        urlMoniker->lpVtbl->Release(urlMoniker);
        this->urlMoniker = 0;
    }
    buffer = (void*)this->buffer;
    this->urlMoniker = 0;
    this->bindCtx = 0;
    this->iStream = 0;
    if (buffer)
        free(buffer);
    this->buffer = 0;
    this->capacity = 0;
    this->size = 0;
    this->stage = 0;
}

//----- (00404950) --------------------------------------------------------
void __thiscall FancyDownloaderAppendBuffer(FancyDownloader* this, const void* a2, unsigned int a3)
{
    unsigned int v3; // esi
    int v5; // eax
    void* v6; // eax
    int v7; // ebp
    static int dword_4171B8;

    v3 = a3;
    dword_4171B8 += a3;
    v5 = a3 + this->size;
    if (v5 >= this->capacity)
    {
        this->capacity = v5 + 0x2000;
        v6 = operator new(v5 + 0x2000);
        v7 = (int)v6;
        if (this->size > 0)
        {
            qmemcpy(v6, (const void*)this->buffer, this->size);
            v3 = a3;
        }
        free((void*)this->buffer);
        this->buffer = v7;
    }
    qmemcpy((void*)(this->size + this->buffer), a2, v3);
    this->size += a3;
}
// 4171B8: using guessed type int dword_4171B8;

//----- (004049F0) --------------------------------------------------------
bool __thiscall FancyDownloaderHasCompleted(FancyDownloader* this, int contentLength, unsigned int lastModified)
{
    int v3; // eax

    v3 = this->contentLength;
    if (v3 > 0 && v3 == contentLength && lastModified / 0x3C == this->lastModified / 0x3Cu)
    {
        this->completed = 1;
        return 0;
    }
    else
    {
        this->contentLength = contentLength;
        this->lastModified = lastModified;
        return 1;
    }
}

//----- (00404A40) --------------------------------------------------------
int __thiscall FancyDownloaderWriteToFile(FancyDownloader* this)
{
    int size; // ebx
    const void* buffer; // ebp
    int len; // eax
    FancyStr* p_localPath; // edi
    char* v7; // eax
    char* v8; // eax
    int v9; // eax
    char* v10; // eax
    int v11; // [esp-10h] [ebp-34h]
    FancyBoxFile v12; // [esp+4h] [ebp-20h] BYREF
    int v13; // [esp+20h] [ebp-4h]

    if (this->completed)
        return 1;
    size = this->size;
    buffer = (const void*)this->buffer;
    if (size > 0 && size == this->contentLength)
    {
        FancyBoxFileInitialize(&v12);
        len = this->localPath.len;
        p_localPath = &this->localPath;
        v13 = 0;
        if (len < 1 || (v7 = p_localPath->buffer) == 0)
            v7 = emptyString;
        FancyBoxChangeAndCreateDirectory(v7);
        if (this->localPath.len < 1 || (v8 = p_localPath->buffer) == 0)
            v8 = emptyString;
        if (!FancyBoxFileOpen(&v12, v8, 1u))
        {
            this->field_4C = 2;
            v13 = -1;
            goto LABEL_14;
        }
        if (FancyBoxFileWrite(&v12, buffer, size) != size)
        {
            this->field_4C = 2;
            FancyBoxFileClose(&v12);
            v13 = -1;
        LABEL_14:
            FancyBoxFileDtor(&v12);
            return 0;
        }
        FancyBoxFileClose(&v12);
        v9 = this->field_48;
        if (v9)
            this->lastModified = v9;
        if (this->lastModified)
        {
            v11 = this->lastModified;
            v10 = FancyStrIsEmpty(&this->localPath);
            if (!FancySetFileTime(v10, v11))
                this->field_4C = 3;
        }
        v13 = -1;
        FancyBoxFileDtor(&v12);
        return 1;
    }
    else
    {
        this->field_4C = 1;
        return 0;
    }
}

//----- (00404BC0) --------------------------------------------------------
int processWindowsMessages()
{
    struct tagMSG Msg; // [esp+10h] [ebp-1Ch] BYREF

    if (!PeekMessageA(&Msg, 0, 0, 0, 0))
        return 1;
    while (GetMessageA(&Msg, 0, 0, 0))
    {
        TranslateMessage(&Msg);
        DispatchMessageA(&Msg);
        if (!PeekMessageA(&Msg, 0, 0, 0, 0))
            return 1;
    }
    return 0;
}

//----- (00404C40) --------------------------------------------------------
int __stdcall IHttpNegotiate_QueryInterface(int a1, const GUID& a2, IUnknown** a3)
{
    return IBindStatusCallback_QueryInterface((FancyDownloaderCallback*)(a1 - 4), a2, a3);
}

//----- (00404C50) --------------------------------------------------------
int __stdcall IHttpNegotiate_AddRef(int a1)
{
    return IBindStatusCallback_AddRef((FancyDownloaderCallback*)(a1 - 4));
}

//----- (00404C60) --------------------------------------------------------
int __stdcall IBindStatusCallback_Release(FancyDownloaderCallback* a1)
{
    int result; // eax
    bool v2; // cf

    result = a1->refCount - 1;
    v2 = a1->refCount == 1;
    a1->refCount = result;
    if (v2)
    {
        FancyDownloaderCallbackDtor(a1);
        free(a1);
        return 0;
    }
    return result;
}

//----- (00404C90) --------------------------------------------------------
int __stdcall IHttpNegotiate_OnResponse(FancyDownloaderSubCallback* a1, DWORD a2, int a3, int a4, int a5)
{
    FancyDownloaderSubCallback* v6; // esi
    IBinding* binding; // eax
    unsigned int lastModified; // eax
    FancyDownloader* downloader; // ecx
    int contentLength; // [esp+3Ch] [ebp-14h] BYREF
    SYSTEMTIME SystemTime; // [esp+40h] [ebp-10h] BYREF
    DWORD v12; // [esp+54h] [ebp+4h] FORCED BYREF
    IWinInetHttpInfo* v13; // [esp+58h] [ebp+8h] FORCED BYREF

    if (a2 == 200)
    {
        v6 = a1;
        binding = a1->binding;
        v13 = 0;
        if (binding->lpVtbl->QueryInterface(binding, CLSID_IWinInetHttpInfo, (void**)&v13) >= 0)
        {
            contentLength = 0;
            v12 = 4;
            v13->lpVtbl->QueryInfo(v13, 0x20000005, &contentLength, &v12, 0, 0);// HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER
            v12 = 16;
            if (!v13->lpVtbl->QueryInfo(v13, 0x4000000B, &SystemTime, &v12, 0, 0))// HTTP_QUERY_LAST_MODIFIED | HTTP_QUERY_FLAG_SYSTEMTIME
            {
                lastModified = SystemTimeToTime_t(SystemTime);
                downloader = v6->downloader;
                if (downloader)
                {
                    if (!FancyDownloaderHasCompleted(downloader, contentLength, lastModified))
                    {
                        v6->completed = 1;
                        v6->binding->lpVtbl->Abort(v6->binding);
                    }
                }
            }
        }
        if (v13)
            v13->lpVtbl->Release(v13);
        return 0;
    }
    else
    {
        a1->binding->lpVtbl->Abort(a1->binding);
        return 0;
    }
}
// 412674: using guessed type GUID CLSID_IWinInetHttpInfo;

//----- (00404DA0) --------------------------------------------------------
int __stdcall IBindStatusCallback_OnStartBinding(FancyDownloaderCallback* a1, int a2, IBinding* a3)
{
    FancyDownloader* field_14; // esi
    void* buffer; // eax

    if (a3)
    {
        a1->binding = a3;
        a3->lpVtbl->AddRef(a3);
    }
    field_14 = a1->downloader;
    if (field_14)
    {
        buffer = (void*)field_14->buffer;
        field_14->field_58 = 10;
        if (buffer)
            free(buffer);
        field_14->capacity = 0x2000;
        field_14->buffer = (int)operator new(0x2000u);
        field_14->size = 0;
        field_14->stage = 2;
    }
    return 0;
}

//----- (00404E00) --------------------------------------------------------
int __stdcall IBindStatusCallback_OnProgress(FancyDownloaderCallback* a1, int a2, unsigned int a3, int a4, int a5)
{
    FancyDownloader* downloader; // ecx
    void(__cdecl * fUpdateProgress)(int, unsigned int); // eax
    char* buffer; // ecx

    downloader = a1->downloader;
    if (!downloader)
        return 0;
    if (a3 < 2)
        return 0;
    downloader->field_58 = (a2 << 10) / a3;
    fUpdateProgress = downloader->fUpdateProgress;
    if (fUpdateProgress)
    {
        if (downloader->filename.len < 1 || (buffer = downloader->filename.buffer) == 0)
            buffer = emptyString;
        ((void(__cdecl*)(int, unsigned int, char*))fUpdateProgress)(a2, a3, buffer);
    }
    return 0;
}

//----- (00404E60) --------------------------------------------------------
int __stdcall IBindStatusCallback_OnDataAvailable(
    FancyDownloaderCallback* a1,
    unsigned int a2,
    int a3,
    int a4,
    STGMEDIUM* a5)
{
    IStream* pstm; // eax
    IStream* stream; // eax
    int v7; // esi
    FancyDownloader* field_14; // ecx
    static char byte_4171C0[4096];

    if ((a2 & 1) != 0 && !a1->stream && a5->tymed == TYMED_ISTREAM)
    {
        pstm = a5->pstm;
        a1->stream = pstm;
        pstm->lpVtbl->AddRef(pstm);
    }
    do
    {
        stream = a1->stream;
        a2 = 0;
        v7 = stream->lpVtbl->Read(stream, byte_4171C0, 4092, (ULONG*)&a2);
        if (a2)
        {
            field_14 = a1->downloader;
            if (field_14)
                FancyDownloaderAppendBuffer(field_14, byte_4171C0, a2);
        }
        if (v7 == (unsigned int)E_PENDING)
            break;
        if (v7 == 1)
            return 0;
    } while (v7 >= 0);
    if (v7 != (unsigned int)E_PENDING)
        return v7;
    return 0;
}
// 404EE0: conditional instruction was optimized away because esi.4<0

//----- (00404F00) --------------------------------------------------------
void __thiscall FancyDownloaderDtor(FancyDownloader* this)
{
    FancyDownloaderRelease(this);
    this->contentLength = 0;
    this->lastModified = 0;
    this->field_48 = 0;
    FancyStrDtor(&this->filename);
    FancyStrDtor(&this->localPath);
    FancyStrDtor(&this->netPath);
}

//----- (00404F70) --------------------------------------------------------
int __stdcall IHttpNegotiate_Release(FancyDownloaderCallback* a1)
{
    return IBindStatusCallback_Release((FancyDownloaderCallback*)((char*)a1 - 4));
}

//----- (00404F80) --------------------------------------------------------
int __stdcall IBindStatusCallback_OnStopBinding(FancyDownloaderCallback* a1, int a2, int a3)
{
    IBinding* binding; // eax
    FancyDownloader* downloader; // edi
    int completed; // eax

    binding = a1->binding;
    if (binding)
        binding->lpVtbl->Release(a1->binding);
    downloader = a1->downloader;
    a1->binding = 0;
    if (downloader)
    {
        if (a2)
        {
            completed = a1->completed;
            downloader->field_58 = 1024;
            if (!completed)
            {
                downloader->stage = 3;
                goto LABEL_9;
            }
        }
        else
        {
            downloader->field_58 = 1024;
        }
        downloader->stage = (FancyDownloaderWriteToFile(downloader) != 0) + 3;
    LABEL_9:
        a1->downloader->callback = 0;
        FancyDownloaderCallbackDtor(a1);
        free(a1);
    }
    return 0;
}

//----- (00405000) --------------------------------------------------------
void __thiscall FancyDownloaderOpen(FancyDownloader* this)
{
    FancyDownloaderCallback* v2; // eax MAPDST
    FancyStr* p_netPath; // edi
    char* buffer; // eax
    char* v6; // eax
    char* v7; // eax
    char* v8; // eax
    IMoniker* urlMoniker; // eax
    IBindCtx* bindCtx; // eax
    IStream* iStream; // eax
    FancyStr lpMultiByteStr; // [esp+14h] [ebp-201Ch] BYREF
    WCHAR WideCharStr[4096]; // [esp+24h] [ebp-200Ch] BYREF
    int v15; // [esp+202Ch] [ebp-4h]

    FancyDownloaderRelease(this);
    FancyStrCtor(&lpMultiByteStr);
    v15 = 0;
    v2 = (FancyDownloaderCallback*)operator new(0x28u);
    LOBYTE(v15) = 1;
    if (v2)
    {
        v2->IBindStatusCallback::lpVtbl = &stru_412584;
        v2->FancyDownloaderSubCallback::IHttpNegotiate::lpVtbl = &stru_412570;
        FancyStrCtor(&v2->url);
        v2->binding = 0;
        v2->stream = 0;
        v2->refCount = 0;
        v2->downloader = this;
        v2->completed = 0;
    }
    else
    {
        v2 = 0;
    }
    LOBYTE(v15) = 0;
    this->callback = v2;
    if (!v2)
        goto LABEL_18;
    p_netPath = &this->netPath;
    if (this->netPath.len < 1 || (buffer = p_netPath->buffer) == 0)
        buffer = emptyString;
    GetPathAndFilenameFromCstr(&lpMultiByteStr, &this->filename, buffer);
    FancyStrSet(&lpMultiByteStr, (const char**)&this->netPath.buffer);
    FancyStrReplace(&lpMultiByteStr, "\\", "/");
    if (lpMultiByteStr.len < 1 || (v6 = lpMultiByteStr.buffer) == 0)
        v6 = emptyString;
    v7 = TrimPath(v6);
    FancyStrFromCStr(&lpMultiByteStr, v7);
    if (FancyStrStartsWith(&lpMultiByteStr, "www."))
        FancyStrInsertCStrAt(&lpMultiByteStr, 0, "http://");
    FancyStrSet(&this->callback->url, (const char**)&lpMultiByteStr.buffer);
    if (lpMultiByteStr.len < 1 || (v8 = lpMultiByteStr.buffer) == 0)
        v8 = emptyString;
    MultiByteToWideChar(0, 0, v8, -1, WideCharStr, 0x2000);
    if (CreateURLMoniker(0, WideCharStr, &this->urlMoniker) >= 0
        && CreateAsyncBindCtx(0, this->callback, 0, &this->bindCtx) >= 0)
    {
        this->urlMoniker->lpVtbl->BindToStorage(this->urlMoniker, this->bindCtx, 0, CLSID_IStream, (void**)&this->iStream);
        this->stage = 1;
        v15 = -1;
        FancyStrDtor(&lpMultiByteStr);
    }
    else
    {
    LABEL_18:
        free(this->callback);
        urlMoniker = this->urlMoniker;
        this->callback = 0;
        if (urlMoniker)
        {
            urlMoniker->lpVtbl->Release(urlMoniker);
            this->urlMoniker = 0;
        }
        bindCtx = this->bindCtx;
        if (bindCtx)
        {
            bindCtx->lpVtbl->Release(this->bindCtx);
            this->bindCtx = 0;
        }
        iStream = this->iStream;
        if (iStream)
        {
            iStream->lpVtbl->Release(this->iStream);
            this->iStream = 0;
        }
        v15 = -1;
        FancyStrDtor(&lpMultiByteStr);
    }
}

//----- (00404770) --------------------------------------------------------
time_t __cdecl SystemTimeToTime_t(SYSTEMTIME SystemTime)
{
    struct _FILETIME FileTime; // [esp+0h] [ebp-3Ch] BYREF
    struct _SYSTEMTIME v3; // [esp+8h] [ebp-34h] BYREF
    struct tm v4; // [esp+18h] [ebp-24h] BYREF

    if (!SystemTimeToFileTime(&SystemTime, &FileTime)
        || !FileTimeToLocalFileTime(&FileTime, &FileTime)
        || !FileTimeToSystemTime(&FileTime, &v3))
    {
        return 0;
    }
    v4.tm_sec = v3.wSecond;
    v4.tm_min = v3.wMinute;
    v4.tm_hour = v3.wHour;
    v4.tm_mday = v3.wDay;
    v4.tm_mon = v3.wMonth - 1;
    v4.tm_year = v3.wYear - 1900;
    v4.tm_isdst = -1;
    return mktime(&v4);
}

//----- (00405FD0) --------------------------------------------------------
char* __cdecl TrimPath(const char* a1)
{
    char* v1; // ebx
    char* i; // esi
    char v3; // al
    char* v4; // ecx
    int v5; // eax
    int v6; // eax
    char v7; // cl
    int v8; // eax
    char v9; // cl
    char v11[260]; // [esp+Ch] [ebp-104h] BYREF
    static char byte_4185F0[264]; // weak

    strcpy(v11, a1);
    strcpy(byte_4185F0, a1);
    v1 = v11;
LABEL_2:
    for (i = v1; *i; ++i)
    {
        if (*(_WORD*)i == '..')
        {
            v3 = i[2];
            if (v3 == '\\' || v3 == '/')
            {
                v4 = i - 2;
                v5 = i - 2 - v1;
                if (v5 >= 1)
                {
                    do
                    {
                        if (*v4 == '\\')
                            break;
                        if (*v4 == '/')
                            break;
                        --v5;
                        --v4;
                    } while (v5 > 0);
                    if (v5 < 1)
                        ++i;
                    *v4 = 0;
                    v6 = 0;
                    do
                    {
                        v7 = v11[v6];
                        byte_4185F0[v6++] = v7;
                    } while (v7);
                    strcat(byte_4185F0, i + 2);
                    v8 = 0;
                    do
                    {
                        v9 = byte_4185F0[v8];
                        v11[v8++] = v9;
                    } while (v9);
                }
                else
                {
                    v1 = i + 3;
                }
                goto LABEL_2;
            }
        }
    }
    return byte_4185F0;
}
// 406037: conditional instruction was optimized away because eax.4>=1
// 405FD0: using guessed type char var_104[260];

