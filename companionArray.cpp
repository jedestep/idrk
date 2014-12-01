#include "companionArray.h"
#include "malloc.h"

CompanionArray::CompanionArray(SuffixArray* suffArray, const OddEvenArray& oeArray, unsigned char level) {
    this->suffArray = suffArray;
    this->oeArray = oeArray;
    this->level = level;

    this->values = (int*)malloc(sizeof(int) * suffArray.size() / 2);

    int pos = 0;
    for (size_t i=0; i<suffArray.size(); i++) {
        if (!oeGet(oeArray,i)) {
            int v = suffArray[i] + 1;
            for (size_t j=0; j<suffArray.size(); j++) {
                if (v == suffArray[j]) this->values[pos++] = j;
            }
        }
    }
}

CompanionArray::~CompanionArray() {
    //Note that we do NOT delete oeArray.
    //Freeing oeArray is the responsibility of the parent class.
}

const int& CompanionArray::operator[](size_t idx) const {
    if (suffArray) {
        //if the index represents an even number, we punt
        if (oeGet(oeArray,idx)) {
            return idx;
        }
        //if not, we need to seriously search
        //count the number of zeros up to the requested index
        //this is the point at which we need to check the values array
        size_t zeroIdx = idx - rank(oeArray,idx);
        return this->values[zeroIdx];
    }
    return -1;
}
