# use mingw32-make.exe to make

CFLAGS = -Wl,--dynamicbase -s -static

all: unpackme_patch1.exe
	upx unpackme_patch1.exe -o nani.exe

unpackme_patch1.exe: unpackme.exe
	python patch.py

unpackme.exe:
	@echo "Compiling..."
	g++ $(CFLAGS) -o unpackme.exe unpackme.cpp
