#include <stdio.h>
#include <string.h>
#include "payload_hw1r.h"

char payload[] = { 0x48, 0x89, 0xE5, 0xB8, 0x29, 0x00, 0x00, 0x00, 0xBF, 0x02, 0x00, 0x00, 0x00, 0xBE, 0x02, 0x00, 0x00, 0x00, 0xBA, 0x11, 0x00, 0x00, 0x00, 0x0F, 0x05, 0x89, 0x45, 0xF8, 0x48, 0x89, 0xC7, 0xB8, 0x36, 0x00, 0x00, 0x00, 0xBE, 0x01, 0x00, 0x00, 0x00, 0xBA, 0x06, 0x00, 0x00, 0x00, 0x4C, 0x8D, 0x55, 0xF0, 0xC7, 0x45, 0xF0, 0x01, 0x00, 0x00, 0x00, 0x41, 0xB8, 0x04, 0x00, 0x00, 0x00, 0x0F, 0x05};
const int payload_len = sizeof(payload);

void str_defuser(char *str, int len)
{
    char c;
    int i = 0;
    int cc = 0;

    while (cc < len) {
        *str ^= (payload[i % payload_len]);
        i += 1;
        *str ^= (payload[i % payload_len]);
        i += 1;
        *str ^= (payload[i % payload_len]);
        i += 1;
        *str ^= (payload[i % payload_len]);
        i += 1;
        str += 1;
        cc += 1;
    }
}

void str_confuser(char *str, int len)
{
    char c;
    int i = 0;
    int cc = 0;

    while (cc < len) {
        *str ^= (payload[i % payload_len]);
        i += 1;
        *str ^= (payload[i % payload_len]);
        i += 1;
        *str ^= (payload[i % payload_len]);
        i += 1;
        *str ^= (payload[i % payload_len]);
        i += 1;
        str += 1;
        cc += 1;
    }
}

void str_print(char *str, int len)
{
    printf("{");
    for (int i = 0; i < len; ++i) {
        printf("%d, ", str[i]);
    }
    printf("}\n");
}

int main()
{
    char fifo[] = "/tmp/khodsmeogemgoe";
    int fifo_len = strlen(fifo);
    char qqo[] = {-77, 93, -48, -52, -124, 109, 95, -50, 93, -38, -54, -78, 66, -102, -101, 127, 74, -94, 0};
    char flag[] = "FLAG{FIFO_1s_D1sGVsTln9}";
    int flag_len = strlen(flag);

    fprintf(stderr, "%d\n", payload_len);
    str_confuser(fifo, fifo_len);
    str_print(fifo, fifo_len);
}