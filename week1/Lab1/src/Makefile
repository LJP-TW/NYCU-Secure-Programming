all:
	nasm -felf64 baby.asm
	ld baby.o -o baby

	rm -rf *.o

	strip baby
