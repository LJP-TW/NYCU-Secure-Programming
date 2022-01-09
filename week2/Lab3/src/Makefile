# use mingw32-make.exe to make

CFLAGS = -Wl,--dynamicbase -s

all:
	@echo "Compiling..."
	gcc $(CFLAGS) -shared -o otherDll.dll otherDll.c
	gcc $(CFLAGS) -L ./ -l otherDll -shared -o hiDll.dll hiDll.c
	gcc $(CFLAGS) -L ./ -l hiDll -o useDll.exe useDll.c

