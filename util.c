#include <string.h>
#include "util.h"

void bit_rot_left(unsigned char *bits, int size, int count)
{
    int fbit, lbit, i, j;
    if (size > 0) {
		for (j = 0; j < count; j++) {
			for (i = 0; i <= ((size - 1) / 8); i++) {
				lbit = bit_get(&bits[i], 1);
				if (i == 0) {
					fbit = lbit;
				} else {
					bit_set(&bits[i-1], 8, lbit);
				}
				bits[i] = bits[i] << 1;
			}
			bit_set(bits, size, fbit);
		}
    }
}

void bit_set(unsigned char *mem, unsigned int bitnum, unsigned int on) {
    bitnum--; //we're using 1 indexed bitnums
    unsigned int nth_byte = bitnum / 8;
    unsigned int offset = bitnum % 8;

    if (on != 0) {
	*(mem + nth_byte) |= ((0x80 >> offset) & 0xff);
    } else {
	*(mem + nth_byte) &= ~(0x80 >> offset);
    }
}

unsigned int bit_get(unsigned char *mem, unsigned int bitnum)
{
    bitnum--;
    unsigned int nth_byte = bitnum / 8;
    unsigned int offset = bitnum % 8;
    return (*(mem + nth_byte) & (0x80 >> offset)) != 0 ? 1 : 0;
}

void permute(unsigned char *mem, const int *mapping, unsigned int numbits)
{
    unsigned char temp[8];
    int i;
    memset(temp, 0, 8);
    for (i = 0; i < numbits; i++) {
	bit_set(temp, i+1, bit_get(mem, mapping[i]));
    }
    i = numbits / 8;
    if (numbits % 8 != 0) {
	i++;
    }
    memcpy(mem, temp, i);
}
