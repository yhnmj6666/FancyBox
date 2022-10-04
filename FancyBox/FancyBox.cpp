#define _CRT_SECURE_NO_WARNINGS

#include "FancyBox.hpp"
#include "FancyDownloader.hpp"
#include "FancyBoxFile.hpp"
#include "FancyBoxFileContent.hpp"
#include "FancyCab.hpp"
#include "FancyLinedText.hpp"

#include "common.hpp"

#include <stdlib.h>

#define __thiscall __fastcall
#define this _this

FancyBox fancyBox = {};
char aFcrunerExe[] = "fcruner.exe"; // idb

//----- (004016C0) --------------------------------------------------------
HWND __thiscall GetMostParentWindow(FancyBox* this)
{
    HWND result; // eax
    HWND hWnd; // esi
    HWND i; // eax

    result = (HWND)IsWindow(this->hWnd);
    if (result)
    {
        hWnd = this->hWnd;
        for (i = GetParent(hWnd); i; i = GetParent(i))
            hWnd = i;
        return hWnd;
    }
    return result;
}

//----- (004017E0) --------------------------------------------------------
HMODULE __thiscall FancyBoxFreeObjsys(FancyBox* this)
{
    void(__cdecl * fStdCmdFancyBox)(int, char*); // eax
    HMODULE result; // eax

    fStdCmdFancyBox = this->fStdCmdFancyBox;
    if (fStdCmdFancyBox)
        fStdCmdFancyBox(3, 0);
    result = this->hObjsys;
    if (this->hObjsys)
        result = (HMODULE)FreeLibrary(this->hObjsys);
    this->fStdCmdFancyBox = 0;
    this->hObjsys = 0;
    this->objsysReady = 0;
    return result;
}

//----- (00401820) --------------------------------------------------------
void __thiscall FancyBoxSaveCmdline(FancyBox* this, char* a2)
{
    char* v3; // eax
    char v4; // al
    char* v5; // eax
    FancyStr* p_strCommandC; // esi
    char* v7; // eax
    bool v8; // cc
    char* v9; // eax
    char* v10; // eax
    unsigned int v11; // esi
    int v12; // eax
    char* v13; // ecx
    unsigned int v14; // esi
    int v15; // eax
    char* v16; // ecx
    char* buffer; // eax
    FancyStr v18; // [esp+Ch] [ebp-24h] BYREF
    FancyStr v19; // [esp+18h] [ebp-18h] BYREF
    int v20; // [esp+2Ch] [ebp-4h]

    FancyStrFromCStr(&this->cmdLine, a2);
    FancyStrCtor(&v19);
    v20 = 0;
    FancyStrCtor(&v18);
    LOBYTE(v20) = 1;
    FancyStrFromCStr(&v19, a2);
    if (this->strCommandRaw.buffer)
        free(this->strCommandRaw.buffer);
    this->strCommandRaw.buffer = 0;
    this->strCommandRaw.len = 0;
    this->strCommandRaw.capacity = 0;
    while (FancyStrSubstring(&v19, &v18, ' ', 0, 0))
    {
        if (v18.len > 3)
        {
            if (FancyStrCharAt(&v18, 0) == '-')
            {
                switch (FancyStrCharAt(&v18, 1))
                {
                case 'C':
                case 'c':
                    if (v18.len < 1 || (buffer = v18.buffer) == 0)
                        buffer = emptyString;
                    p_strCommandC = &this->strCommandC;
                    v7 = buffer + 3;
                    goto LABEL_18;
                case 'D':
                case 'd':
                    if (v18.len < 1 || (v3 = v18.buffer) == 0)
                        v3 = emptyString;
                    FancyStrFromCStr(&this->strCommandDll, v3 + 3);
                    break;
                case 'F':
                case 'f':
                    v14 = FancyStrCharAt(&v18, 2) - '1';
                    if (v14 <= 2)
                    {
                        v15 = this->field_CB8[v14];
                        if (v15 < 16)
                        {
                            if (v18.len < 1 || (v16 = v18.buffer) == 0)
                                v16 = emptyString;
                            strcpy((char*)&this->field_6A8 + 512 * v14 + 32 * v15 + 1, v16 + 4);
                            ++this->field_CB8[v14];
                        }
                    }
                    break;
                case 'I':
                case 'i':
                    if (v18.len < 1 || (v10 = v18.buffer) == 0)
                        v10 = emptyString;
                    FancyStrFromCStr(&this->strCommandI, v10 + 3);
                    break;
                case 'S':
                case 's':
                    v4 = FancyStrCharAt(&v18, 2);
                    if (v4 == ':')
                    {
                        v8 = v18.len < 1;
                        this->field_68 = 1;
                        if (v8 || (v9 = v18.buffer) == 0)
                            v9 = emptyString;
                        FancyStrFromCStr(&this->strCommandSystem, v9 + 3);
                        FancyStrTrimTailChar(&this->strCommandSystem, '/');
                        FancyStrAppendCStr(&this->strCommandSystem, "/");
                    }
                    else if ((v4 == 'V' || v4 == 'v') && v18.len > 4)
                    {
                        v5 = v18.buffer;
                        if (!v18.buffer)
                            v5 = emptyString;
                        p_strCommandC = &this->strCommandSV;
                        v7 = v5 + 4;
                    LABEL_18:
                        FancyStrFromCStr(p_strCommandC, v7);
                        FancyStrTrimTailChar(p_strCommandC, '\\');
                    }
                    break;
                case 'W':
                case 'w':
                    v11 = FancyStrCharAt(&v18, 2) - '1';
                    if (v11 <= 2)
                    {
                        v12 = this->field_CAC[v11];
                        if (v12 < 16)
                        {
                            if (v18.len < 1 || (v13 = v18.buffer) == 0)
                                v13 = emptyString;
                            strcpy(&this->field_A8 + 512 * v11 + 32 * v12 + 1, v13 + 4);
                            ++this->field_CAC[v11];
                        }
                    }
                    break;
                default:
                    break;
                }
            }
            else
            {
                if (this->strCommandRaw.len > 0)
                    FancyStrAppendCStr(&this->strCommandRaw, ",");
                FancyStrAppend(&this->strCommandRaw, &v18);
            }
        }
    }
    LOBYTE(v20) = 0;
    FancyStrDtor(&v18);
    v20 = -1;
    FancyStrDtor(&v19);
}
// 40193C: conditional instruction was optimized away because %var_20.4>=5

//----- (00401B90) --------------------------------------------------------
void __thiscall FancyBoxNotifyObjsys(FancyBox* this)
{
    void(__cdecl * fStdCmdFancyBox)(int, char*); // eax

    fStdCmdFancyBox = this->fStdCmdFancyBox;
    if (fStdCmdFancyBox)
        fStdCmdFancyBox(10, 0);
}

//----- (00402090) --------------------------------------------------------
char* __thiscall sub_402090(FancyBox* this, unsigned int a2)
{
    char* buffer; // ecx
    FancyStr v5; // [esp+8h] [ebp-24h] BYREF
    FancyStr v6; // [esp+14h] [ebp-18h] BYREF
    int v7; // [esp+28h] [ebp-4h]
    static char byte_417178[32]; // weak
    
    if (a2 > 2)
        return 0;
    if (this->field_CAC[a2] >= 1)
    {
        strcpy(byte_417178, (const char*)&this->field_A8 + 512 * a2 + 32 * (rand() % this->field_CAC[a2]) + 1);
        return byte_417178;
    }
    if (a2)
        return 0;
    FancyStrCtor(&v6);
    v7 = 0;
    FancyStrCtor(&v5);
    LOBYTE(v7) = 1;
    FancyStrSet(&v6, (const char**)&this->strCommandSystem.buffer);
    FancyStrRemove(&v6, 0, 7);
    FancyStrSubstring(&v6, &v5, '/', 0, 0);
    if (v5.len < 1 || (buffer = v5.buffer) == 0)
        buffer = emptyString;
    strcpy(byte_417178, buffer);
    LOBYTE(v7) = 0;
    FancyStrDtor(&v5);
    v7 = -1;
    FancyStrDtor(&v6);
    return byte_417178;
}

//----- (004021D0) --------------------------------------------------------
char* __thiscall sub_4021D0(FancyBox* this, unsigned int a2)
{
    static char byte_417198[32]; // weak
    if (a2 > 2 || this->field_CB8[a2] < 1)
        return 0;
    strcpy(byte_417198, (const char*)&this->field_6A8 + 512 * a2 + 32 * (rand() % this->field_CB8[a2]) + 1);
    return byte_417198;
}

//----- (00402790) --------------------------------------------------------
void __thiscall FancyBoxCtor(FancyBox* this)
{
    FancyStr* p_strCommandDll; // ebp
    char* String; // eax
    char aObjsysDll[11] = "objsys.dll"; // weak

    p_strCommandDll = &this->strCommandDll;
    FancyStrCtor(&this->strCommandDll);
    FancyStrCtor(&this->strCommandRaw);
    FancyStrCtor(&this->field_2C);
    FancyStrCtor(&this->field_38);
    FancyStrCtor(&this->objsysDllPath);
    FancyStrCtor(&this->field_50);
    FancyStrCtor(&this->strCommandSystem);
    FancyStrCtor(&this->cmdLine);
    FancyStrCtor(&this->strCommandSV);
    FancyStrCtor(&this->strCommandC);
    FancyStrCtor(&this->strCommandI);
    FancyStrCtor(&this->updateMessage);
    this->hObjsys = 0;
    this->fStdInitFancyBox = 0;
    this->fStdCmdFancyBox = 0;
    this->hWnd = 0;
    this->objsysReady = 0;
    InitialzeHexMap();
    FancyStrFromCStr(p_strCommandDll, aObjsysDll);
    String = (char*)FancyRegReadString("fcbox2", "syshomeadd", (BYTE*)"http://fcbox/download/system");
    FancyStrFromCStr(&this->strCommandSystem, String);
    FancyStrTrimTailChar(&this->strCommandSystem, '/');
    FancyStrAppendCStr(&this->strCommandSystem, "/");
    this->field_74 = 0;
    this->field_A8 = 0;
    this->field_68 = 0;
    this->field_70 = 5;
    this->field_CAC[0] = 0;
    this->field_CAC[1] = 0;
    this->field_CAC[2] = 0;
    this->field_CB8[0] = 0;
    this->field_CB8[1] = 0;
    this->field_CB8[2] = 0;
    this->field_CD0 = 0;
}

//----- (00402900) --------------------------------------------------------
void __thiscall sub_402900(FancyBox* this, FancyStr* a2)
{
    signed int v3; // edi
    FancyStr* v4; // eax
    BOOL v5; // esi
    FancyStr* v6; // ebp
    char* v7; // esi
    FancyDownloader* v8; // eax
    FancyDownloader* v9; // esi
    int v10; // eax
    int v11; // ebp
    int v12; // ecx
    FancyDownloader* v13; // eax
    int v14; // ebx
    int i; // esi
    FancyDownloader* v16; // edi
    char* buffer; // eax
    char* v18; // eax
    char v19; // [esp+Fh] [ebp-81h]
    int v20; // [esp+10h] [ebp-80h]
    FancyStr v21; // [esp+18h] [ebp-78h] BYREF
    FancyStr v22; // [esp+24h] [ebp-6Ch] BYREF
    FancyStr v23; // [esp+30h] [ebp-60h] BYREF
    FancyDownloader* v24[3]; // [esp+3Ch] [ebp-54h] BYREF
    FancyStr lpFileName; // [esp+48h] [ebp-48h] BYREF
    FancyStr v26; // [esp+54h] [ebp-3Ch] BYREF
    FancyStr v27[3]; // [esp+60h] [ebp-30h] BYREF
    int v28; // [esp+8Ch] [ebp-4h]

    FancyStrCtor(&v23);
    v3 = 0;
    v28 = 0;
    FancyStrSetStr(&v22, (const char**)&a2->buffer);
    LOBYTE(v28) = 1;
    FancyStrToLower(&v22);
    v4 = FancyStrSubString(&v22, &v26, 0, 7);
    LOBYTE(v28) = 2;
    v5 = FancyStrNotEqual(v4, "http://");
    LOBYTE(v28) = 1;
    FancyStrDtor(&v26);
    if (v5)
    {
        LOBYTE(v28) = 0;
        FancyStrDtor(&v22);
        v28 = -1;
        FancyStrDtor(&v23);
    }
    else
    {
        FancyStrSubstring(&v22, &v23, ' ', 0, 0);
        FancyStrSet(&v22, (const char**)&v23.buffer);
        FancyStrSubstring(&v22, &v23, ',', 0, 0);
        FancyStrSet(&v22, (const char**)&v23.buffer);
        FancyStrSubstring(&v22, &v23, '+', 0, 0);
        FancyStrSet(&v22, (const char**)&v23.buffer);
        FancyStrSubstring(&v22, &v23, '?', 0, 0);
        FancyStrSet(&v22, (const char**)&v23.buffer);
        v19 = 0;
        FancyStrCtor(&lpFileName);
        LOBYTE(v28) = 3;
        FancyStrCtor(&v21);
        LOBYTE(v28) = 4;
        FancyStrCtor(&v26);
        LOBYTE(v28) = 5;
        vector_constructor((char*)v27, 0xCu, 3, (void(__thiscall*)(void*))FancyStrCtor, (void(__thiscall*)(void*))FancyStrDtor);
        memset(v24, 0, sizeof(v24));
        LOBYTE(v28) = 6;
        v20 = -1;
        FancyStrSet(&lpFileName, (const char**)&this->field_2C.buffer);
        FancyStrAppendCStr(&lpFileName, "checkfile.dat");
        v6 = v27;
        do
        {
            v7 = sub_4021D0(this, v3);
            if (v7)
            {
                FancyStrSet(&v21, (const char**)&v22.buffer);
                FancyStrRemove(&v21, 0, 7);
                FancyStrSubstring(&v21, &v26, '/', 0, 0);
                FancyStrInsert(&v21, 0, '/');
                FancyStrInsertCStrAt(&v21, 0, v7);
                FancyStrInsertCStrAt(&v21, 0, "http://");
                FancyStrFromCStr(v6, v7);
                v8 = (FancyDownloader*)operator new(0x60u);
                LOBYTE(v28) = 7;
                if (v8)
                    v9 = FancyDownloaderCtor(v8);
                else
                    v9 = 0;
                LOBYTE(v28) = 6;
                v24[v3] = v9;
                FancyStrSet(&v9->netPath, (const char**)&v21.buffer);
                FancyStrSet(&v9->localPath, (const char**)&lpFileName.buffer);
                v9->field_48 = 0;
                FancyDownloaderOpen(v9);
            }
            ++v3;
            ++v6;
        } while (v3 < 3);
        v10 = 0;
        while (!v24[v10])
        {
            if (++v10 >= 3)
                goto LABEL_38;
        }
        if (v10 != -1)
        {
            v11 = 1;
            while (1)
            {
                v12 = 0;
                while (1)
                {
                    v13 = v24[v12];
                    if (v13)
                    {
                        if (v13->stage == 2 || v13->stage == 4)
                            break;
                    }
                    if (++v12 >= 3)
                    {
                        v14 = v20;
                        goto LABEL_26;
                    }
                }
                v14 = v12;
                v20 = v12;
                v19 = 1;
                for (i = 0; i < 3; ++i)
                {
                    v16 = v24[i];
                    if (v16)
                    {
                        FancyDownloaderDtor(v24[i]);
                        free(v16);
                    }
                    v24[i] = 0;
                }
            LABEL_26:
                if (!processWindowsMessages() || v11 > 100)
                    break;
                Sleep(6u);
                ++v11;
                if (v14 != -1)
                {
                    v14 = v20;
                    break;
                }
            }
            if (v19)
            {
                FancyStrSet(&v21, (const char**)&a2->buffer);
                FancyStrRemove(&v21, 0, 7);
                FancyStrSubstring(&v21, &v26, 47, 0, 0);
                FancyStrInsert(&v21, 0, 47);
                if (v27[v14].len < 1 || (buffer = v27[v14].buffer) == 0)
                    buffer = emptyString;
                FancyStrInsertCStrAt(&v21, 0, buffer);
                FancyStrInsertCStrAt(&v21, 0, "http://");
                FancyStrSet(a2, (const char**)&v21.buffer);
                if (lpFileName.len < 1 || (v18 = lpFileName.buffer) == 0)
                    v18 = emptyString;
                DeleteFileA(v18);
            }
        }
    LABEL_38:
        LOBYTE(v28) = 5;
        vector_destructor((char*)v27, 0xCu, 3, (void(__thiscall*)(void*))FancyStrDtor);
        LOBYTE(v28) = 4;
        FancyStrDtor(&v26);
        LOBYTE(v28) = 3;
        FancyStrDtor(&v21);
        LOBYTE(v28) = 1;
        FancyStrDtor(&lpFileName);
        LOBYTE(v28) = 0;
        FancyStrDtor(&v22);
        v28 = -1;
        FancyStrDtor(&v23);
    }
}

//----- (00402D70) --------------------------------------------------------
int __thiscall FancyBoxUpdateSystem(FancyBox* this, HWND hWnd)
{
    char* buffer; // eax
    FancyStr* p_strCommandSystem; // ebx
    FancyStr* p_updateMessage; // esi
    char* v7; // esi
    char* v8; // eax
    signed int v9; // edi
    FancyStr* v10; // ebp
    char* v11; // esi
    FancyDownloader* v12; // eax
    FancyDownloader* v13; // esi
    int v14; // ecx
    FancyDownloader* v15; // eax
    int i; // edi
    FancyDownloader* v17; // esi
    FancyDownloader* v18; // eax
    int j; // edi
    void* v20; // esi
    char* v21; // eax
    char* v22; // eax
    int v23; // esi
    int v24; // edi
    int v25; // eax
    char* Line; // eax
    unsigned int v28; // eax
    char* v29; // ecx
    int v30; // esi
    char* v31; // eax
    unsigned int v32; // eax
    char* v33; // ecx
    int Integer; // edi
    int v35; // ebp
    char* v36; // eax
    char* v37; // eax
    char* v38; // esi
    char* v39; // ecx
    char* v40; // eax
    int v41; // ebx
    int v42; // ebp
    char* v43; // eax
    char* v44; // eax
    FancyStr* v45; // esi
    char* v46; // esi
    char* v47; // edi
    char* v48; // eax
    char* v49; // eax
    char* v50; // eax
    int v51; // eax
    WPARAM v52; // edi
    char* v53; // esi
    FancyStr* p_strCommandRaw; // esi
    int v55; // ebx
    char* v56; // eax
    char* v57; // eax
    char* v58; // eax
    char* v59; // eax
    char* v60; // esi
    char* v61; // ecx
    time_t v62; // eax
    char* v63; // eax
    FancyStr* v64; // esi
    char* v65; // eax
    char v66; // [esp+Fh] [ebp-105h]
    FancyStr lpFileName; // [esp+10h] [ebp-104h] BYREF
    int v68; // [esp+1Ch] [ebp-F8h]
    FancyBox* v69; // [esp+20h] [ebp-F4h] MAPDST
    FancyStr v70; // [esp+24h] [ebp-F0h] BYREF
    FancyStr v71; // [esp+30h] [ebp-E4h] BYREF
    FancyStr v72; // [esp+3Ch] [ebp-D8h] BYREF
    FancyStr arglist; // [esp+48h] [ebp-CCh] BYREF
    FancyDownloader* v74[3]; // [esp+54h] [ebp-C0h] BYREF
    FancyStr v75; // [esp+54h] [ebp-C0h] FORCED BYREF
    FancyStr v76; // [esp+60h] [ebp-B4h] BYREF
    FancyStr v77; // [esp+6Ch] [ebp-A8h] BYREF
    FancyDownloader* v78; // [esp+78h] [ebp-9Ch]
    int v79; // [esp+78h] [ebp-9Ch] FORCED
    FancyLinedText v80; // [esp+7Ch] [ebp-98h] BYREF
    FancyStr v81; // [esp+8Ch] [ebp-88h] BYREF
    FancyStr v82; // [esp+98h] [ebp-7Ch] BYREF
    FancyUpdateDialog v83; // [esp+A4h] [ebp-70h] BYREF
    FancyStr v84; // [esp+D8h] [ebp-3Ch] BYREF
    FancyStr v85[3]; // [esp+E4h] [ebp-30h] BYREF
    int v86; // [esp+110h] [ebp-4h]
    char aFc2infoDat[12] = "fc2info.dat"; // weak

    v69 = this;
    FancyStrCtor(&v76);
    v86 = 0;
    FancyStrCtor(&lpFileName);
    LOBYTE(v86) = 1;
    FancyStrCtor(&arglist);
    LOBYTE(v86) = 2;
    FancyUpdateDialogCtor(&v83);
    LOBYTE(v86) = 3;
    fancyBox.updateDialog = &v83;
    fancyBox.field_CE0 = 1;
    fancyBox.field_CD8 = 0;
    FancyStrSet(&v76, (const char**)&this->field_2C.buffer);
    FancyStrSet(&lpFileName, (const char**)&v76.buffer);
    FancyStrAppendCStr(&lpFileName, aFc2infoDat);
    if (lpFileName.len < 1 || (buffer = lpFileName.buffer) == 0)
        buffer = emptyString;
    if (CompareTime(buffer, this->field_70, 0, 0))
    {
        LOBYTE(v86) = 2;
        FancyUpdateDialogRelease(&v83);
        LOBYTE(v86) = 1;
        FancyStrDtor(&arglist);
        LOBYTE(v86) = 0;
        FancyStrDtor(&lpFileName);
        v86 = -1;
        FancyStrDtor(&v76);
        return 1;
    }
    p_strCommandSystem = &this->strCommandSystem;
    FancyStrSet(&arglist, (const char**)&this->strCommandSystem.buffer);
    FancyStrAppendCStr(&arglist, aFc2infoDat);
    FancyUpdateDialogCreate(&v83, this->hInstance, 0, this->field_CD0);
    p_updateMessage = &this->updateMessage;
    FancyStrFromCStr(p_updateMessage, "Check system info\r\nWaiting...");
    if (p_updateMessage->len < 1 || (v7 = p_updateMessage->buffer) == 0)
        v7 = emptyString;
    FancyUpdateDialogSetDownloadingText(fancyBox.updateDialog, v7, 1);
    FancyUpdateDialogSetUpdatePercentage(fancyBox.updateDialog, 0);
    if (lpFileName.len < 1 || (v8 = lpFileName.buffer) == 0)
        v8 = emptyString;
    FancyBoxChangeAndCreateDirectory(v8);
    v66 = 0;
    FancyStrCtor(&v82);
    LOBYTE(v86) = 4;
    FancyStrCtor(&v84);
    LOBYTE(v86) = 5;
    vector_constructor((char*)v85, 0xCu, 3, (void(__thiscall*)(void*))FancyStrCtor, (void(__thiscall*)(void*))FancyStrDtor);
    memset(v74, 0, sizeof(v74));
    LOBYTE(v86) = 6;
    v68 = -1;
    v9 = 0;
    v10 = v85;
    do
    {
        v11 = sub_402090(v69, v9);
        if (v11)
        {
            FancyStrSet(&v82, (const char**)&p_strCommandSystem->buffer);
            FancyStrRemove(&v82, 0, 7);
            FancyStrSubstring(&v82, &v84, 47, 0, 0);
            FancyStrInsert(&v82, 0, 47);
            FancyStrInsertCStrAt(&v82, 0, v11);
            FancyStrInsertCStrAt(&v82, 0, "http://");
            FancyStrSet(v10, (const char**)&v82.buffer);
            v12 = (FancyDownloader*)operator new(0x60u);
            v78 = v12;
            LOBYTE(v86) = 7;
            if (v12)
                v13 = FancyDownloaderCtor(v12);
            else
                v13 = 0;
            LOBYTE(v86) = 6;
            v74[v9] = v13;
            FancyStrAppendCStr(&v82, aFc2infoDat);
            FancyStrSet(&v13->netPath, (const char**)&v82.buffer);
            FancyStrSet(&v13->localPath, (const char**)&lpFileName.buffer);
            v13->field_48 = 0;
            FancyDownloaderOpen(v13);
        }
        ++v9;
        ++v10;
    } while (v9 < 3);
    while (1)
    {
        v14 = 0;
        while (1)
        {
            v15 = v74[v14];
            if (v15)
            {
                if (v15->stage == 2 || v15->stage == 4)
                    break;
            }
            if (++v14 >= 3)
                goto LABEL_35;
        }
        v68 = v14;
        for (i = 0; i < 3; ++i)
        {
            v17 = v74[i];
            if (v17 && v68 != i)
            {
                FancyDownloaderDtor(v74[i]);
                free(v17);
                v74[i] = 0;
            }
        }
    LABEL_35:
        if (v83.field_24 || !processWindowsMessages())
            break;
        Sleep(6u);
        while (v68 != -1)
        {
            v18 = v74[v68];
            if (v18->stage != 2)
            {
                if (v18->stage != 4)
                    goto LABEL_35;
                v66 = 1;
                for (j = 0; j < 3; ++j)
                {
                    v20 = (void*)*((_DWORD*)&v75.buffer + j);
                    if (v20)
                    {
                        FancyDownloaderDtor(v74[j]);
                        free(v20);
                        *((_DWORD*)&v75.buffer + j) = 0;
                    }
                }
                FancyStrSet(&v69->strCommandSystem, (const char**)&v85[v68].buffer);
                goto LABEL_43;
            }
        }
    }
LABEL_43:
    LOBYTE(v86) = 5;
    vector_destructor((char*)v85, 0xCu, 3, (void(__thiscall*)(void*))FancyStrDtor);
    LOBYTE(v86) = 4;
    FancyStrDtor(&v84);
    LOBYTE(v86) = 3;
    FancyStrDtor(&v82);
    if (!v66)
    {
        if (!v83.field_24)
        {
            if (arglist.len < 1 || (v21 = arglist.buffer) == 0)
                v21 = emptyString;
            FancyBoxHideAndErrorMessageBox(&v83, hWnd, "Download system info failed\r\n%s", v21);
        }
        goto LABEL_49;
    }
    FancyLinedTextCtor(&v80);
    LOBYTE(v86) = 8;
    if (lpFileName.len < 1 || (v22 = lpFileName.buffer) == 0)
        v22 = emptyString;
    if (!FancyLinedTextFillFromPath(&v80, v22))
    {
        FancyBoxHideAndErrorMessageBox(&v83, hWnd, "Can't read system info!");
        LOBYTE(v86) = 3;
        FancyLinedTextDtor(&v80);
        goto LABEL_49;
    }
    v23 = 0;
    FancyStrCtor(&v70);
    LOBYTE(v86) = 9;
    FancyStrCtor(&v72);
    LOBYTE(v86) = 10;
    FancyStrCtor(&v71);
    LOBYTE(v86) = 11;
    FancyStrCtor(&v81);
    LOBYTE(v86) = 12;
    FancyStrCtor(&v77);
    LOBYTE(v86) = 13;
    v24 = 0;
    v25 = FancyLinedTextSize(&v80);
    if (v25 > 0)
    {
        do
        {
            if (v83.field_24)
                goto LABEL_159;
            Line = FancyLinedTextGetLine(&v80, v24);
            FancyStrFromCStr(&v70, Line);
            if (v70.len >= 3)
            {
                FancyStrSubstring(&v70, &v72, 44, 0, 0);
                if (!v69->field_A8)
                    goto LABEL_63;
                v28 = strlen(aFcrunerExe);
                if (v72.len < 1 || (v29 = v72.buffer) == 0)
                    v29 = emptyString;
                if (_strnicmp(v29, aFcrunerExe, v28 - 3))
                {
                LABEL_63:
                    v23 += FancyStrGetInteger(&v70, 0, ',');
                    FancyStrGetInteger(&v70, 0, ';');
                }
            }
            ++v24;
        } while (v24 < FancyLinedTextSize(&v80));
    }
    fancyBox.field_CD4 = v23;
    FancyUpdateDialogSetUpdatePercentage(fancyBox.updateDialog, 5u);
    v30 = 0;
    v68 = 0;
    v79 = 0;
    if (FancyLinedTextSize(&v80) <= 0)
    {
    LABEL_118:
        fancyBox.field_CE0 = 0;
        v52 = 95;
        FancyUpdateDialogSetDownloadPercentage(fancyBox.updateDialog, 100u);
        FancyUpdateDialogSetUpdatePercentage(fancyBox.updateDialog, 95u);
        if (v68 > 0)
            Sleep(0x1Eu);
        if (v69->strCommandRaw.len)
        {
            FancyStrFromCStr(&v69->updateMessage, "Check script file...");
            if (v69->updateMessage.len < 1 || (v53 = v69->updateMessage.buffer) == 0)
                v53 = emptyString;
            FancyUpdateDialogSetDownloadingText(&v83, v53, 0);
            FancyStrFromCStr(&v77, emptyString);
            if (v69->strCommandRaw.len)
            {
                p_strCommandRaw = &v69->strCommandRaw;
                do
                {
                    v55 = FancyStrFind(p_strCommandRaw, "?", 0);
                    if (FancyStrFind(p_strCommandRaw, ",", 0) <= v55)
                    {
                        FancyStrSubstring(p_strCommandRaw, &v70, 44, 0, 0);
                    }
                    else
                    {
                        FancyStrSet(&v70, (const char**)&p_strCommandRaw->buffer);
                        if (p_strCommandRaw->buffer)
                            free(p_strCommandRaw->buffer);
                        p_strCommandRaw->buffer = 0;
                        p_strCommandRaw->len = 0;
                        p_strCommandRaw->capacity = 0;
                    }
                    sub_402900(v69, &v70);
                    FancyStrAppend(&v77, &v70);
                    FancyStrAppendCStr(&v77, ",");
                    v52 += 2;
                    FancyUpdateDialogSetUpdatePercentage(fancyBox.updateDialog, v52);
                } while (v69->strCommandRaw.len);
            }
            FancyStrTrimTailChar(&v77, 44);
            FancyStrSet(&v69->strCommandRaw, (const char**)&v77.buffer);
        }
        Sleep(0x1Eu);
        FancyUpdateDialogSetUpdatePercentage(fancyBox.updateDialog, 100u);
        v64 = &v69->updateMessage;
        FancyStrFromCStr(&v69->updateMessage, "Update ok!");
        if (v69->updateMessage.len < 1 || (v65 = v64->buffer) == 0)
            v65 = emptyString;
        FancyUpdateDialogSetDownloadingText(&v83, v65, 0);
        Sleep(0x1Eu);
        LOBYTE(v86) = 12;
        FancyStrDtor(&v77);
        LOBYTE(v86) = 11;
        FancyStrDtor(&v81);
        LOBYTE(v86) = 10;
        FancyStrDtor(&v71);
        LOBYTE(v86) = 9;
        FancyStrDtor(&v72);
        LOBYTE(v86) = 8;
        FancyStrDtor(&v70);
        LOBYTE(v86) = 3;
        FancyLinedTextDtor(&v80);
        LOBYTE(v86) = 2;
        FancyUpdateDialogRelease(&v83);
        LOBYTE(v86) = 1;
        FancyStrDtor(&arglist);
        LOBYTE(v86) = 0;
        FancyStrDtor(&lpFileName);
        v86 = -1;
        FancyStrDtor(&v76);
        return 1;
    }
    while (1)
    {
        if (v83.field_24)
            goto LABEL_159;
        v31 = FancyLinedTextGetLine(&v80, v30);
        FancyStrFromCStr(&v70, v31);
        if (v70.len < 3)
            goto LABEL_117;
        FancyStrSet(&v77, (const char**)&v70.buffer);
        FancyStrSubstring(&v70, &v72, 44, 0, 0);
        if (v69->field_A8)
        {
            v32 = strlen(aFcrunerExe);
            if (v72.len < 1 || (v33 = v72.buffer) == 0)
                v33 = emptyString;
            if (!_strnicmp(v33, aFcrunerExe, v32 - 3))
                goto LABEL_117;
        }
        Integer = FancyStrGetInteger(&v70, 0, ',');
        v35 = FancyStrGetInteger(&v70, 0, ';');
        FancyStrSet(&lpFileName, (const char**)&v76.buffer);
        FancyStrAppend(&lpFileName, &v72);
        FancyStrSet(&v81, (const char**)&lpFileName.buffer);
        if (lpFileName.len < 1 || (v36 = lpFileName.buffer) == 0)
            v36 = emptyString;
        if (!VerifyFileSizeAndTime(v36, v35, Integer))
            break;
    LABEL_91:
        fancyBox.field_CD8 += Integer;
        FancyStrSubstring(&v70, &v71, ',', 0, 0);
        v41 = FancyStrGetInteger(&v70, 0, ',');
        v42 = FancyStrGetInteger(&v70, 0, ',');
        FancyStrSet(&lpFileName, (const char**)&v76.buffer);
        FancyStrAppend(&lpFileName, &v71);
        if (lpFileName.len < 1 || (v43 = lpFileName.buffer) == 0)
            v43 = emptyString;
        if (VerifyFileSizeAndTime(v43, v42, v41))
            goto LABEL_117;
        FancyStrCtor(&v75);
        LOBYTE(v86) = 14;
        if (v71.len < 1 || (v44 = v71.buffer) == 0)
            v44 = emptyString;
        v45 = &v69->updateMessage;
        FancyStrSetVAStr(&v69->updateMessage, "Uncab file %s...", v44);
        if (v45->len < 1 || (v46 = v45->buffer) == 0)
            v46 = emptyString;
        FancyUpdateDialogSetDownloadingText(&v83, v46, 1);
        if (lpFileName.len < 1 || (v47 = lpFileName.buffer) == 0)
            v47 = emptyString;
        if (v81.len < 1 || (v48 = v81.buffer) == 0)
            v48 = emptyString;
        if (!sub_401D30(v47, &v75, v48))
        {
            if (v71.len < 1 || (v57 = v71.buffer) == 0)
                v57 = emptyString;
            FancyBoxHideAndErrorMessageBox(&v83, hWnd, "Uncab %s failed!", v57);
            goto LABEL_158;
        }
        if (lpFileName.len < 1 || (v49 = lpFileName.buffer) == 0)
            v49 = emptyString;
        if (!FancySetFileTime(v49, v42))
        {
            if (v71.len < 1 || (v58 = v71.buffer) == 0)
                v58 = emptyString;
            FancyBoxHideAndErrorMessageBox(&v83, hWnd, "Can't set %s date", v58);
            goto LABEL_158;
        }
        if (lpFileName.len < 1 || (v50 = lpFileName.buffer) == 0)
            v50 = emptyString;
        if (!VerifyFileSizeAndTime(v50, v42, v41))
        {
            if (lpFileName.len < 1 || (v59 = lpFileName.buffer) == 0)
                v59 = emptyString;
            if (VerifyFileSizeAndTime(v59, v42, 0))
            {
                if (v71.len < 1 || (v63 = v71.buffer) == 0)
                    v63 = emptyString;
                FancyBoxHideAndErrorMessageBox(&v83, hWnd, "Check uncab %s length err", v63);
            }
            else
            {
                v60 = emptyString;
                if (lpFileName.len < 1 || (v61 = lpFileName.buffer) == 0)
                    v61 = emptyString;
                if (v71.len >= 1 && v71.buffer)
                    v60 = v71.buffer;
                v62 = GetLastWriteTime(v61);
                FancyBoxHideAndErrorMessageBox(&v83, hWnd, "Check uncab %s date err,%X must be %X", v60, v62, v42);
            }
        LABEL_158:
            LOBYTE(v86) = 13;
            FancyStrDtor(&v75);
            goto LABEL_159;
        }
        ++v68;
        LOBYTE(v86) = 13;
        FancyStrDtor(&v75);
    LABEL_117:
        v30 = ++v79;
        v51 = FancyLinedTextSize(&v80);
        if (v30 >= v51)
            goto LABEL_118;
    }
    if (v72.len < 1 || (v37 = v72.buffer) == 0)
        v37 = emptyString;
    FancyStrSetVAStr(&v69->updateMessage, "Downloading %s...", v37);
    if (v69->updateMessage.len < 1 || (v38 = v69->updateMessage.buffer) == 0)
        v38 = emptyString;
    FancyUpdateDialogSetDownloadingText(&v83, v38, 1);
    FancyBoxHideOrDeactiveWindow(&v83, 1);
    FancyStrSet(&arglist, (const char**)&v69->strCommandSystem.buffer);
    FancyStrAppend(&arglist, &v72);
    if (lpFileName.len < 1 || (v39 = lpFileName.buffer) == 0)
        v39 = emptyString;
    if (arglist.len < 1 || (v40 = arglist.buffer) == 0)
        v40 = emptyString;
    if (sub_405230(v40, v39, v35, Integer, UpdateProgress))
    {
        ++v68;
        goto LABEL_91;
    }
    if (!v83.field_24)
    {
        if (v72.len < 1 || (v56 = v72.buffer) == 0)
            v56 = emptyString;
        FancyBoxHideAndErrorMessageBox(&v83, hWnd, "Can't download %", v56);
    }
LABEL_159:
    LOBYTE(v86) = 12;
    FancyStrDtor(&v77);
    LOBYTE(v86) = 11;
    FancyStrDtor(&v81);
    LOBYTE(v86) = 10;
    FancyStrDtor(&v71);
    LOBYTE(v86) = 9;
    FancyStrDtor(&v72);
    LOBYTE(v86) = 8;
    FancyStrDtor(&v70);
    LOBYTE(v86) = 3;
    FancyLinedTextDtor(&v80);
LABEL_49:
    LOBYTE(v86) = 2;
    FancyUpdateDialogRelease(&v83);
    LOBYTE(v86) = 1;
    FancyStrDtor(&arglist);
    LOBYTE(v86) = 0;
    FancyStrDtor(&lpFileName);
    v86 = -1;
    FancyStrDtor(&v76);
    return 0;
}
// 40316A: conditional instruction was optimized away because %var_105.1==0

//----- (004040A0) --------------------------------------------------------
int __thiscall InitializeCache(FancyBox* this)
{
    HWND hWnd; // esi
    HWND i; // eax
    FancyStr* v5; // edi
    FancyStr* v6; // esi

    EnsureCache(&fancyBox.field_CE8, "system");
    FancyStrSet(&this->field_2C, (const char**)&fancyBox.field_CE8.strFullPath.buffer);
    if (this->field_2C.len >= 3)
    {
        if (this->strCommandSV.len > 1)
        {
            FancyStrAppend(&this->field_2C, &this->strCommandSV);
            FancyStrAppendCStr(&this->field_2C, "\\");
        }
        v5 = &this->field_38;
        FancyStrSet(&this->field_38, (const char**)&this->field_2C.buffer);
        FancyStrSet(&this->objsysDllPath, (const char**)&this->field_38.buffer);
        FancyStrAppend(&this->objsysDllPath, &this->strCommandDll);
        v6 = &this->field_50;
        FancyStrSet(v6, (const char**)&v5->buffer);
        FancyStrAppendCStr(v6, aFcrunerExe);
        return 1;
    }
    else
    {
        FancyBoxErrorMessageBox(this, "Can't create cache dir.\r\nMake sure the disk is not full or write-protected.");
        Sleep(0xC8u);
        if (IsWindow(this->hWnd))
        {
            hWnd = this->hWnd;
            for (i = GetParent(hWnd); i; i = GetParent(i))
                hWnd = i;
            PostMessageA(hWnd, 0x10u, 0, 0);
            return 0;
        }
        else
        {
            PostMessageA(0, 0x10u, 0, 0);
            return 0;
        }
    }
}

//----- (004041A0) --------------------------------------------------------
void __thiscall FancyBoxInitObjsys(FancyBox* this, HINSTANCE a2, HWND hWnd)
{
    HWND v4; // edi
    FancyStr* p_objsysDllPath; // ebp
    int v6; // eax
    char v7; // dl
    char* buffer; // eax
    char* v9; // eax
    char* v10; // eax
    char* v11; // ecx
    bool v12; // cc
    char* v13; // eax
    char* v14; // eax
    char* v15; // eax
    char* v16; // eax
    char* v17; // eax
    char* v18; // eax
    char* v19; // eax
    HWND MostParentWindow; // eax
    int(__cdecl * StdInitFancyBox)(HMODULE, HWND, int, int); // eax
    char* v22; // ebp
    void(__cdecl * StdCmdFancyBox)(int, char*); // eax
    char* v24; // eax
    char* v25; // eax
    char* LastErrorCStr; // [esp-10h] [ebp-148h]
    LONG v27; // [esp-10h] [ebp-148h]
    FancyStr lpFileName; // [esp+4h] [ebp-134h] BYREF
    FancyStr lpExistingFileName; // [esp+10h] [ebp-128h] BYREF
    FancyStr lpPathName; // [esp+1Ch] [ebp-11Ch] BYREF
    char Filename[260]; // [esp+28h] [ebp-110h] BYREF
    int v32; // [esp+134h] [ebp-4h]

    if (!this->objsysReady)
    {
        this->objsysReady = 1;
        if (a2)
            this->hInstance = a2;
        v4 = hWnd;
        if (hWnd)
        {
            this->hWnd = hWnd;
        }
        else
        {
            hWnd = this->hWnd;
            v4 = hWnd;
        }
        if (InitializeCache(this))
        {
            FancyStrCtor(&lpExistingFileName);
            v32 = 0;
            FancyStrCtor(&lpFileName);
            p_objsysDllPath = &this->objsysDllPath;
            LOBYTE(v32) = 1;
            FancyStrSet(&lpExistingFileName, (const char**)&this->objsysDllPath.buffer);
            GetModuleFileNameA(0, Filename, 260u);
            v6 = strlen(Filename);
            if (Filename[v6] != '\\')
            {
                do
                {
                    if (v6 <= 0)
                        break;
                    v7 = Filename[--v6];
                } while (v7 != '\\');
            }
            Filename[v6] = 0;
            FancyStrFromCStr(&lpFileName, Filename);
            FancyStrAppendCStr(&lpFileName, "\\");
            FancyStrFromCStr(&lpFileName, Filename);
            FancyStrAppendCStr(&lpFileName, "\\");
            FancyStrAppend(&lpFileName, &this->strCommandDll);
            if (lpFileName.len < 1 || (buffer = lpFileName.buffer) == 0)
                buffer = emptyString;
            if (VerifyFileSizeAndTime(buffer, 0, 0))
                FancyStrSet(&this->objsysDllPath, (const char**)&lpFileName.buffer);
            if (this->field_68)
                goto LABEL_68;
            if (this->objsysDllPath.len < 1 || (v9 = p_objsysDllPath->buffer) == 0)
                v9 = emptyString;
            if (!VerifyFileSizeAndTime(v9, 0, 0))
            {
            LABEL_68:
                if (!FancyBoxUpdateSystem(this, v4))
                    goto LABEL_22;
                FancyStrToLower(&lpExistingFileName);
                FancyStrToLower(&this->objsysDllPath);
                if (FancyStrNotEquals(&lpExistingFileName, &this->objsysDllPath))
                {
                    if (this->objsysDllPath.len < 1 || (v10 = p_objsysDllPath->buffer) == 0)
                        v10 = emptyString;
                    if (lpExistingFileName.len < 1 || (v11 = lpExistingFileName.buffer) == 0)
                        v11 = emptyString;
                    if (!CopyFileA(v11, v10, 0))
                    {
                    LABEL_22:
                        FancyBoxErrorMessageBox(this, "Update System err");
                    LABEL_23:
                        LOBYTE(v32) = 0;
                        FancyStrDtor(&lpFileName);
                        v32 = -1;
                        FancyStrDtor(&lpExistingFileName);
                        return;
                    }
                }
            }
            FancyStrCtor(&lpPathName);
            v12 = this->objsysDllPath.len < 1;
            LOBYTE(v32) = 2;
            if (v12 || (v13 = p_objsysDllPath->buffer) == 0)
                v13 = emptyString;
            GetPathAndFilenameFromCstr(&lpPathName, &lpFileName, v13);
            GetCurrentDirectoryA(0x104u, Filename);
            if (lpPathName.len < 1 || (v14 = lpPathName.buffer) == 0)
                v14 = emptyString;
            SetCurrentDirectoryA(v14);
            if (this->objsysDllPath.len < 1 || (v15 = p_objsysDllPath->buffer) == 0)
                v15 = emptyString;
            this->hObjsys = LoadLibraryA(v15);
            SetCurrentDirectoryA(Filename);
            if (!this->hObjsys)
            {
                if (!FancyBoxUpdateSystem(this, hWnd))
                {
                    FancyBoxErrorMessageBox(this, "Update System err");
                    this->objsysReady = 0;
                    LOBYTE(v32) = 1;
                    FancyStrDtor(&lpPathName);
                    goto LABEL_23;
                }
                if (lpPathName.len < 1 || (v16 = lpPathName.buffer) == 0)
                    v16 = emptyString;
                SetCurrentDirectoryA(v16);
                v17 = FancyStrIsEmpty(&this->objsysDllPath);
                this->hObjsys = LoadLibraryA(v17);
                SetCurrentDirectoryA(Filename);
                if (!this->hObjsys)
                {
                    LastErrorCStr = GetLastErrorCStr();
                    v18 = FancyStrIsEmpty(&this->objsysDllPath);
                    FancyBoxErrorMessageBox(this, "Load %s.\r\n%s", v18, LastErrorCStr);
                    this->objsysReady = 0;
                    LOBYTE(v32) = 1;
                    FancyStrDtor(&lpPathName);
                    goto LABEL_23;
                }
            }
            if (this->strCommandC.len > 2)
            {
                v19 = this->strCommandC.buffer;
                if (!v19)
                    v19 = emptyString;
                v27 = (LONG)v19;
                MostParentWindow = GetMostParentWindow(this);
                SetWindowLongA(MostParentWindow, -21, v27);
            }
            StdInitFancyBox = (int(__cdecl*)(HMODULE, HWND, int, int))GetProcAddress(this->hObjsys, "StdInitFancyBox");
            this->fStdInitFancyBox = StdInitFancyBox;
            if (!StdInitFancyBox)
            {
                if (this->objsysDllPath.len < 1 || (v22 = p_objsysDllPath->buffer) == 0)
                    v22 = emptyString;
                FancyBoxErrorMessageBox(this, "Seek StdInitFancyBox Err %s!", v22);
                goto LABEL_62;
            }
            StdCmdFancyBox = (void(__cdecl*)(int, char*))GetProcAddress(this->hObjsys, "StdCmdFancyBox");
            this->fStdCmdFancyBox = StdCmdFancyBox;
            if (!StdCmdFancyBox)
            {
                v24 = FancyStrIsEmpty(&this->objsysDllPath);
                FancyBoxErrorMessageBox(this, "Seek StdCmdFancyBox Err %s!", v24);
            LABEL_62:
                this->objsysReady = 0;
                LOBYTE(v32) = 1;
                FancyStrDtor(&lpPathName);
                goto LABEL_23;
            }
            if (this->fStdInitFancyBox(this->hInstance, hWnd, this->field_74, 100) < 1)
            {
                FancyBoxErrorMessageBox(this, "Init FacnyBox return err");
                FreeLibrary(this->hObjsys);
                this->fStdCmdFancyBox = 0;
                this->hObjsys = 0;
                goto LABEL_62;
            }
            if (this->strCommandRaw.len > 3)
            {
                v25 = FancyStrIsEmpty(&this->strCommandRaw);
                this->fStdCmdFancyBox(0, v25);
            }
            LOBYTE(v32) = 1;
            FancyStrDtor(&lpPathName);
            LOBYTE(v32) = 0;
            FancyStrDtor(&lpFileName);
            v32 = -1;
            FancyStrDtor(&lpExistingFileName);
        }
    }
}
// 404512: conditional instruction was optimized away because eax.4>=3
// 4041A0: using guessed type CHAR Filename[260];


//----- (00401C00) --------------------------------------------------------
BYTE* __cdecl FancyRegReadString(LPCSTR lpString2, LPCSTR lpValueName, BYTE* lpDefault)
{
    BYTE* result; // eax
    bool v4; // zf
    DWORD cbData; // [esp+0h] [ebp-Ch] BYREF
    HKEY phkResult; // [esp+4h] [ebp-8h] BYREF
    DWORD Type; // [esp+8h] [ebp-4h] BYREF
    static BYTE Data[1024]; // idb

    lstrcpyA((LPSTR)&Data, "SOFTWARE\\XXT\\");
    lstrcatA((LPSTR)&Data, lpString2);
    if (RegOpenKeyA(HKEY_LOCAL_MACHINE, (LPCSTR)&Data, &phkResult))
        return lpDefault;
    cbData = 1024;
    v4 = RegQueryValueExA(phkResult, lpValueName, 0, &Type, Data, &cbData) == 0;
    result = lpDefault;
    if (v4)
        return Data;
    return result;
}

//----- (004065F0) --------------------------------------------------------
BOOL __cdecl CompareTime(LPCSTR lpFileName, int a2, int a3, FILETIME* a4)
{
    HANDLE FirstFileA; // eax
    DWORD dwHighDateTime; // edx
    DWORD v7; // ecx
    struct _FILETIME SystemTimeAsFileTime; // [esp+0h] [ebp-148h] BYREF
    struct _WIN32_FIND_DATAA FindFileData; // [esp+8h] [ebp-140h] BYREF

    FirstFileA = FindFirstFileA(lpFileName, &FindFileData);
    if (FirstFileA == (HANDLE)-1)
        return 0;
    FindClose(FirstFileA);
    if (a3 > 0 && a3 != FindFileData.nFileSizeLow - FindFileData.nFileSizeHigh)
        return 0;
    if (a4)
    {
        dwHighDateTime = a4->dwHighDateTime;
        SystemTimeAsFileTime.dwLowDateTime = a4->dwLowDateTime;
        SystemTimeAsFileTime.dwHighDateTime = dwHighDateTime;
    }
    else
    {
        GetSystemTimeAsFileTime(&SystemTimeAsFileTime);
    }
    if (CompareFileTime(&FindFileData.ftLastWriteTime, &SystemTimeAsFileTime) > 0)
        return 0;
    v7 = (unsigned __int64)(-10000000i64 * a2 + *(_QWORD*)&SystemTimeAsFileTime) >> 32;
    SystemTimeAsFileTime.dwLowDateTime += -10000000 * a2;
    SystemTimeAsFileTime.dwHighDateTime = v7;
    return CompareFileTime(&FindFileData.ftLastWriteTime, &SystemTimeAsFileTime) >= 0;
}

//----- (00402040) --------------------------------------------------------
int FancyBoxHideAndErrorMessageBox(FancyBaseDialog* a1, HWND hWnd, LPCSTR a3, ...)
{
    CHAR Text[2048]; // [esp+0h] [ebp-800h] BYREF
    va_list arglist; // [esp+810h] [ebp+10h] BYREF

    va_start(arglist, a3);
    wvsprintfA(Text, a3, arglist);
    FancyBoxHideWindow(a1);
    return MessageBoxA(hWnd, Text, "FancyBox Err", 0x10u);
}

//----- (00406570) --------------------------------------------------------
BOOL __cdecl VerifyFileSizeAndTime(LPCSTR lpFileName, unsigned int filetime, int filesize)
{
    HANDLE FirstFileA; // eax
    BOOL result; // eax
    unsigned int v5; // eax
    unsigned int v6; // eax
    struct _WIN32_FIND_DATAA FindFileData; // [esp+0h] [ebp-140h] BYREF

    FirstFileA = FindFirstFileA(lpFileName, &FindFileData);
    if (FirstFileA == (HANDLE)-1)
        return 0;
    FindClose(FirstFileA);
    result = 0;
    if (filesize <= 0 || filesize == FindFileData.nFileSizeLow - FindFileData.nFileSizeHigh)
    {
        if (!filetime)
            return 1;
        v5 = FileTimeToTime_t(&FindFileData.ftLastWriteTime);
        v6 = v5 <= filetime ? filetime - v5 : v5 - filetime;
        if (v6 <= 0x3C)
            return 1;
    }
    return result;
}

//----- (00401D30) --------------------------------------------------------
int __usercall sub_401D30(CHAR* a1, FancyStr* a2, char* a3)
{
    FancyBoxFile file; // [esp+4h] [ebp-368h] BYREF
    FancyBoxFileContent v5; // [esp+18h] [ebp-354h] BYREF
    FancyBoxFileContent v6; // [esp+2Ch] [ebp-340h] BYREF
    FancyCab v7; // [esp+40h] [ebp-32Ch] BYREF
    int v8; // [esp+368h] [ebp-4h]

    FancyBoxFileInitialize(&file);
    v8 = 0;
    FancyBoxFileContentCtor(&v5);
    LOBYTE(v8) = 1;
    FancyBoxFileContentCtor(&v6);
    LOBYTE(v8) = 2;
    if (!FancyBoxFileOpen(&file, a3, 0) || !FancyBoxFileContentRead(&v5, &file))
        goto LABEL_12;
    FancyBoxFileClose(&file);
    v5.readSize = 0;
    FancyCabCtor(&v7);
    LOBYTE(v8) = 3;
    if (!FancyCabInitialize(&v7, &v5, &v6))
    {
        FancyStrFromCStr(a2, "Can't open file");
        LOBYTE(v8) = 2;
        FancyCabDtor(&v7);
        LOBYTE(v8) = 1;
        FancyBoxFileContentDtor(&v6);
        LOBYTE(v8) = 0;
        FancyBoxFileContentDtor(&v5);
        v8 = -1;
        FancyBoxFileDtor(&file);
        return 0;
    }
    if (!FancyCabExtract(&v7, 0))
    {
        FancyStrFromCStr(a2, "Can't extract file");
        LOBYTE(v8) = 2;
        FancyCabDtor(&v7);
        LOBYTE(v8) = 1;
        FancyBoxFileContentDtor(&v6);
        LOBYTE(v8) = 0;
        FancyBoxFileContentDtor(&v5);
        v8 = -1;
        FancyBoxFileDtor(&file);
        return 0;
    }
    if (VerifyFileSizeAndTime(a1, 0, 0) && !DeleteFileA(a1))
    {
        FancyStrFromCStr(a2, "Can't over write file");
        LOBYTE(v8) = 2;
        FancyCabDtor(&v7);
        LOBYTE(v8) = 1;
        FancyBoxFileContentDtor(&v6);
        LOBYTE(v8) = 0;
        FancyBoxFileContentDtor(&v5);
        v8 = -1;
        FancyBoxFileDtor(&file);
        return 0;
    }
    if (!FancyBoxFileOpen(&file, a1, 1u))
    {
        FancyStrFromCStr(a2, "Can't create file");
        LOBYTE(v8) = 2;
        FancyCabDtor(&v7);
    LABEL_12:
        LOBYTE(v8) = 1;
        FancyBoxFileContentDtor(&v6);
        LOBYTE(v8) = 0;
        FancyBoxFileContentDtor(&v5);
        v8 = -1;
        FancyBoxFileDtor(&file);
        return 0;
    }
    FancyBoxFileContentWrite(&v6, &file);
    FancyBoxFileClose(&file);
    LOBYTE(v8) = 2;
    FancyCabDtor(&v7);
    LOBYTE(v8) = 1;
    FancyBoxFileContentDtor(&v6);
    LOBYTE(v8) = 0;
    FancyBoxFileContentDtor(&v5);
    v8 = -1;
    FancyBoxFileDtor(&file);
    return 1;
}

//----- (004066C0) --------------------------------------------------------
time_t __cdecl GetLastWriteTime(LPCSTR lpFileName)
{
    HANDLE FirstFileA; // eax
    struct _WIN32_FIND_DATAA FindFileData; // [esp+0h] [ebp-140h] BYREF

    FirstFileA = FindFirstFileA(lpFileName, &FindFileData);
    if (FirstFileA == (HANDLE)-1)
        return 0;
    FindClose(FirstFileA);
    return FileTimeToTime_t(&FindFileData.ftLastWriteTime);
}

//----- (00402230) --------------------------------------------------------
void __cdecl UpdateProgress(int a1, unsigned int a2)
{
    unsigned int v2; // esi

    if (fancyBox.field_CE0)
    {
        if (fancyBox.updateDialog)
        {
            v2 = (unsigned int)(100 * (a1 + fancyBox.field_CD8)) / fancyBox.field_CD4;
            FancyUpdateDialogSetDownloadPercentage(fancyBox.updateDialog, 100 * a1 / a2);
            FancyUpdateDialogSetUpdatePercentage(fancyBox.updateDialog, (int)(90 * v2) / 100 + 5);
        }
    }
}

//----- (00405230) --------------------------------------------------------
BOOL __cdecl sub_405230(char* a1, char* a2, int a3, int a4, void(__cdecl* a5)(int, unsigned int))
{
    BOOL v5; // esi
    FancyDownloader v7; // [esp+4h] [ebp-6Ch] BYREF
    int v8; // [esp+6Ch] [ebp-4h]

    FancyDownloaderCtor(&v7);
    v8 = 0;
    FancyStrFromCStr(&v7.netPath, a1);
    FancyStrFromCStr(&v7.localPath, a2);
    v7.fUpdateProgress = a5;
    v7.field_48 = a3;
    v7.size = a4;
    FancyDownloaderOpen(&v7);
    if (v7.stage <= 2)
    {
        do
            Sleep(6u);
        while (processWindowsMessages() && v7.stage <= 2);
    }
    v5 = v7.stage == 4;
    v8 = -1;
    FancyDownloaderDtor(&v7);
    return v5;
}

//----- (00401BB0) --------------------------------------------------------
int FancyBoxErrorMessageBox(FancyBox* a1, LPCSTR a2, ...)
{
    CHAR Text[2048]; // [esp+0h] [ebp-800h] BYREF
    va_list arglist; // [esp+80Ch] [ebp+Ch] BYREF

    va_start(arglist, a2);
    wvsprintfA(Text, a2, arglist);
    return MessageBoxA(a1->hWnd, Text, "FancyBox Err", 0x10u);
}

