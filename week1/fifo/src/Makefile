all: enc_payload.h
	gcc hw1_w.c -o fifo

	strip fifo

enc_payload.h: hw1r
	./genheader.py

hw1r:
	gcc hw1_r.c -o hw1r -z execstack

	strip hw1r

str_confuser:
	gcc str_confuser.c -o str_confuser

shellcode:
	nasm -felf64 shellcode.asm
	ld shellcode.o -o shellcode

