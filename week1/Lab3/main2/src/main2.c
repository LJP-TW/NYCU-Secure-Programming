#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define __init __attribute__ ((constructor))

char g_buf[0x20] = "NotFLAG{QQ}";

__init void RunFunc1(int argc, char *argv[])
{
    // char __buf[] = "FLAG{Faker_BibleThump}";
    char __buf[] = {17, 26, 20, 19, 40, 20, 48, 59, 58, 44, 2, 30, 50, 56, 53, 61, 19, 46, 48, 41, 51, 63, 0};

    if (argc != 2)
        return;

    int k = atoi(argv[1]);
    int g = k / 17;
    
    printf("%d\n", g);

    if (g == 0x6486) {
        for (int i = 0; i < 22; ++i) {
            __buf[i] ^= i;
            __buf[i] ^= 87;
        }
        strcpy(g_buf, __buf);
    }
}

int main()
{
    printf("g_buf: %s\n", g_buf);
}

