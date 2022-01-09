#include <windows.h>
#include <strsafe.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
        printf("FUIYOH, Nice to meow you :)\n");
        break;
    case DLL_PROCESS_DETACH:
        printf("HAIYA\n");
        break;
    case DLL_THREAD_ATTACH:
        printf("thread FUIYOH\n");
        break;
    case DLL_THREAD_DETACH:
        printf("thread HAIYA\n");
        break;
    }

    return TRUE;
}

__declspec(dllexport) int __cdecl YoDllFunc2 (char *str, int a, int passwd2)
{
    if (passwd2 != 0x66665566) {
        return 0;
    }

    str[1] = a;
    str[2] = 'A';

    StringCbCopyA(&str[3], 2, "GASK12OKD2K)(sakD1K0DW12LS12VNRUTH94");
    StringCbCopyA(&str[4], 2, "{FV23Fsad128+v4239ds09i9kksa(@KF0");
    StringCbCopyA(&str[5], 2, "dFVNCIUW4BO2J38Jmf9c2j9jf1m9c1k9k09k0k0");

    str[6] = a;
    str[7] = a;

    StringCbCopyA(&str[8], 2, "_ve22kc30fk01 l12l-d0l12");
    StringCbCopyA(&str[9], 2, "SFLAG{Yo_Thisisn'tFLAGHA}");
    StringCbCopyA(&str[10], 2, "oKJ@)Vmv2302r329fkm23fmp23f2pi");
    StringCbCopyA(&str[11], 2, "_ve22kc30fk01 l12l-d0l12");
    StringCbCopyA(&str[12], 2, "cAKV2K3F0Ksmv2J0KV230VK232F2F23BR");
    StringCbCopyA(&str[13], 2, "0mb*@ujvE2382JF9283JF*(dbus*djV2IF");
    StringCbCopyA(&str[14], 2, "0mb*@ujvE2382JF9283JF*(dbus*djV2IF");

    str[15] = a;

    StringCbCopyA(&str[16], 2, "_ve22kc30fk01 l12l-d0l12");

    return 0;
}


