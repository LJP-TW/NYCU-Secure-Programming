#!/usr/bin/env python3

with open('3xc3pt.exe', 'rb') as f:
    content = list(f.read())

func_rva = bytes.fromhex('1100')[::-1]

lea_func = 0xadd

# unwindinfo of main
unwindinfo = 0x1a9b8

for i in range(len(func_rva)):
    content[unwindinfo + 8 + i] = func_rva[i]

for i in range(7):
    content[lea_func + i] = 0x90

with open('3xc3pt_patch.exe', 'wb') as f:
    f.write(bytes(content))
