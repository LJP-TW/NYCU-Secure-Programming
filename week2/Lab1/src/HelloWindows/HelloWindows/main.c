#include <Windows.h>
#include <memoryapi.h>

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "make_flag_great_again.h"

#ifdef __cplusplus
#define INITIALIZER(f) \
        static void f(void); \
        struct f##_t_ { f##_t_(void) { f(); } }; static f##_t_ f##_; \
        static void f(void)
#elif defined(_MSC_VER)
#pragma section(".CRT$XCU",read)
#define INITIALIZER2_(f,p) \
        static void f(void); \
        __declspec(allocate(".CRT$XCU")) void (*f##_)(void) = f; \
        __pragma(comment(linker,"/include:" p #f "_")) \
        static void f(void)
#ifdef _WIN64
#define INITIALIZER(f) INITIALIZER2_(f,"")
#else
#define INITIALIZER(f) INITIALIZER2_(f,"_")
#endif
#else
#define INITIALIZER(f) \
        static void f(void) __attribute__((constructor)); \
        static void f(void)
#endif

// FLAG{H3ll_W1nd0wS}
char flag[] = "NotFLAG{XXXXXXX_15_S0_GREAT_15NT_IT?}";

int init_flag(void)
{
	memcpy(&flag[8], "Windows", 7);
}

static void finalize(void)
{
	printf("finalize, can you find me?\n");
}

INITIALIZER(initialize)
{
	printf("initialize, can you find me?\n");
	init_flag();
	atexit(finalize);
}

typedef int (*FUNC_printf) (const char* const format, ...);
typedef int (*FUNC_scanf) (const char* const format, ...);
typedef void* (*fp)(FUNC_printf p_printf, FUNC_scanf p_scanf, int the_key[], int the_key_len, char *flag);

void make_flag_great_again(FUNC_printf p_printf, FUNC_scanf p_scanf, int the_key[], int the_key_len, char *flag)
{	
	char format[] = { 107, 101, 121, 58, 32, 0 }; // "key: "
	char format2[] = { 37, 100, 0 }; // "%d"
	int key; // 675767058

	p_printf(format);
	p_scanf(format2, &key);
	
	for (int i = 0; i < the_key_len; ++i) {
		the_key[i] -= key;
		flag[i] ^= the_key[i];
	}
}

int main()
{
	int i;
	fp fp_ptr;
	int the_key[] = { 675767066, 675767093, 675767111, 675767059, 675767113, 675767067, 675767174, 675767081, 675767117, 675767112, 675767115, 675767143, 675767059, 675767077, 675767125, 675767098, 675767156, 675767130, 675767153 };

	FUNC_printf p_printf = printf;
	FUNC_scanf p_scanf = scanf;

	fp_ptr = (fp)malloc(0x1000);

	if (!VirtualProtect(fp_ptr, 0x1000, PAGE_EXECUTE_READWRITE, &i)) {
		printf("GG: %d\n", GetLastError());
	}

	memcpy(fp_ptr, my_func, my_func_len);
	
	// make_flag_great_again(p_printf, p_scanf, the_key, sizeof(the_key) / 4, flag);
	fp_ptr(p_printf, p_scanf, the_key, sizeof(the_key) / 4, flag);

	printf("%s\n", flag);
}
