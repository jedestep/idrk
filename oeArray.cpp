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
    //up to, and including, the bit at arr[numBits]
    numBits++;
    int numBytes = (int)ceil(numBits / 8.0);
    if (numBits <= 8*sizeof(unsigned int)) {
        //printf("in the 32 case\n");
        unsigned int z = 0;
        for (int i=0; i<numBytes; i++) {
            z |= arr[i] << (8*numBytes - 8*(i+1));
        }
        if (numBits%8)
            z = z >> (8 - numBits%8);
        return __builtin_popcount(z);
    }
    else {
        int sum = 0;
        //copy of numbits
        int b = numBits;
        size_t longBitSize = 8*sizeof(unsigned int);
        while (b > longBitSize) {
            //-1 because it's there.
            sum += rank(arr, longBitSize-1);
            b -= longBitSize;
            arr += sizeof(unsigned char) * sizeof(unsigned int);
        }
        if (b) {
            sum += rank(arr, b-1);
        }
        return sum;
    }
}
