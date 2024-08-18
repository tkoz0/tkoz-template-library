import math
import struct
import pyperclip

def print_and_copy(s:str):
    print(s)
    pyperclip.copy(s)

def toinitlist(n:int):
    assert n >= 0
    if n >= 2**128:
        print(f'given n >= 2**128')
        n %= 2**128
    n1,n0 = divmod(n,2**64)
    print_and_copy(f'{{{n0}{"ull" if n0 >= 2**32 else ""},{n1}{"ull" if n1 >= 2**32 else ""}}}')

def floatbits(n:float):
    # TODO does not support infinity/nan/denormal
    m = struct.unpack('<Q',struct.pack('<d',n))[0]
    mb = bin(m)[2:]
    mb = '0'*(64-len(mb))+mb
    print(mb)
    mant = bin(m%2**52)[2:]
    mant = '0'*(52-len(mant))+mant
    print(f'{"+-"[m>>63]}1.{mant}x2^{((m>>52)&0x7FF)-1023}')

def onebitindexes(n:int):
    l = []
    i = 0
    while n:
        if n % 2 == 1:
            l.append(i)
        i += 1
        n >>= 1
    print(','.join(map(str,l[::-1])))
