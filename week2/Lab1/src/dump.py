# Run in IDA python interpretor
# Dump make_flag_great_again
addr_start = 0x140001180
addr_end   = 0x140001249
with open('make_flag_great_again.h', 'wb') as f:
    content = GetManyBytes(addr_start, (addr_end - addr_start))
    f.write('char my_func[] = {')
    for b in content:
        f.write(str(ord(b)))
        f.write(',')
    f.write('};\n')
    f.write('int my_func_len = ')
    f.write(str(len(content)))
    f.write(';\n')
