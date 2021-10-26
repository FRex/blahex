#ifndef BLAHEX_H
#define BLAHEX_H

#include <string.h>
#include <stdlib.h>

static int blahex_digitToInt(char d)
{
    if('0' <= d && d <= '9') return d - '0';
    if('a' <= d && d <= 'f') return d - 'a' + 10;
    if('A' <= d && d <= 'F') return d - 'A' + 10;
    return -1;
}

static int blahex_countDigitsLen(const char * str, int len)
{
    int i, ret;
    ret = 0;
    for(i = 0; i < len; ++i)
        if(blahex_digitToInt(str[i]) != -1)
            ++ret;
    return ret;
}

static int blahex_countDigits(const char * str)
{
    return blahex_countDigitsLen(str, (int)strlen(str));
}

static int blahex_stringToBinaryLen(void * buff, const char * str, int len)
{
    int i, nib, ret, d;

    nib = -1;
    ret = 0;
    for(i = 0; i < len; ++i)
    {
        d = blahex_digitToInt(str[i]);
        if(d == -1)
            continue;

        if(nib == -1)
        {
            nib = d;
        }
        else
        {
            ((unsigned char*)buff)[ret++] = (unsigned char)((nib << 4) | d);
            nib = -1;
        }
    } /* for i */

    return ret;
}

static int blahex_stringToBinary(void * buff, const char * str)
{
    return blahex_stringToBinaryLen(buff, str, (int)strlen(str));
}

static void * blahex_stringToBinaryAllocLen(int * bytelen, const char * str, int len)
{
    *bytelen = blahex_countDigitsLen(str, len) / 2;
    void * ret = malloc(*bytelen);
    if(ret)
        blahex_stringToBinaryLen(ret, str, len);
    return ret;
}

static void * blahex_stringToBinaryAlloc(int * bytelen, const char * str)
{
    return blahex_stringToBinaryAllocLen(bytelen, str, (int)strlen(str));
}

static int blahex_binaryToString(char * str, const void * buff, int bytelen, char pad)
{
    int i, strlen;
    unsigned char b;

    strlen = 0;
    for(i = 0; i < bytelen; ++i)
    {
        b = ((unsigned char*)buff)[i];
        str[strlen++] = "0123456789ABCDEF"[b >> 4];
        str[strlen++] = "0123456789ABCDEF"[b & 15];
        if(pad)
            str[strlen++] = pad;
    } /* for i */

    /* undo last padding char to put \0 there if it exists */
    if(pad && strlen)
        --strlen;

    str[strlen] = '\0';
    return strlen;
}

#endif /* BLAHEX_H */
