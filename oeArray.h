#ifndef _OEARRAY_H
#define _OEARRAY_H

// A vector representing whether a position is odd or even
// In the paper, referred to as B_k
// 0 is odd, 1 is even
typedef unsigned char * OddEvenArray;

// get the rank of 1 at a position in the OEArray
unsigned int rank(OddEvenArray, unsigned int);
// get the value of the ith bit
unsigned char oeGet(OddEvenArray, unsigned int);

#endif
