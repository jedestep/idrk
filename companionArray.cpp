#include "companionArray.h"
#include "malloc.h"


CompanionArray::CompanionArray(SuffixArray* suffArray, const OddEvenArray& oeArray, unsigned char level) {
    this->oeArray = oeArray;
    this->level = level;

    int_vector<> iv(suffArray->size()/2);
    size_t pos = 0;
    for (size_t i=0; i<suffArray->size(); i++) {
        if (!oeGet(oeArray,i)) {
            int v = (*suffArray)[i] + 1;
            for (size_t j=0; j<suffArray->size(); j++) {
                if (v == (*suffArray)[j]) iv[pos++] = j;
            }
        }
    }
    util::bit_compress(iv);
    enc_vector<>* ev = new enc_vector<>(iv);
    this->values = ev;
    this->_size = suffArray->size();
    this->_realSize = size_in_bytes(*ev);
}

CompanionArray::~CompanionArray() {
    //if (suffArray) delete suffArray;
}

int CompanionArray::operator[](size_t idx) const {
    //if the index represents an even number, we punt
    if (oeGet(oeArray,idx) == 1) {
        return 1+idx;
    }
    //if not, we need to seriously search
    //count the number of zeros up to the requested index
    //this is the point at which we need to check the values array
    size_t zeroIdx = (idx) - rank(oeArray,idx);
    return 1+(*(this->values))[zeroIdx];
}

void CompanionArray::print() {
    for (size_t i=0;i<size();i++) {
        printf("%d ",this->operator[](i));
    }
    printf("\n");
}
