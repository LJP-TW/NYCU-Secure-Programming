    global _start

    section .text
_start:
    mov rbp, rsp
    ; socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)
    mov rax, 41
    mov rdi, 2
    mov rsi, 2
    mov rdx, 0x11
    syscall
    mov dword [rbp - 8], eax
    ; setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (void *) &broadcastPermission, 
    ;            sizeof(broadcastPermission))
    mov rdi, rax
    mov rax, 54
    mov rsi, 0x1
    mov rdx, 0x6
    lea r10, [rbp - 0x10]
    mov dword [rbp - 0x10], 1
    mov r8, 4
    syscall
    ; /* Broadcast sendString in datagram to clients every 3 seconds*/
LOOP:
    ; sendto(sock, sendString, sendStringLen, 0, (struct sockaddr *) &broadcastAddr, sizeof(broadcastAddr)))
    mov byte [rbp - 0x30], 2
    mov byte [rbp - 0x30 + 1], 0
    mov byte [rbp - 0x30 + 2], 0x22
    mov byte [rbp - 0x30 + 3], 0xad
    mov byte [rbp - 0x30 + 4], 0xc0
    mov byte [rbp - 0x30 + 5], 0xa8
    mov byte [rbp - 0x30 + 6], 0x82
    mov byte [rbp - 0x30 + 7], 1
    mov byte [rbp - 0x30 + 8], 0
    mov byte [rbp - 0x30 + 9], 0
    mov byte [rbp - 0x30 + 10], 0
    mov byte [rbp - 0x30 + 11], 0
    mov byte [rbp - 0x30 + 12], 0
    mov byte [rbp - 0x30 + 13], 0
    mov byte [rbp - 0x30 + 14], 0
    mov byte [rbp - 0x30 + 15], 0
    xor rdi, rdi
    mov edi, [rbp - 8]
    lea rsi, [rsp + 0x18]
    mov rdx, 24
    mov r10, 0
    lea r8, [rbp - 0x30]
    mov r9, 16
    mov rax, 44
    syscall
    ; clock_nanosleep(CLOCK_REALTIME, 0, {tv_sec=3, tv_nsec=0}
    mov rax, 230
    mov rdi, 0
    mov rsi, 0
    lea rdx, [rbp - 0x20]
    mov qword [rbp - 0x20], 3
    mov qword [rbp - 0x20 + 8], 0
    mov r10, 0
    syscall
    jmp LOOP


    section .data
flag: db  "NotFLAG{Hello_Baby_Reverser}", 0