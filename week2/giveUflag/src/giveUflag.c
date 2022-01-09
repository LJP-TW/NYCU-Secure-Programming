#include <stdio.h>
#include <wchar.h>
#include <synchapi.h>

#define SLEEP_TIME 604800000

char *kingOfFlavor = "YOU_USE_HAIYA_WHEn_YOU'RE_DISAPPOINTED_MMSSGG";

char* GetKernel32(void)
{
    char *peb;
    char *ImageBase;
    char *Ldr;
    char *fLink_head;
    char *fLink;
    char *Kernel32Base;
    wchar_t *DllName;
    
    asm ("mov %%gs:0x60, %%rax\n\t" 
         "mov %%rax, %[peb]\n\t"
         : [peb] "=m" (peb)
         : 
         :);

    ImageBase = *(void **)(peb + 0x10);
    Ldr = *(void **)(peb + 0x18);
    fLink_head = *(void **)(Ldr + 0x20);
    DllName = *(void **)(fLink_head + 0x50);
    fLink = *(void **)(fLink_head);

    while (fLink != fLink_head) {
        DllName = *(void **)(fLink + 0x50);

        if (!wcsicmp(DllName, L"kernel32.dll")) {
            break;
        }

        fLink = *(void **)(fLink);
    }

    Kernel32Base = *(void **)(fLink + 0x20);

    return Kernel32Base;
}

char *GetSleep(char *kernel32base)
{
    char *pe;
    char *ExportDirectory;
    char *names;
    int numberOfFunctions;
    char *AddressOfFunctions;
    char *AddressOfNames;
    char *AddressOfSleep;
    void (*Kernel32Sleep)(int);
    // char flags[] = "FLAG{PaRs1N6_PE_aNd_D11_1S_50_C00111!!!!!111}"
    int xor_flag[] = {31, 3, 20, 24, 46, 3, 36, 13, 59, 112, 7, 111, 30, 15, 18, 23, 36, 32, 59, 6, 11, 100, 22, 13, 116, 12, 27, 124, 99, 30, 19, 96, 127, 120, 127, 101, 100, 101, 126, 108, 108, 98, 98, 118, 58};
    char buf[0x100] = { 0 };
    int i;

    pe = kernel32base + *(int *)(kernel32base + 0x3c);
    ExportDirectory = kernel32base + *(int *)(pe + 0x88);
    names = kernel32base + *(int *)(ExportDirectory + 0xc);
    numberOfFunctions = *(int *)(ExportDirectory + 0x14);
    AddressOfFunctions = kernel32base + *(int *)(ExportDirectory + 0x1c);
    AddressOfNames = kernel32base + *(int *)(ExportDirectory + 0x20);

    for (i = 0; i < numberOfFunctions; ++i) {
        char *functionName;
        functionName = kernel32base + *(int *)(AddressOfNames + i * 4);

        if (!stricmp(functionName, "sleep")) {
            break;
        }
    }

    AddressOfSleep = kernel32base + *(int *)(AddressOfFunctions + i * 4);

    Kernel32Sleep = (void *)AddressOfSleep;

    Kernel32Sleep(SLEEP_TIME);

    printf("https://i.ytimg.com/vi/_T2c8g6Zuq8/maxresdefault.jpg\n");

    Kernel32Sleep(SLEEP_TIME);

    printf("https://i.ytimg.com/vi/MY4sFW83yxg/maxresdefault.jpg\n");

    Kernel32Sleep(SLEEP_TIME);

    printf("https://i.ytimg.com/vi/OVuZ4vGxVKE/maxresdefault.jpg\n");

    for (int i = 0; i < 45; ++i) {
        buf[i] = xor_flag[i] ^ (int)kingOfFlavor[i];
    }

    printf("%s\n", buf);

    return AddressOfSleep;
}

int GiveUFlag(void)
{
    char *Kernel32Base;
    
    Kernel32Base = GetKernel32();

    GetSleep(Kernel32Base);
}

int main(void)
{
    GiveUFlag();
}