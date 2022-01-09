#!/usr/bin/env python3

with open('unpackme.exe', 'rb') as f:
    content = list(f.read())

# lea functions
start_addrs = [0xe0a, 0xe15, 0xe20]
size        = 0x7

for start_addr in start_addrs:
    for i in range(size):
        content[start_addr + i] = 0x90

# do_flag address
start_addr = 0x9af
size       = 0x100

for i in range(size):
    content[start_addr + i] ^= 0x87

# unwindinfo of golden_func
unwindinfo = 0xbd0a4
handler    = bytes.fromhex('000016FB')[::-1]

for i in range(len(handler)):
    content[unwindinfo + 0x10 + i] = handler[i]

with open('unpackme_patch1.exe', 'wb') as f:
    f.write(bytes(content))
