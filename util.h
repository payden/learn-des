/*
 * util.h
 *
 *  Created on: May 22, 2014
 *      Author: payden
 */

#ifndef UTIL_H_
#define UTIL_H_

void bit_rot_left(unsigned char *bits, int size, int count);
void bit_set(unsigned char *mem, unsigned int bitnum, unsigned int on);
unsigned int bit_get(unsigned char *mem, unsigned int bitnum);
void permute(unsigned char *mem, const int *mapping, unsigned int numbits);

#endif /* UTIL_H_ */
