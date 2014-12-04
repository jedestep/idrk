#include "companionArray.h"
#include "malloc.h"

CompanionArray::CompanionArray(SuffixArray* suffArray, const OddEvenArray& oeArray, unsigned char level) {
    this->suffArray = suffArray;
    this->oeArray = oeArray;
    this->level = level;

    this->values = (int*)malloc(sizeof(int) * suffArray->size()/2);

    size_t pos = 0;
    for (size_t i=0; i<suffArray->size(); i++) {
        if (!oeGet(oeArray,i)) {
            int v = (*suffArray)[i] + 1;
            for (size_t j=0; j<suffArray->size(); j++) {
                if (v == (*suffArray)[j]) this->values[pos++] = j;
            }
        }
    }
    this->_size = suffArray->size();
    this->_realSize = pos;
}

CompanionArray::~CompanionArray() {
    //if (suffArray) delete suffArray;
}

int CompanionArray::operator[](size_t idx) const {
    //if the index represents an even number, we punt
    //printf("idx is %d\n",idx);
    //printf("oeGet is %d\n",oeGet(oeArray,idx));
    if (oeGet(oeArray,idx) == 1) {
        return 1+idx;
    }
    //if not, we need to seriously search
    //count the number of zeros up to the requested index
    //this is the point at which we need to check the values array
    //printf("rank of %d is %d\n",idx+1,rank(oeArray,idx+1));
    size_t zeroIdx = (idx) - rank(oeArray,idx);
    //printf("zeroIdx is %d\n",zeroIdx);
    //printf("size of values is %d\n",
    return 1+this->values[zeroIdx];
}

void CompanionArray::print() {
    for (int i=0;i<size();i++) {
        printf("%d ",this->operator[](i));
    }
    printf("\n");
}
