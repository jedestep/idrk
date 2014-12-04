#include "oeArray.h"
#include "stdio.h"
#include "math.h"

unsigned char oeGet(OddEvenArray oeArray, unsigned int idx) {
    unsigned int i = idx / 8;
    unsigned int b = idx % 8;
    return (unsigned char) ((oeArray[i] >> (7 - b)) & 1);
}

void printOeArray(OddEvenArray oeArray, unsigned int size) {
    for(unsigned int i=0;i<size;i++) {
        printf("%d ",oeGet(oeArray,i));
    }
    printf("\n");
}

void printRankArray(OddEvenArray oeArray, unsigned int size) {
    for(unsigned int i=0;i<size;i++) {
        printf("%d ",rank(oeArray,i));
    }
    printf("\n");
}

unsigned int rank(OddEvenArray arr, unsigned int numBits) {
    //if (numBits == 0) return 0;
    //up to, and including, the bit at arr[numBits]
    numBits++;
    int numBytes = (int)ceil(numBits / 8.0);
    if (numBits <= 8*sizeof(unsigned int)) {
        unsigned int z = 0;
        for (int i=0; i<numBytes; i++) {
            z |= arr[i] << (8*numBytes - 8*(i+1));
        }
        if (numBits%8)
            z = z >> (8 - numBits%8);
        return __builtin_popcount(z);
    }
    else if (numBits <= 8*sizeof(unsigned long long)) {
        unsigned long long z = 0;
        for (int i=0; i<numBytes; i++) {
            z |= arr[i] << (8*numBytes - 8*(i+1));
        }
        if (numBits%8)
            z = z >> (8 - numBits%8);
        return __builtin_popcountll(z);
    }
    else {
        int sum = 0;
        int longBitSize = 8*sizeof(unsigned long long);
        for (int i=0; i<numBytes; i+=sizeof(unsigned long long)) {
            if ((numBits - (i*longBitSize/8)) > longBitSize) {
                unsigned long long* a = (unsigned long long*) (arr + i);
                sum += __builtin_popcountll(*a);
            }
            else {
                sum += rank(arr + i, numBits - (i*longBitSize/8));
                break;
            }
        }
        return sum;
    }
}
