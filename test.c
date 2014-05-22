#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "des.h"
#include "util.h"
int main(int argc, char **argv) {
    unsigned char key[8] = {0x7a, 0x78, 0x4f, 0x93, 0xc5, 0x06, 0x47, 0x40};
    int x,z;
    unsigned char the_key[8];
    unsigned char pc1[7];
    unsigned char subkeys[16][7];
    unsigned char key_left[4];
    unsigned char key_right[4];
    unsigned char key_join[7];
    memset(key_left, 0, 4);
    memset(key_right, 0, 4);
    memcpy(the_key, key, 8);
    permute(the_key, permuted_choice1, 56);
    memcpy(pc1, the_key, 7);
    fprintf(stderr, "Permuted choice: %02x%02x%02x%02x%02x%02x%02x\n",
	pc1[0], pc1[1], pc1[2], pc1[3], pc1[4], pc1[5], pc1[6]);
    x = 0;
    //initialize key_left and key_right
	for (z = 0; z < 28; z++) {
		bit_set(key_left, z + 1, bit_get(pc1, z + 1));
	}
	for (z = 0; z < 28; z++) {
		bit_set(key_right, z + 1, bit_get(pc1, (z + 28) + 1));
	}
    for (x = 0; x < 16; x++) {
	    fprintf(stderr, "Key left: %02x%02x%02x%02x\n", key_left[0], key_left[1],
	    key_left[2], key_left[3]);
	    fprintf(stderr, "Key right: %02x%02x%02x%02x\n", key_right[0],
		key_right[1], key_right[2], key_right[3]);
	    bit_rot_left(key_left, 28, key_round_shifts[x]);
	    bit_rot_left(key_right, 28, key_round_shifts[x]);
	    for (z = 0; z < 28; z++) {
	    	bit_set(key_join, z + 1, bit_get(key_left, z + 1));
	    }
	    for (z = 0; z < 28; z++) {
	    	bit_set(key_join, (z + 28) + 1, bit_get(key_right, z + 1));
	    }
	    fprintf(stderr, "Rejoined after rotate for round: %u==%02x%02x%02x%02x%02x%02x\n", x + 1, key_join[0],
	    		key_join[1], key_join[2], key_join[3], key_join[4], key_join[5]);
	    memcpy(subkeys[x], key_join, 6);
	    permute(subkeys[x], permuted_choice2, 48);
	    fprintf(stderr, "Permuted choice for subkey %u: %02x%02x%02x%02x%02x%02x\n", x + 1,
		subkeys[x][0], subkeys[x][1], subkeys[x][2], subkeys[x][3], subkeys[x][4],
		subkeys[x][5]);
    }

    return 0;
}

