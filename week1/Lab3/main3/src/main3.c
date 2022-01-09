#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define __fini1 __attribute__ ((destructor (102)))
#define __fini2 __attribute__ ((destructor (101)))

char g_buf[0x100];

typedef unsigned long long ULL;

static inline int syscall(ULL rax, ULL rdi, ULL rsi, ULL rdx)
{
    asm volatile(
              "movq %3, %%rdx;"
              "movq %2, %%rsi;"
              "movq %1, %%rdi;"
              "movq %0, %%rax;"
              "syscall;" 
              :
              : "r" (rax), "r" (rdi), "r" (rsi), "r" (rdx)
              : "rax", "rdi", "rsi", "rdx"
            );
}

__fini1 void RunFunc1()
{
    char __buf[] = {75, 80, 68, 79, 132, 76, 113, 97, 120, 99, 110, 122, 98, 125, 96, 124, 124, 117, 106, 103, 102, 127, 111, 122, 118, 106, 118, 127, 122, 110, 119, 123, 85, 85, 76, 80, 93, 75, 85, 75, 76, 79, 83, 79, 66, 84, 172, 0};

    for (int i = 0; i < 47; ++i) {
        __buf[i] ^= i;
        __buf[i] -= 5;
    }

    strcpy(g_buf, __buf);
}

__fini2 void RunFunc2()
{
    int fd;
    char b[] = {52, 122, 116, 120, 48, 102, 121, 107, 104, 113, 90, 102, 132, 113, 105, 107, 120, 131, 125, 38, 126, 43, 117, 42, 48, 46, 126, 109, 124, 126, 125, 117, 74, 86, 78, 74, 88, 91, 13, 70, 73, 77, 82, 0};

    for (int i = 0; i < 43; ++i) {
        b[i] -= 5;
        b[i] ^= i;
    }

    // fd = open("/tmp/drake_jsajicoj2m3f230cskdfoepkfws.flag", O_CREAT | O_TRUNC | O_WRONLY, 0x000);
    fd = syscall(2, b, O_CREAT | O_TRUNC | O_WRONLY, 0x000);

    if (fd>=0) {
        // dup2(fd, 1);
        syscall(33, fd, 1, 0);

        printf("%s\n", g_buf);

        // close(fd);
        syscall(3, fd, 0, 0);
    }
}

int main()
{
    char __buf[] = "NotFLAG{Drake_not_liking_something}";

    strcpy(g_buf, __buf);

    printf("g_buf: %s\n", g_buf);
}

