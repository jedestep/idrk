#ifndef _OEARRAY_H
#define _OEARRAY_H

/**
 * A vector representing whether a position is odd or even
 * In the paper, referred to as B_k
 * 0 is odd, 1 is even
 */
typedef unsigned char * OddEvenArray;

/**
 * get the rank of 1 at a position in the oeArray
 */
unsigned int rank(OddEvenArray, unsigned int);

/**
 * get the value of the ith bit
 */
unsigned char oeGet(OddEvenArray, unsigned int);

/**
 * print the value of each bit in an oeArray
 * @param the oeArray to print
 * @param the size of the oeArray
 */
void printOeArray(OddEvenArray, unsigned int);

/**
 * print the rank at each position in an oeArray
 * @param the oeArray to print
 * @param the size of the oeArray
 */
void printRankArray(OddEvenArray, unsigned int);

#endif
