#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define __fini1 __attribute__ ((destructor (102)))
#define __fini2 __attribute__ ((destructor (101)))

char g_buf[0x100];

typedef unsigned long UL;

static inline int my_syscall(UL r1, UL r2, UL r3, UL r4)
{
    asm volatile(
              "movl %3, %%edx;"
              "movl %2, %%ecx;"
              "movl %1, %%ebx;"
              "movl %0, %%eax;"
              "int $0x80;" 
              :
              : "" (r1), "" (r2), "" (r3), "" (r4)
              : "eax", "ebx", "ecx", "edx"
            );
}

__fini1 void RunFunc1()
{
    char __buf[] = {67, 74, 70, 79, 114, 78, 121, 109, 102, 107, 80, 124, 120, 121, 122, 122, 114, 73, 111, 43, 43, 69, 122, 114, 121, 65, 118, 78, 85, 125, 19, 92, 29, 22, 90, 0};

    for (int i = 0; i < 35; ++i) {
        __buf[i] ^= (i + 5);
    }

    strcpy(g_buf, __buf);
}

__fini2 void RunFunc2()
{
    int fd;
    char b[] = {42, 114, 106, 120, 38, 110, 121, 109, 102, 107, 80, 102, 124, 123, 126, 113, 115, 36, 47, 43, 115, 124, 126, 113, 118, 120, 114, 83, 15, 68, 79, 69, 66, 0};

    for (int i = 0; i < 33; ++i) {
        b[i] ^= (i + 5);
    }

    // fd = open("/tmp/drake_vmimef283jfemkfms.flag", O_CREAT | O_TRUNC | O_WRONLY, 0x000);
    fd = my_syscall(5, b, O_CREAT | O_TRUNC | O_WRONLY, 0x000);

    if (fd < 0) {
        return;
    }
    // dup2(fd, 1);
    my_syscall(63, fd, 1, 0);

    printf("%s\n", g_buf);

    // close(fd);
    my_syscall(6, fd, 0, 0);
}

int main()
{
    char __buf[] = "NotFLAG{Drake_not_liking_something}";

    strcpy(g_buf, __buf);

    printf("g_buf: %s\n", g_buf);
}

