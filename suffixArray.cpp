
#include "suffixArray.h"

#include "malloc.h"
#include "stdio.h"
#include <map>

using std::map;

SuffixArray::SuffixArray() {
    _size = 0;
    values = NULL;
}

SuffixArray::SuffixArray(const string& inString) {
    size_t len = inString.length();
    _size = len;
    values = (int*)malloc(sizeof(int) * len);
    map<string,int> m;
    for (size_t i=0; i<len; i++) {
        string subs = inString.substr(i, len);
        m[subs] = i;
    }
    map<string,int>::iterator it = m.begin();
    int vali = 0;
    for (; it != m.end(); ++it) {
        values[vali++] = it->second;
    }
}

SuffixArray::~SuffixArray() {
    free(values);
}

void SuffixArray::print() {
    for (int i=0;i<_size;i++) {
        printf("%d ",values[i]);
    }
    printf("\n");
}

OddEvenArray SuffixArray::makeBArray() const {
    size_t len = this->size();
    unsigned char _oe_bitPos = 0;
    int _oe_byte = 0;
    OddEvenArray oe = (OddEvenArray)malloc(sizeof(unsigned char) * (1 + len/8));
    //printf("allocated OEArray of size %d byte(s)\n",1 + len/8);
    for (size_t i=0; i<len; i++) {
        if (_oe_bitPos == 8) {
            _oe_byte++;
            _oe_bitPos = 0;
        }
        oe[_oe_byte] |= ((values[i]+1) % 2) << (7 - _oe_bitPos++);
    }
    return oe;
}

int SuffixArray::rank(OddEvenArray arr, size_t numBits) {
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
            sum += __builtin_popcount(*a);
        }
        return sum;
    }
}

/* ** CompressedSuffixArray ** */
CompressedSuffixArray::CompressedSuffixArray() {
    oddEvenArrays = NULL;
    companionArrays = NULL;
    values = NULL;
    size = 0;
    levels = 0;
}

CompressedSuffixArray::CompressedSuffixArray(const string& s) {
    size_t len = s.length();
    levels = (unsigned int) ceil(log2(log2(len) / log2(SIGMA)));
    // TODO
}

const int& CompressedSuffixArray::_lookup(size_t i, unsigned char k) {
    if (k == this->levels) {
        return this->values[i];
    }

    return 2 * _lookup(SuffixArray::rank(oddEvenArrays[k], companionArrays[k][i]), k + 1) + (oddEvenArrays[k][i] - 1);
}

int main() {
    string a = "acagtt$";
    SuffixArray b(a);
    b.print();

    //CompressedSuffixArray c;
    OddEvenArray B = b.makeBArray();
    for (size_t i=0; i<1 + b.size()/8; i++) {
        printf("%x ", B[i]);
    }
    printf("\n");
    delete B;
}
