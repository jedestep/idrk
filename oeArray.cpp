#include "oeArray.h"

unsigned char oeGet(OddEvenArray oeArray, unsigned int idx) {
    unsigned int i = idx / 8;
    unsigned int b = idx % 8;
    return (unsigned char) ((oeArray[i] >> (7 - b)) & 1);
}

unsigned int rank(OddEvenArray arr, unsigned int numBits) {
    if (numBits <= 8*sizeof(unsigned int)) {
        unsigned int* a = (unsigned int*)arr;
        return __builtin_popcount(*a);
    }
    else if (numBits <= 8*sizeof(unsigned long long)) {
        unsigned long long* a = (unsigned long long*)arr;
        return __builtin_popcountll(*a);
    }
    else {
        int numBytes = numBits / 8;
        int sum = 0;
        for (int i=0; i<numBytes; i+=sizeof(unsigned long long)) {
            unsigned long long* a = (unsigned long long*) (arr + i);
            sum += __builtin_popcountll(*a);
        }
        return sum;
    }
}

