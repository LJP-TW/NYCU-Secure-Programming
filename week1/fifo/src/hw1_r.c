#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

#define shellcode_len 216

typedef void(*function)(void);

void str_defuser(char *str, int len, char *payload, int payload_len)
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

int main(void)
{
    int	readfd;
    char shellcode[shellcode_len] = { 0 };
    char flag[] = {-38, 101, -4, -5, -48, 73, 120, -8, 121, -32, -115, -78, 120, -75, -52, 124, 102, -57, -50, -24, -42, 127, -1, -125, 0};
    int flag_len = sizeof(flag);
    function fp = (function)&shellcode;

    if ((readfd = open("/tmp/bnpkevsekfpk3/aw3movsdirnqw", O_RDONLY)) < 0) {
        perror("open()");
        exit(1);
    }

    read(readfd, shellcode, shellcode_len);

    close(readfd);

    if ((unlink("/tmp/bnpkevsekfpk3/aw3movsdirnqw")) < 0) {
        perror("unlink()");
        exit(1);
    }

    str_defuser(flag, flag_len - 1, shellcode, 65);

    fp();
}
