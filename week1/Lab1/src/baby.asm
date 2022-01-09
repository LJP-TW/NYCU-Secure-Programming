    global _start

    section .text
_start:
    mov rbp, rsp
    xor rax, rax
    inc rax
    jnz Baby_open
Baby_bye:
    mov rax, 60
    xor rdi, rdi
    syscall
Baby_open:
    inc rax
    mov rdi, fn
    xor rsi, rsi
    or  rsi, 0x001
    or  rsi, 0x040
    or  rsi, 0x200	
    xor rdx, rdx
    or  rdx, 0x777
    syscall
    mov qword [rbp+0x100], rax
    xor rax, rax
    xor r8, r8
    mov r12, key
    jnz Baby_bye
    jz Baby_Loop_cmp
Baby_Loop:
    mov r10, flag
    mov r11b, byte [r10 + r8]
    xor r11b, byte [r12 + r8]
    mov byte [rbp+0x200], r11b
    call Baby_write
    inc r8
Baby_Loop_cmp:
    cmp r8, 29
    jnz Baby_Loop
    mov rax, 3
    mov rdi, [rbp+0x100]
    syscall
    jmp Baby_bye
Baby_write:
    mov rax, 1
    mov rdi, qword [rbp+0x100]
    xor rdx, rdx
    inc rdx
    lea rsi, [rbp+0x200]
    syscall
    ret

    section .data
fn:   db  "/tmp/baby_aksgmsdkvmdfiivjdd", 0
flag: db  "NotFLAG{Hello_Baby_Reverser}", 0
key:  db  8, 35, 53, 1, 55, 21, 47, 18, 59, 58, 5, 31, 48, 38, 45, 20, 16, 38, 57, 62, 4, 17, 58, 19, 17, 6, 22, 0, 0
