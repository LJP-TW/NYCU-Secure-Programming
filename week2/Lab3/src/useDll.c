#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memoryapi.h>

__declspec(dllexport) int __cdecl YoDllFunc1 (char *str, int passwd1, int passwd2);

__declspec(dllexport) int main(void)
{
    char *buf;
    int passwd1, passwd2;
    int ret;

    buf = VirtualAlloc(NULL, 0x1000, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

    printf("%p\n", main);
    
    scanf("%d %d", &passwd1, &passwd2);

    ret = YoDllFunc1(buf, passwd1, passwd2);

    printf("%s\n", buf);

    return 0;
}

