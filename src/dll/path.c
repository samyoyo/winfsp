/**
 * @file dll/path.c
 *
 * @copyright 2015 Bill Zissimopoulos
 */

#include <dll/library.h>

FSP_API VOID FspPathPrefix(PWSTR Path, PWSTR *PPrefix, PWSTR *PRemain)
{
    PWSTR Pointer;

    for (Pointer = Path; *Pointer; Pointer++)
        if (L'\\' == *Pointer)
        {
            *Pointer++ = L'\0';
            for (; L'\\' == *Pointer; Pointer++)
                ;
            break;
        }

    *PPrefix = Path;
    *PRemain = Pointer;
}

FSP_API VOID FspPathSuffix(PWSTR Path, PWSTR *PRemain, PWSTR *PSuffix)
{
    PWSTR Pointer, RemainEnd, Suffix = 0;

    for (Pointer = Path; *Pointer;)
        if (L'\\' == *Pointer)
        {
            RemainEnd = Pointer++;
            for (; L'\\' == *Pointer; Pointer++)
                ;
            Suffix = Pointer;
        }
        else
            Pointer++;

    *PRemain = Path;
    if (Path < Suffix)
    {
        *RemainEnd = L'\0';
        *PSuffix = Suffix;
    }
    else
        *PSuffix = Pointer;
}

FSP_API VOID FspPathCombine(PWSTR Prefix, PWSTR Suffix)
{
    for (; Prefix < Suffix; Prefix++)
        if (L'\0' == *Prefix)
            *Prefix = L'\\';
}