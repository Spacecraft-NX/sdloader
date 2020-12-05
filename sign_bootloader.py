'''
Copyright (c) 2020 Spacecraft-NX

This program is free software; you can redistribute it and/or modify it
under the terms and conditions of the GNU General Public License,
version 2, as published by the Free Software Foundation.

This program is distributed in the hope it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
'''

import sys, os, struct, hashlib
from Crypto.Signature import pss
from Crypto.PublicKey import RSA
from Crypto.Hash import SHA256
from Crypto.Cipher import AES

def egcd(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = egcd(b % a, a)
        return (g, x - (b // a) * y, y)

def modinv(a, m):
    g, x, y = egcd(a, m)
    if g != 1:
        raise Exception('modular inverse does not exist')
    else:
        return x % m

N = 0xFF696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696969696959
E = 0x10001
P = 19
Q = N / 19

assert N == P * Q

D = modinv(E, (P - 1) * (Q - 1))

assert(pow(pow(5, D, N), E, N) == 5)

RSA_KEY = RSA.construct((N, E, D, P, Q), True)

def sign_pss(dat):
    sig = pss.new(RSA_KEY).sign(SHA256.new(dat))[::-1]
    assert len(sig) == 0x100
    return sig

#    LDR R0, =0x70012000
#    MOV R1, #0x1000
#    STR R1, [R0, #0x14]
#    
#    LDR R1, =0xD000144
#    STR R1, [R0, #0x304]
#
#    MOV R2, #0
#    MOV R1, #0xD8
#    STR R1, [R0, #0x31C]
#    STR R2, [R0, #0x320]
#    MOV R1, #0xD9
#    STR R1, [R0, #0x31C]
#    STR R2, [R0, #0x320]
#    MOV R1, #0xDA
#    STR R1, [R0, #0x31C]
#    STR R2, [R0, #0x320]
#    MOV R1, #0xDB
#    STR R1, [R0, #0x31C]
#    STR R2, [R0, #0x320]
#
#    ADR R3, ll
#    LDR R1, [R3, #8]
#    LSRS R1, R1, #4
#    SUBS R1, #1
#    STR R1, [R0, #0x318]
#    
#    STR R3, [R0, #0x18]
#    STR R3, [R0, #0x24]
#    
#    LDR R1, [R0, #0x804]
#    STR R1, [R0, #0x804]
#
#    LDR R1, [R0, #0x10]
#    STR R1, [R0, #0x10]
#    
#    MOV R1, #1
#    STR R1, [R0, #0x08]
#
#    MOV R4, #0x10
#loop:
#    LDR R1, [R0,#0x10]
#    TST R1, R4
#    BEQ loop
#
#    LDR R1, [R3, #4]
#    BX R1
#ll:
#    .word 0
#    .word 0x40010240
#    .word 0xFDC0
LDR = '\xE0\xBD\x56\x6B\xE7\x78\xF6\x1B\x29\xC8\xE2\xE8\xC7\xA5\x3D\xDD'+ \
      '\x9F\xD4\x99\x23\x0F\x30\xCF\x56\x3D\x7D\x12\x20\x34\xF0\xAD\x4C'+ \
      '\xC5\xA2\x51\xD2\x24\x9D\x87\x9B\xFB\xB9\x74\x00\x8B\xD7\xEC\x1D'+ \
      '\x95\x1D\x33\xEF\xE5\xBD\x32\x49\xDC\x96\x01\x47\x4A\x40\x4D\xA8'+ \
      '\x32\x92\xDA\x68\x2E\x7D\xD9\xEA\x47\xFF\xB3\x0D\x1D\xD9\xF7\x42'+ \
      '\xDA\x96\x45\x6D\x86\xAF\xEC\x45\x79\x0F\xDD\x74\x59\x53\xF8\x01'+ \
      '\x92\x64\x64\xCC\x58\x75\xEC\xA3\x52\xEC\xD2\xA1\xC5\x5E\x06\x9E'+ \
      '\x36\x44\xE4\x61\x7F\x71\xBD\x31\x85\x4D\x46\xFA\xA9\x7E\x45\x22'+ \
      '\xDA\x58\x62\xD3\x8D\x51\x93\xE8\x9B\x39\x22\x75\xB4\xF1\x83\xA9'+ \
      '\x22\xD3\xCD\x8F\xB5\x45\xE5\x06\x39\x6B\xDA\x7C\x25\xE1\x34\x7F'+ \
      '\xFB\x79\xAF\x2F\x35\x41\x45\xFC\x86\xE6\x1E\x84\xB1\x25\x3F\xDD'
    
def getldr():
    return LDR + '\x00' * 32

def generate_unified_bootloader(data):
    if len(data) % 16 != 0:
        data += '\00' * (16 - (len(data) % 16))
    
    data = getldr() + data

    nonce = os.urandom(0x20)
    sha256hash = hashlib.sha256(data).digest()
    length = len(data)
    load_addr = 0x40010170
    entry_address = 0x40010170
    
    header = struct.pack('32s32sIIII16x', nonce, sha256hash, 9, length, load_addr, entry_address)
    signature = sign_pss(header)
    signature_and_header = struct.pack('16x256s96s', signature, header)

    return signature_and_header + data

def generate_erista_bct(data):
    devparams = struct.pack('II56x', 0x9, 0x2)
    sdramparams = struct.pack('1896x')
    bootloader = struct.pack('IIIIIII16x256s', 9, 0xFC, 0, len(data), 0x40010000, 0x40010240, 3, sign_pss(data))
    empty_bootloader = struct.pack('4x4x4x4x4x4x4x16x256x')
    signed = struct.pack('16x16xIIIIII', 0x210001, 0xE, 0x9, 0x1000000, 0x1, 0x4) + devparams + struct.pack('I', 0) + sdramparams * 4 + struct.pack('I', 1) + bootloader + empty_bootloader * 3 + struct.pack('B', 0) + struct.pack('I', 0) + struct.pack('I', 0) + struct.pack('I14x', 0x80000000) + struct.pack('5x')

    signature = struct.pack('16x256s', sign_pss(signed))
    unsigned = struct.pack('IBB6x516x256s', 0x200, 0xF, 0xE, ('%0512X' % N).decode('hex')[::-1]) + signature + struct.pack('4x32x196x4x4x')

    return unsigned + signed


def main(argc, argv):
    if argc != 2:
        print 'Usage: %s file' % argv[0]
        return 1

    data = open(argv[1], 'rb').read()
    if len(data) > 0x10000 - 0x240:
        print 'Too big bootloader!'
        return -1

    data = generate_unified_bootloader(data)

    with open('%s.enc' % argv[1], 'wb') as f:
        f.write(data)

    bct = generate_erista_bct(data)

    with open('%s.bct' % argv[1], 'wb') as f:
        f.write(bct)

    return 0

if __name__ == '__main__':
    sys.exit(main(len(sys.argv), sys.argv))