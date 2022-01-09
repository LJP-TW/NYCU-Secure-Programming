#include <Windows.h>
#include <debugapi.h>
#include <winreg.h>
#include <iostream>
#include <stdio.h>
#include <cpuid.h>

using namespace std;

void nothing(char *real_flag)
{
    return;
}

void do_flag()
{
    int flag[] = {232, 226, 239, 233, 213, 220, 157, 216, 157, 220, 221, 157, 241, 227, 207, 155, 250, 157, 252, 211};
    int keykey = 174;
    char real_flag[0x100];
    int i;

    for (i = 0; i < sizeof(flag) / 4; ++i) {
        real_flag[i] = flag[i] ^ keykey;
    }

    real_flag[i] = 0;

    nothing(real_flag);

    exit(1);
}

int real_golden_func(void* ExceptionRecord, void* EstablisherFrame, struct _CONTEXT* ContextRecord, void* DispatcherContext)
{
    char *start_addr = (char *)do_flag;
    int size = 0x100;
    DWORD i;

    if (!VirtualProtect((LPVOID) 0x401000, 0x1000, PAGE_EXECUTE_READWRITE, &i)) {
        exit(1);
	}

    for (int i = 0; i < size; ++i) {
        start_addr[i] ^= 0x87;
    }

    if (!VirtualProtect((LPVOID) 0x401000, 0x1000, PAGE_EXECUTE_READ, &i)) {
        exit(1);
	}

	ContextRecord->Rip = (DWORD64) do_flag;

	return 0;
}

void golden_func()
{
    int zero = 0;
    int a;

    try {
        throw overflow_error("");
    } catch (...) {
        printf("GG\n");
    }
}

/*
If HV presence confirmed then it is good to know which type of hypervisor we have
When CPUID is called with EAX=0x40000000, cpuid return the hypervisor signature.
*/
BOOL cpuid_hypervisor_vendor()
{
	INT CPUInfo[4] = { -1 };
	CHAR szHypervisorVendor[0x40];
	WCHAR *pwszConverted;
    int eax = 0x40000000, ebx, ecx, edx;

	BOOL bResult = FALSE;

	const char* szBlacklistedHypervisors[] = {
		"KVMKVMKVM\0\0\0",	/* KVM */
		"Microsoft Hv",		/* Microsoft Hyper-V or Windows Virtual PC */
		"VMwareVMware",		/* VMware */
		"XenVMMXenVMM",		/* Xen */
		"prl hyperv  ",		/* Parallels */
		"VBoxVBoxVBox",		/* VirtualBox */
	};
	WORD dwlength = sizeof(szBlacklistedHypervisors) / sizeof(szBlacklistedHypervisors[0]);

	// __cpuid with an InfoType argument of 0 returns the number of
	// valid Ids in CPUInfo[0] and the CPU identification string in
	// the other three array elements. The CPU identification string is
	// not in linear order. The code below arranges the information 
	// in a human readable form.
    asm ("mov $0x40000000, %%rax\n\t"
         "cpuid\n\t"
         "mov %%ebx, %[CPUInfo1]\n\t"
         "mov %%ecx, %[CPUInfo2]\n\t"
         "mov %%edx, %[CPUInfo3]\n\t"
         : [CPUInfo1] "=m" (CPUInfo[1]), [CPUInfo2] "=m" (CPUInfo[2]), [CPUInfo3] "=m" (CPUInfo[3])
         :
         :
    );

	memset(szHypervisorVendor, 0, sizeof(szHypervisorVendor));
	memcpy(szHypervisorVendor, CPUInfo + 1, 12);

	for (int i = 0; i < dwlength; i++)
	{
		bResult = (strcmp(szHypervisorVendor, szBlacklistedHypervisors[i]) == 0);

		if (bResult) {
            printf("[!] %s\n", szHypervisorVendor);
            printf("You use VM ... bad reverse engineer :(((\n");
			return TRUE;
        }
	}

    golden_func();

	return FALSE;
}

int evil_func()
{
    int debugger;

    printf("Bye~\n");

    asm ("call SELF\n\t"
         "SELF:\n\t"
         "pop %%rax\n\t"
         "add $0xd, %%rax\n\t"
         "jmp *%%rax\n\t"
         :
         :
         :
    );

    asm ("1: .byte 0xe9, 0x80, 0x87, 0x55, 0x66, 0x01 \n\t":::);

    if (IsDebuggerPresent()) {
        printf("You use debugger ... bad reverse engineer :(((\n");
        exit(1);
    }

    cpuid_hypervisor_vendor();
}

int main()
{
    void *p;
    p = (void *) real_golden_func;
    p = (void *) golden_func;
    p = (void *) do_flag;
    printf("Unpack me \U0001F608\n");

    // call evil function
    evil_func();
    // asm ("call SELF\n\t"
    //      "SELF:\n\t"
    //      "pop %%rax\n\t"
    //      "add $-0x31, %%rax\n\t"
    //      "jmp *%%rax\n\t"
    //      :
    //      :
    //      :);
}
