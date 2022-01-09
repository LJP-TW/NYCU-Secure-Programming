#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strsafe.h>

__declspec(dllexport) int __cdecl YoDllFunc2 (char *str, int a, int passwd2);

__declspec(dllexport) int __cdecl YoDllFunc1 (char *str, int passwd1, int passwd2)
{
    if (passwd1 != 0x54878745) {
        StringCbCopyA(str, 3, "GG");
        return 0;
    }

    str[0] = 'F';

    YoDllFunc2(str, 'L', passwd2);

    str[17] = 'R';

    StringCbCopyA(&str[18], 2, "1MV)230f,23k9v0k23.sas//s???sdlasod1");
    StringCbCopyA(&str[19], 2, "gasd1aasv1sVASKM(I(Fi92kf012kf12kf+1d");
    StringCbCopyA(&str[20], 2, "HmSVIMV@OIFJ)(V@(#KV(@)#KV(@V)KALSDALPSD");
    StringCbCopyA(&str[21], 2, "TASVasacsk0i2k0wkf203k4[90kbtjpgjfhvyufhg0cv");
    StringCbCopyA(&str[22], 2, "?Kiskd02msad2mW)M*DU@*DU@(#*F(@!)!)@)!===+");
    StringCbCopyA(&str[23], 2, "}mvoi3mrj8 p4u9f3um4 3[6369as08 ==");

    str[24] = 0;

    return 0;
}


