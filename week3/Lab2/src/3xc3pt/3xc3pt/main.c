#include <Windows.h>
#include <stdio.h>

void do_flag(void)
{
	printf("Try-catch : Never gonna give u up\n");
}

int func(void* ExceptionRecord, void* EstablisherFrame, struct _CONTEXT* ContextRecord, void* DispatcherContext)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	char text[0x100];
	int tttt[] = { 28, 85, 30, 107, 106, 64, 112, 116, 86, 104, 110, 84, 108, 84, 28, 85, 30, 107, 106, 64, 112, 116, 86, 104, 110, 84, 108, 84, 28, 85, 30, 107, 106, 64, 112, 116, 86, 104, 110, 84, 108, 84, 28, 85, 30, 107, 106, 64, 112, 116, 86, 104, 110, 84, 108 };
	int key[] = { 121, 58, 124, 15, 50, 52, 59, 100, 27, 20, 9, 24, 126, 25, 120, 41, 109, 56, 29, 60, 0, 18, 61, 20, 44, 27, 24, 22, 70, 5, 98, 42, 44, 60, 35, 22, 1, 40, 37, 68, 43, 40, 75, 25, 98, 27, 1, 38, 12, 8, 42, 118, 18, 74, 50 };

	for (int i = 0; i < sizeof(key) / 4; ++i) {
		text[i] = tttt[i] ^ 0x23;
	}

	for (int i = 0; i < sizeof(key) / 4; ++i) {
		text[i] ^= key[i];
	}

	// Start the child process. 
	if (!CreateProcess(NULL,   // No module name (use command line)
		text,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi)           // Pointer to PROCESS_INFORMATION structure
		)
	{
		// Error, Never mind :)
	}

	ContextRecord->Rip = do_flag;

	return 0;
}

int main(int argc, char **argv)
{
	void* p = func;
	int zero = 0;
	int a;
	__try {
		a = 1 / zero;
	}
	__except (1) {
		printf("Try-catch : Never gonna let u downnnn\n");
	}
}
