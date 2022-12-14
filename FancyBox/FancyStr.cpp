#include "FancyStr.hpp"
#include "common.hpp"
#include <stdlib.h>
#include <string.h>
#include <WinUser.h>

#define __thiscall __fastcall

char emptyString0[2] = { '\0', '\0' }; // weak
char* emptyString = (char*)&emptyString0;
int dword_4186F8[256]; // weak
char byte_418AF8[16]; // weak

//----- (00401000) --------------------------------------------------------
char* __thiscall FancyStrIsEmpty(FancyStr* This)
{
    char* result; // eax

    if (This->len < 1)
        return emptyString;
    result = This->buffer;
    if (!This->buffer)
        return emptyString;
    return result;
}

//----- (004015B0) --------------------------------------------------------
void __thiscall FancyStrDtor(FancyStr* This)
{
    if (This->buffer)
        free(This->buffer);
    This->buffer = 0;
    This->len = 0;
    This->capacity = 0;
}

//----- (00406CF0) --------------------------------------------------------
// Microsoft VisualC 2-14/net runtime
void __thiscall FancyStrCtor(FancyStr* This)
{
    This->buffer = 0;
    This->len = 0;
    This->capacity = 0;
}

//----- (00406D00) --------------------------------------------------------
void __thiscall FancyStrSetCStr(FancyStr* This, const char* a2, int a3)
{
    int v3; // edi
    char* v5; // eax
    int v6; // ecx
    unsigned int v7; // edx

    v3 = a3;
    if (a3 < 0)
        v3 = 0;
    if (This->buffer)
        free(This->buffer);
    This->capacity = v3 + 8;
    This->buffer = 0;
    This->len = 0;
    v5 = (char*)operator new(v3 + 10);
    This->buffer = v5;
    if (a2 && v3 > 0)
    {
        v6 = strlen(a2);
        v7 = v6;
        if (v6 > 0)
        {
            if (v6 >= v3)
                v7 = v3;
            qmemcpy(v5, a2, v7);
            This->buffer[v7] = 0;
            This->len = v7;
        }
    }
    else
    {
        *v5 = 0;
    }
}

//----- (00406DA0) --------------------------------------------------------
int __thiscall FancyStrFindNextChar(FancyStr* This, char a2, int a3)
{
    int len; // edx
    char* buffer; // edx
    char v5; // cl
    char* v6; // eax

    len = This->len;
    if (len < 1 || a3 >= len)
        return -1;
    buffer = This->buffer;
    v5 = This->buffer[a3];
    v6 = &buffer[a3];
    if (!v5)
        return -1;
    while (v5 != a2)
    {
        v5 = *++v6;
        if (!v5)
            return -1;
    }
    return v6 - buffer;
}

//----- (00406DF0) --------------------------------------------------------
char* __usercall find_cstr(char* result, const char* a2)
{
    char v2; // dl
    int i; // esi
    char* v4; // ecx

    if (*a2)
    {
        v2 = *result;
        if (*result)
        {
            for (i = result - a2; ; ++i)
            {
                v4 = (char*)a2;
                if (v2)
                    break;
            LABEL_8:
                if (!*v4)
                    return result;
                v2 = *++result;
                if (!v2)
                    return 0;
            }
            while (*v4)
            {
                if (v4[i] == *v4)
                {
                    if ((v4++)[i + 1])
                        continue;
                }
                goto LABEL_8;
            }
        }
        else
        {
            return 0;
        }
    }
    return result;
}

//----- (00406E40) --------------------------------------------------------
int __thiscall FancyStrFind(FancyStr* This, const char* a2, int start)
{
    int len; // edx
    char* buffer; // esi
    int v6; // eax
    char* cstr; // eax

    len = This->len;
    if (len < 1)
        return -1;
    buffer = This->buffer;
    if (!This->buffer || !a2)
        return -1;
    v6 = start;
    if (start < 0)
        v6 = 0;
    if (v6 < len && (cstr = find_cstr(&buffer[v6], a2)) != 0)
        return cstr - buffer;
    else
        return -1;
}

//----- (00406E90) --------------------------------------------------------
signed int __thiscall FancyStrToLower(FancyStr* This)
{
    signed int result; // eax

    result = This->len;
    if (result >= 1)
        return CharLowerBuffA(This->buffer, This->len);
    return result;
}

//----- (00406EB0) --------------------------------------------------------
void __thiscall FancyStrInsertCStrAt(FancyStr* This, int a2, const char* a3)
{
    signed int v4; // ebp
    int len; // eax
    int v6; // eax
    char* buffer; // esi
    int v8; // eax
    char* v9; // ecx
    int v10; // eax
    char* v11; // [esp-10h] [ebp-18h]

    if (a2 >= 0)
    {
        if (a3)
        {
            v4 = strlen(a3);
            if (v4 >= 1)
            {
                len = This->len;
                if (a2 >= len)
                    v6 = a2 + v4;
                else
                    v6 = v4 + len;
                if (v6 >= This->capacity)
                {
                    buffer = This->buffer;
                    v11 = This->buffer;
                    This->buffer = 0;
                    FancyStrSetCStr(This, v11, v6 + 1);
                    if (buffer)
                        free(buffer);
                }
                v8 = This->len;
                if (a2 < v8)
                    memcpy(&This->buffer[v4 + a2], &This->buffer[a2], v8 - a2 + 1);
                qmemcpy(&This->buffer[a2], a3, v4);
                v9 = This->buffer;
                v10 = v4 + This->len;
                This->len = v10;
                v9[v10] = 0;
            }
        }
    }
}

//----- (00406F70) --------------------------------------------------------
void __thiscall FancyStrInsert(FancyStr* This, int a2, char a3)
{
    int len; // eax
    int v5; // eax
    char* buffer; // ebx
    int v7; // eax
    char* v8; // ecx
    int v9; // eax
    char* v10; // [esp-Ch] [ebp-14h]

    if (a2 >= 0)
    {
        len = This->len;
        if (a2 >= len)
            v5 = a2 + 1;
        else
            v5 = len + 1;
        if (v5 >= This->capacity)
        {
            buffer = This->buffer;
            v10 = This->buffer;
            This->buffer = 0;
            FancyStrSetCStr(This, v10, v5 + 1);
            if (buffer)
                free(buffer);
        }
        v7 = This->len;
        if (a2 < v7)
            memcpy(&This->buffer[a2 + 1], &This->buffer[a2], v7 - a2 + 1);
        This->buffer[a2] = a3;
        v8 = This->buffer;
        v9 = This->len + 1;
        This->len = v9;
        v8[v9] = 0;
    }
}

//----- (00406FF0) --------------------------------------------------------
void __thiscall FancyStrAppend(FancyStr* This, FancyStr* a2)
{
    FancyStrInsertCStrAt(This, This->len, a2->buffer);
}

//----- (00407010) --------------------------------------------------------
void __thiscall FancyStrAppendCStr(FancyStr* This, const char* a2)
{
    FancyStrInsertCStrAt(This, This->len, a2);
}

//----- (00407030) --------------------------------------------------------
char __thiscall FancyStrCharAt(FancyStr* This, int a2)
{
    if (a2 >= 0 && a2 < This->len && This->buffer)
        return This->buffer[a2];
    else
        return 0;
}

//----- (00407050) --------------------------------------------------------
BOOL __thiscall FancyStrEquals(FancyStr* This, const char* a2)
{
    return This->buffer && a2 && This->len >= 1 && strcmp(This->buffer, a2) == 0;
}

//----- (004070C0) --------------------------------------------------------
BOOL __thiscall FancyStrNotEquals(FancyStr* This, FancyStr* a2)
{
    int len; // eax

    len = This->len;
    return len < 1 || len != a2->len || strcmp(This->buffer, a2->buffer) != 0;
}

//----- (00407130) --------------------------------------------------------
BOOL __thiscall FancyStrNotEqual(FancyStr* This, const char* a2)
{
    return !FancyStrEquals(This, a2);
}

//----- (00407150) --------------------------------------------------------
void __thiscall FancyStrReplace(FancyStr* This, const char* a2, const char* a3)
{
    int v4; // esi
    unsigned int v5; // ebp
    char* v6; // eax
    char* v7; // edx
    int v8; // eax
    unsigned int v9; // esi
    char* cstr; // eax
    int capacity; // edx
    unsigned int v12; // edi
    int v13; // ecx
    char* v14; // eax
    char* i; // eax
    int v16; // [esp+Ch] [ebp-14h]
    int v17; // [esp+10h] [ebp-10h]
    unsigned int v18; // [esp+14h] [ebp-Ch]
    unsigned int v19; // [esp+14h] [ebp-Ch]
    int v20; // [esp+18h] [ebp-8h]
    char* buffer; // [esp+1Ch] [ebp-4h]

    v16 = 0;
    if (a3)
    {
        if (a2)
        {
            if (This->len >= 1)
            {
                v4 = strlen(a2);
                v20 = v4;
                v5 = strlen(a3);
                if (v4 >= 1)
                {
                    v18 = v4 - v5;
                    if ((int)(v4 - v5) <= 0)
                    {
                        if ((int)(v4 - v5) >= 0)
                        {
                            for (i = find_cstr(This->buffer, a2); i; i = find_cstr(&i[v5], a2))
                            {
                                qmemcpy(i, a3, v5);
                                ++v16;
                            }
                        }
                        else
                        {
                            v9 = v5 - v4;
                            v19 = v9;
                            cstr = find_cstr(This->buffer, a2);
                            if (cstr)
                            {
                                while (1)
                                {
                                    capacity = This->capacity;
                                    v12 = cstr - This->buffer;
                                    buffer = This->buffer;
                                    v13 = v9 + This->len;
                                    This->len = v13;
                                    if (v13 < capacity)
                                    {
                                        memcpy(&cstr[v5], &cstr[v20], v13 - v12 - v5);
                                    }
                                    else
                                    {
                                        This->capacity = v9 + v13 + 4 * v9 + 8;
                                        v14 = (char*)operator new(v9 + v13 + 4 * v9 + 9);
                                        This->buffer = v14;
                                        qmemcpy(v14, buffer, v12);
                                        qmemcpy(&This->buffer[v12 + v5], &buffer[v12 + v20], This->len - v12 - v5);
                                        free(buffer);
                                    }
                                    qmemcpy(&This->buffer[v12], a3, v5);
                                    This->buffer[This->len] = 0;
                                    ++v16;
                                    cstr = find_cstr(&This->buffer[v12 + v5], a2);
                                    if (!cstr)
                                        break;
                                    v9 = v19;
                                }
                            }
                        }
                    }
                    else
                    {
                        v6 = find_cstr(This->buffer, a2);
                        if (v6)
                        {
                            while (1)
                            {
                                v17 = v6 - This->buffer;
                                qmemcpy(&v6[v5], &v6[v4], This->len - v17 - v4);
                                if (v5)
                                    qmemcpy(v6, a3, v5);
                                v7 = This->buffer;
                                v8 = This->len - v18;
                                This->len = v8;
                                v7[v8] = 0;
                                ++v16;
                                v6 = find_cstr(&This->buffer[v17 + v5], a2);
                                if (!v6)
                                    break;
                                v4 = v20;
                            }
                        }
                    }
                }
            }
        }
    }
}

//----- (004073D0) --------------------------------------------------------
void __thiscall FancyStrRemove(FancyStr* This, int index, int size)
{
    int len; // ecx
    int v5; // edx
    char* buffer; // ecx
    int v7; // eax

    if (index >= 0)
    {
        len = This->len;
        if (index < len)
        {
            if (This->buffer)
            {
                v5 = size;
                if (index + size >= len)
                {
                    if (index < 1)
                    {
                        FancyStrDtor(This);
                        return;
                    }
                    if (index + size >= len)
                        v5 = len - index;
                }
                if (v5 >= 1)
                {
                    if (This->len - index - v5 > 0)
                        qmemcpy(&This->buffer[index], &This->buffer[index + v5], This->len - index - v5);
                    buffer = This->buffer;
                    v7 = This->len - v5;
                    This->len = v7;
                    buffer[v7] = 0;
                }
            }
        }
    }
}

//----- (00407450) --------------------------------------------------------
int __cdecl Cstr_to_int(char* a1)
{
    char v1; // al
    char v2; // al
    char v3; // dl
    int v4; // eax
    char* v5; // ecx
    int result; // eax
    char v7; // dl
    char* v8; // ecx

    v1 = *a1;
    if (*a1 == '-')
    {
        v2 = a1[1];
        if (v2 < '0' || v2 > '9')
        {
            v4 = 0;
        }
        else
        {
            v3 = a1[2];
            v4 = v2 - '0';
            v5 = a1 + 2;
            if (v3 >= '0')
            {
                while (v3 <= 57)
                {
                    ++v5;
                    v4 = v3 + 10 * v4 - '0';
                    v3 = *v5;
                    if (*v5 < '0')
                        return -v4;
                }
            }
        }
        return -v4;
    }
    else if (v1 < '0' || v1 > '9')
    {
        return 0;
    }
    else
    {
        v7 = a1[1];
        result = v1 - '0';
        v8 = a1 + 1;
        if (v7 >= '0')
        {
            do
            {
                if (v7 > '9')
                    break;
                ++v8;
                result = v7 + 10 * result - '0';
                v7 = *v8;
            } while (*v8 >= '0');
        }
    }
    return result;
}

//----- (004074D0) --------------------------------------------------------
int __cdecl Cstr_to_int_hex(char* a1)
{
    char* v1; // edx
    unsigned __int8 v2; // cl
    int result; // eax
    int v4; // esi

    v1 = a1;
    v2 = *a1;
    result = 0;
    if (*a1)
    {
        do
        {
            v4 = dword_4186F8[v2];
            v2 = v1[1];
            result = v4 + 16 * result;
            ++v1;
        } while (v2);
    }
    return result;
}
// 4186F8: using guessed type int dword_4186F8[256];

//----- (00407500) --------------------------------------------------------
void __thiscall FancyStrResize(FancyStr* This, int a2)
{
    int v3; // edi
    char* v4; // eax

    if (This->len <= a2)
    {
        v3 = a2;
        if (a2 < 0)
            v3 = 0;
        if (This->buffer)
            free(This->buffer);
        This->capacity = v3 + 8;
        This->buffer = 0;
        This->len = 0;
        v4 = (char*)operator new(v3 + 10);
        This->buffer = v4;
        *v4 = 0;
    }
    else
    {
        This->buffer[a2] = 0;
        This->len = strlen(This->buffer);
    }
}

//----- (00407570) --------------------------------------------------------
char* __thiscall FancyStrAlloc(FancyStr* This, int a2)
{
    int v2; // edi
    char* v4; // eax

    v2 = a2;
    if (a2 < 0)
        v2 = 0;
    if (This->buffer)
        free(This->buffer);
    This->capacity = v2 + 8;
    This->buffer = 0;
    This->len = 0;
    v4 = (char*)operator new(v2 + 10);
    This->buffer = v4;
    *v4 = 0;
    return This->buffer;
}

//----- (004075C0) --------------------------------------------------------
void __thiscall FancyStrShrink(FancyStr* This)
{
    This->len = strlen(This->buffer);
}

//----- (004075E0) --------------------------------------------------------
int __thiscall FancyStrTrimTailChar(FancyStr* This, char a2)
{
    int len; // esi
    char* buffer; // edx

    len = This->len;
    if (len < 1)
        return 0;
    buffer = This->buffer;
    if (!This->buffer || buffer[len - 1] != a2)
        return 0;
    This->len = len - 1;
    buffer[len - 1] = 0;
    return 1;
}

//----- (00407620) --------------------------------------------------------
BOOL __thiscall FancyStrStartsWith(FancyStr* This, const char* a2)
{
    int v3; // eax
    char v5[60]; // [esp+8h] [ebp-3Ch] BYREF

    v3 = strlen(a2);
    if (This->len < v3 || v3 >= 0x28)
        return 0;
    qmemcpy(v5, This->buffer, v3);
    v5[v3] = 0;
    return strcmp(v5, a2) == 0;
}
// 407620: using guessed type char var_3C[60];

//----- (004076C0) --------------------------------------------------------
FancyStr* __thiscall FancyStrSetStr(FancyStr* This, const char** a2)
{
    const char* v3; // edx
    bool v4; // zf

    This->buffer = 0;
    This->len = 0;
    This->capacity = 0;
    v3 = *a2;
    v4 = *a2 == 0;
    This->buffer = 0;
    This->len = 0;
    This->capacity = 0;
    if (!v4)
        FancyStrSetCStr(This, v3, strlen(v3));
    return This;
}

//----- (00407700) --------------------------------------------------------
void __thiscall FancyStrCtorFromCStr(FancyStr* This, char* a2)
{
    This->buffer = 0;
    This->len = 0;
    This->capacity = 0;
    if (a2)
        FancyStrSetCStr(This, a2, strlen(a2));
}

//----- (00407740) --------------------------------------------------------
void FancyStrSetVAStr(FancyStr* a1, LPCSTR arg4, ...)
{
    CHAR a2[2048]; // [esp+4h] [ebp-800h] BYREF
    va_list arglist; // [esp+810h] [ebp+Ch] BYREF

    va_start(arglist, arg4);
    wvsprintfA(a2, arg4, arglist);
    if (a1->buffer)
        free(a1->buffer);
    a1->buffer = 0;
    a1->len = 0;
    a1->capacity = 0;
    FancyStrSetCStr(a1, a2, strlen(a2));
}

//----- (004077B0) --------------------------------------------------------
void __thiscall FancyStrSet(FancyStr* This, const char** a2)
{
    const char* v2; // edi

    v2 = *a2;
    if (This->buffer)
        free(This->buffer);
    This->buffer = 0;
    This->len = 0;
    This->capacity = 0;
    if (v2)
        FancyStrSetCStr(This, v2, strlen(v2));
}

//----- (00407800) --------------------------------------------------------
void __thiscall FancyStrFromCStr(FancyStr* This, const char* a2)
{
    if (This->buffer)
        free(This->buffer);
    This->buffer = 0;
    This->len = 0;
    This->capacity = 0;
    if (a2)
        FancyStrSetCStr(This, a2, strlen(a2));
}

//----- (00407850) --------------------------------------------------------
int __thiscall FancyStrSubstring(FancyStr* This, FancyStr* a2, char separator, char a4, int a5)
{
    int len; // edx
    int result; // eax
    char* buffer; // edi
    unsigned __int8 v9; // bl
    int v10; // ecx
    signed int v11; // ecx
    int v12; // ecx
    int v13; // ebx
    char v14; // cl
    int v15; // esi
    char v16; // al
    char* v17; // edi
    char* v18; // edi
    int v19; // ecx
    int v20; // eax
    char* v21; // edi
    int v22; // esi
    int v23; // ecx
    char v24; // al
    const char* v25; // edi
    int i; // esi
    char v27; // al
    signed int v28; // ecx
    int v29; // ecx

    len = This->len;
    result = 0;
    if (len < 1)
        return result;
    buffer = This->buffer;
    do                                            // remove character before ' '
    {
        v9 = buffer[result];
        if (v9 > ' ')
            break;
        ++result;
    } while (result < This->len);
    if (result)
    {
        v10 = This->len;
        if (v10 > 0 && buffer)
        {
            if (result < v10)
            {
                if (result >= 1)
                {
                    v11 = v10 - result;
                    if (v11 > 0)
                        qmemcpy(buffer, &buffer[result], v11);
                    v12 = This->len - result;
                    This->len = v12;
                    This->buffer[v12] = 0;
                }
            }
            else
            {
                FancyStrDtor(This);
            }
        }
        len = This->len;
        if (len < 1)
            return 0;
    }
    if (v9 == '\'' || v9 == '"')
    {
        v22 = 1;
        v23 = 0;
        if (len > 1)
        {
            do
            {
                v24 = This->buffer[v22];
                if (v24 == '\\' && v23 != v22)
                    v23 = v22 + 1;
                if (v24 == v9 && v23 != v22)
                    break;
                ++v22;
            } while (v22 < This->len);
        }
        This->buffer[v22] = 0;
        v25 = This->buffer + 1;
        if (a2->buffer)
            free(a2->buffer);
        a2->buffer = 0;
        a2->len = 0;
        a2->capacity = 0;
        if (v25)
            FancyStrSetCStr(a2, v25, strlen(v25));
        for (i = v22 + 1; i < This->len; ++i)
        {
            v27 = This->buffer[i];
            if (v27 == separator)
                break;
            if (v27 == a4)
                break;
        }
        v19 = This->len;
        v20 = i + 1;
        if (v19 <= 0)
            return 1;
        v21 = This->buffer;
        if (!This->buffer)
            return 1;
        if (v20 >= v19)
            goto LABEL_38;
        goto LABEL_66;
    }
    v13 = 0;
    v14 = separator;
    v15 = 0;
    do
    {
        v16 = This->buffer[v13];
        if (v16 == '{' && v14 != '{')
            ++v15;
        if (v16 == '}' && --v15 >= 0)
            goto LABEL_30;
        if (v15 >= 1)
            goto LABEL_30;
        if (v16 == v14 || v16 > 0 && v16 < 32 || v16 == a4)
            break;
        v14 = separator;
    LABEL_30:
        ++v13;
    } while (v13 < This->len);
    if (v13 < len)
    {
        This->buffer[v13] = 0;
        v18 = This->buffer;
        if (a2->buffer)
            free(a2->buffer);
        a2->buffer = 0;
        a2->len = 0;
        a2->capacity = 0;
        if (v18)
            FancyStrSetCStr(a2, v18, strlen(v18));
        v19 = This->len;
        v20 = v13 + 1;
        if (v19 <= 0)
            return 1;
        v21 = This->buffer;
        if (!This->buffer)
            return 1;
        if (v20 >= v19)
        {
            FancyStrDtor(This);
            return 1;
        }
    LABEL_66:
        if (v20 >= 1)
        {
            v28 = v19 - v20;
            if (v28 > 0)
                qmemcpy(v21, &v21[v20], v28);
            v29 = This->len - v20;
            This->len = v29;
            This->buffer[v29] = 0;
        }
        return 1;
    }
    if (a5)
        return 0;
    v17 = This->buffer;
    if (a2->buffer)
        free(a2->buffer);
    a2->buffer = 0;
    a2->len = 0;
    a2->capacity = 0;
    if (v17)
        FancyStrSetCStr(a2, v17, strlen(v17));
    if (This->buffer)
        LABEL_38:
    free(This->buffer);
    This->buffer = 0;
    This->len = 0;
    This->capacity = 0;
    return 1;
}
// 40786B: conditional instruction was optimized away because edx.4>=1
// 4078F9: conditional instruction was optimized away because edx.4>=1

//----- (00407B20) --------------------------------------------------------
int __thiscall FancyStrGetInteger(FancyStr* This, int nDefault, char separator)
{
    char* buffer; // esi
    int v5; // edi
    int v6; // esi
    char* v7; // eax
    FancyStr v8; // [esp+4h] [ebp-18h] BYREF
    int v9; // [esp+18h] [ebp-4h]

    memset(&v8, 0, sizeof(v8));
    v9 = 0;
    if (FancyStrSubstring(This, &v8, separator, 0, 0))
    {
        buffer = v8.buffer;
        if (v8.len > 2 && v8.buffer)
        {
            if (*v8.buffer == '#')
            {
                v5 = Cstr_to_int_hex(v8.buffer + 1);
                v9 = -1;
                free(buffer);
                return v5;
            }
            if (*v8.buffer == '0' && v8.buffer[1] == 'x')
            {
                v6 = Cstr_to_int_hex(v8.buffer + 2);
                v9 = -1;
                FancyStrDtor(&v8);
                return v6;
            }
        }
        if (v8.len < 1 || (v7 = v8.buffer) == 0)
            v7 = emptyString;
        v5 = Cstr_to_int(v7);
        v9 = -1;
        if (buffer)
            free(buffer);
        return v5;
    }
    v9 = -1;
    if (v8.buffer)
        free(v8.buffer);
    return nDefault;
}
// 407BA4: conditional instruction was optimized away because %var_14.4>=3
// 407BBC: conditional instruction was optimized away because %var_14.4>=3
// 407BE4: conditional instruction was optimized away because %var_18.4!=0
// 407BEE: conditional instruction was optimized away because %var_14.4>=3
// 407BF9: conditional instruction was optimized away because %var_14.4>=3

//----- (00407C80) --------------------------------------------------------
FancyStr* __thiscall FancyStrSubString(FancyStr* This, FancyStr* a2, int a3, int a4)
{
    int len; // edx
    FancyStr* result; // eax
    int v7; // eax
    int v8; // ecx
    FancyStr* v9; // esi
    int v10; // esi
    char* v11; // ecx
    char v12; // bl
    FancyStr v13; // [esp+Ch] [ebp-18h] BYREF
    int v14; // [esp+20h] [ebp-4h]

    memset(&v13, 0, sizeof(v13));
    len = This->len;
    v14 = 1;
    if (len >= 1)
    {
        v7 = a3;
        if (a3 < 0)
            v7 = 0;
        v8 = a4;
        if (a4 == -1)
            v8 = len - v7;
        if (v7 + v8 > len)
            v8 = len - v7;
        if (v8 > 0)
        {
            v10 = v7 + v8;
            v11 = &This->buffer[v7 + v8];
            v12 = *v11;
            *v11 = 0;
            FancyStrFromCStr(&v13, &This->buffer[v7]);
            This->buffer[v10] = v12;
            v9 = a2;
            FancyStrSetStr(a2, (const char**)&v13.buffer);
            LOBYTE(v14) = 0;
            if (v13.buffer)
                free(v13.buffer);
        }
        else
        {
            v9 = a2;
            FancyStrSetStr(a2, (const char**)&v13.buffer);
        }
        return v9;
    }
    else
    {
        result = a2;
        a2->buffer = 0;
        a2->len = 0;
        a2->capacity = 0;
    }
    return result;
}

//----- (00406CA0) --------------------------------------------------------
int InitialzeHexMap()
{
    int result; // eax
    unsigned __int8 v1; // cl

    result = 0;
    memset(dword_4186F8, 0, sizeof(dword_4186F8));
    do
    {
        if (result >= 10)
        {
            dword_4186F8[(unsigned __int8)(result + 'W')] = result;
            v1 = result + '7';
        }
        else
        {
            v1 = result + '0';
        }
        dword_4186F8[v1] = result;
        byte_418AF8[result++] = v1;
    } while (result < 16);
    return result;
}
// 4186F8: using guessed type int dword_4186F8[256];

