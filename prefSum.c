#ifndef _PREFSUM_H
#define _PREFSUM_H

#include "malloc.h"
#include "stdio.h"
#include "time.h"

/** Sum the entire array. */
int binaryArraySum1(unsigned char* arr, int numBits) {
    if (numBits <= 8*sizeof(unsigned int)) {
        unsigned int* a = (unsigned int*) arr;
        return __builtin_popcount(*a);
    }
    else if (numBits <= 8*sizeof(unsigned long long)) {
        unsigned long long* a = (unsigned long long*) arr;
        return __builtin_popcountll(*a);
    }
    else {
        int numBytes = numBits / 8;
        int sum = 0;
        int i=0;
        for (i=0; i<numBytes; i+= sizeof(unsigned long long)) {
            unsigned long long* a = (unsigned long long*) (arr + i);
            sum += __builtin_popcountll(*a);
        }
        return sum;
    }
}

/*
int main() {
    //unsigned char foo[1001000];
    unsigned char* foo = (unsigned char*)malloc(sizeof(unsigned char)*100000000);
    for (int i=0; i<100000000; i++) {
        foo[i] = 3;
    }
    clock_t start = clock();
    printf("%d\n", binaryArraySum1(foo,800000000));
    start = clock() - start;
    printf("Method 1 took %f seconds\n", ((float)start)/CLOCKS_PER_SEC);
    start = clock();
    printf("%d\n", binaryArraySum2(foo,800000000));
    start = clock() - start;
    printf("Method 2 took %f seconds\n", ((float)start)/CLOCKS_PER_SEC);
 }
#endif
*/
