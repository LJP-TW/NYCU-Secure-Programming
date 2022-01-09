#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <memoryapi.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void NTAPI MY_TLS_CALLBACK(PVOID DllHandle, DWORD Reason, PVOID Reserved);
void NTAPI MY_TLS_CALLBACK2(PVOID DllHandle, DWORD Reason, PVOID Reserved);

#ifdef _M_AMD64
#pragma comment (linker, "/INCLUDE:_tls_used")
#pragma comment (linker, "/INCLUDE:p_tls_callback1")
#pragma const_seg(".CRT$XLF")
EXTERN_C const PIMAGE_TLS_CALLBACK p_tls_callback1[] = { MY_TLS_CALLBACK, MY_TLS_CALLBACK2, 0};
// EXTERN_C const PIMAGE_TLS_CALLBACK p_tls_callback1[] = { MY_TLS_CALLBACK, MY_TLS_CALLBACK2, 0 };
#pragma const_seg()
#endif

#ifdef _M_IX86
#pragma comment (linker, "/INCLUDE:__tls_used")
#pragma comment (linker, "/INCLUDE:_p_tls_callback1")
#pragma data_seg(".CRT$XLF")
EXTERN_C PIMAGE_TLS_CALLBACK p_tls_callback1[] = { MY_TLS_CALLBACK,MY_TLS_CALLBACK2,0 };
#pragma data_seg()
#endif

//             FLAG{WOW_YOU_F0UND_M3!!!!!!!!!!!!?!}
//             FLNotAG{TRY_HARDER_TRY_HARDER_TRY_HARDER}
//             FLAGNot{GGGG_Not_FLAG_AGAIN........................}
char flag[] = "NotFLAG{Hello_My_Friend_This_15N0T_Flag_biblethump_}";

char passwd[] = "Th3_Pa55wd";

int init_flag(void)
{
    char gggg[] = { 78, 111, 123, 110, 118, 111, 116, 123, 91, 112, 114, 116, 120, 80, 112, 73, 69, 82, 97, 124, 112, 104, 122, 80, 84, 115, 99, 24, 35, 64, 79, 50, 71, 37, 57, 41, 16, 11, 12, 35, 49, 71 };
	memcpy(flag, gggg, sizeof(gggg));
}

void NTAPI MY_TLS_CALLBACK(PVOID DllHandle, DWORD Reason, PVOID Reserved)
{
    char realpwd[] = { 'R', 'E', 'A', 'L', 'P', 'W', 'D', 0 };
    switch (Reason)
    {
    case DLL_PROCESS_ATTACH:
        memcpy(passwd, realpwd, sizeof(realpwd));
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
}
void NTAPI MY_TLS_CALLBACK2(PVOID DllHandle, DWORD Reason, PVOID Reserved)
{
    char yoasobi[] = { 'Y', 'o', 'a', 's', 'o', 'b', 'i', 0 };
    switch (Reason)
    {
    case DLL_PROCESS_ATTACH:
        memcpy(passwd, yoasobi, sizeof(yoasobi));
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
}

static void finalize(void)
{
    HANDLE hFile;
    BOOL bErrorFlag = FALSE;
    UINT uRetVal = 0;
    DWORD dwRetVal = 0;
    DWORD dwBytesWritten = 0;
    TCHAR lpTempPathBuffer[MAX_PATH];
    TCHAR szTempFileName[MAX_PATH];
    int keykey[] = { 0, 0, 15, 40, 15, 22, 8, 44, 11, 11, 22, 10, 23, 7, 98, 17, 11, 22, 0, 25, 97, 120, 126, 105, 96, 115, 101, 100, 115, 126, 117, 115, 120, 96, 105, 60, 82 };
    char real_flag[0x100];
    
    for (int i = 0; i < sizeof(keykey) / 4; ++i) {
        real_flag[i] = flag[i] ^ keykey[i];
    }
        
    // Gets the temp path env string (no guarantee it's a valid path).
    dwRetVal = GetTempPath(MAX_PATH,          // length of the buffer
                           lpTempPathBuffer); // buffer for path 

    if (dwRetVal > MAX_PATH || (dwRetVal == 0)) {
        return (1);
    }

    // Generates a temporary file name. 
    uRetVal = GetTempFileName(lpTempPathBuffer, // directory for tmp files
                              TEXT("a_"),       // temp file name prefix 
                              0,                // create unique name 
                              szTempFileName);  // buffer for name 

    if (uRetVal == 0) {
        return (1);
    }

    hFile = CreateFile(szTempFileName,         // name of the write
                       GENERIC_WRITE,          // open for writing
                       0,                      // do not share
                       NULL,                   // default security
                       CREATE_ALWAYS,          // overwrite existing
                       FILE_ATTRIBUTE_NORMAL,  // normal file
                       NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
        return;
    }

    bErrorFlag = WriteFile(
        hFile,              // open file handle
        real_flag,          // start of data to write
        sizeof(keykey) / 4, // number of bytes to write
        &dwBytesWritten,    // number of bytes that were written
        NULL);              // no overlapped structure

    CloseHandle(hFile);
}

INITIALIZER(initialize)
{
	init_flag();
	atexit(finalize);
}

int main(int argc, char **argv)
{
    if (argc < 2)
        return 0;

    if (!strcmp(argv[1], passwd)) {
        int key[] = { 8, 35, 53, 1, 2, 46, 51, 0, 15, 34, 43, 43, 48, 17, 34, 13, 0, 0, 62, 40, 34, 49, 37, 24, 21, 33, 39, 93, 113, 31, 27, 96, 30, 122, 113, 104, 66, 79, 73, 113, 76, 71, 76, 66, 75, 90, 70, 91, 67, 94, 113, 0 };
        
        for (int i = 0; i < sizeof(key) / 4; ++i) {
            flag[i] ^= key[i];
        }

        printf("H3ll, my friend\nI already put flag in the FS, go to find the onepiece!\n");
    }
}
