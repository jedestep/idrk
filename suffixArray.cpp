#include "suffixArray.h"

#include "malloc.h"
#include "stdio.h"
#include "stdlib.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <cmath>

using std::map;
using std::string;

SuffixArray::SuffixArray() {
    _size = 0;
    values = NULL;
}

//inString should be terminated with a $
SuffixArray::SuffixArray(const string& inString) {
    //make the optimizer earn its keep
    size_t len = inString.length();
    _size = len;
    /*
    string s1(inString);
    SuffixArray::SuffixComparator cmp;
    cmp.s = s1;
    cmp.len = len;
    cmp.gap = 0;
    this->_size = len;
    values = (int*)malloc(sizeof(int) * len);
    //int* positions = (int*)malloc(sizeof(int) * len);
    int* temp = (int*)calloc(len,sizeof(int));
    for (int i=0; i<len; ++i) {
        values[i] = i;
    }
    for (cmp.gap = 1;; cmp.gap *= 2) {
        printf("gap is %d\n",cmp.gap);
        std::sort(values, values + len, cmp);
        for (int i=0;i<len-1;++i) {
            temp[i+1] = temp[i] + cmp(values[i],values[i+1]);
            cmp.s[values[i]] = temp[i];
        }
        if (temp[len-1] == len-1) break;
    
    }
    */
    values = (int*)malloc(sizeof(int) * len);
    map<string,int> m;
    for (size_t i=0; i<len; i++) {
        string subs = inString.substr(i, len);
        m[subs] = i;
    }
    map<string,int>::iterator it = m.begin();
    int vali = 0;
    for (; it != m.end(); ++it) {
        values[vali++] = 1+it->second;
    }
}

SuffixArray::SuffixArray(int* values, size_t size) {
    this->values = values;
    this->_size = size;
}

SuffixArray::~SuffixArray() {
    free(values);
}

void SuffixArray::print() {
    for (size_t i=0;i<_size;i++) {
        printf("%d ",values[i]);
    }
    printf("\n");
}

OddEvenArray SuffixArray::makeBArray() const {
    size_t len = this->size();
    unsigned char _oe_bitPos = 0;
    int _oe_byte = 0;
    OddEvenArray oe = (OddEvenArray)calloc(1 + len/8,sizeof(unsigned char));
    for (size_t i=0; i<len; i++) {
        if (_oe_bitPos == 8) {
            _oe_byte++;
            _oe_bitPos = 0;
        }
        unsigned char mv = (values[i]+1) % 2;
        unsigned char b = mv << (7 - _oe_bitPos++);
        oe[_oe_byte] |= b;
    }
    return oe;
}

/* ** CompressedSuffixArray ** */
CompressedSuffixArray::CompressedSuffixArray() {
    oddEvenArrays = NULL;
    companionArrays = NULL;
    values = NULL;
    _size = 0;
    levels = 0;
}

CompressedSuffixArray::CompressedSuffixArray(const string& s) {
    size_t len = s.length();
    this->_size = len;
    levels = (unsigned int) ceil(log2(log2(len) / log2(SIGMA)));
    this->oddEvenArrays = (OddEvenArray*)malloc(levels*sizeof(OddEvenArray));
    this->companionArrays = (CompanionArray*)malloc(levels*sizeof(CompanionArray));
    SuffixArray* sa0 = new SuffixArray(s);
    SuffixArray* curr = sa0;
    SuffixArray* old;
    int* temp = NULL;
    for(int i=0;i<levels;i++) {
        this->oddEvenArrays[i] = curr->makeBArray();
        //printOeArray(oddEvenArrays[i],curr->size());
        //printRankArray(oddEvenArrays[i],curr->size());
        //make companionArray for this level
        CompanionArray* c = new CompanionArray(curr, this->oddEvenArrays[i],i);
        this->companionArrays[i] = *c;

        //gather evens and divide them by 2
        temp = (int*)malloc((curr->size()/2) * sizeof(int));
        size_t cnt = 0;
        for(size_t j=0;j<curr->size();j++) {
            if(oeGet(this->oddEvenArrays[i],j)) {
                temp[cnt++] = (*curr)[j]/2;
            }
        }
        old = curr;
        curr = new SuffixArray(temp,curr->size()/2);
        delete old;
    }
    //printf("finishing it up!\n");
    /*
    temp = (int*)malloc((curr->size()/2) * sizeof(int));
    size_t cnt = 0;
    for(int j=0;j<curr->size();j++) {
        if((*curr)[j]%2 == 0) {
            temp[cnt++] = (*curr)[j]/2;
        }
    }
    */

    this->_realSize = curr->size();
    this->values = temp;

    /*
    printf("final values:\n");
    for(int i=0;i<curr->size();i++) {
        printf("%d ",values[i]);
    }
    printf("\n");
    */
}

CompressedSuffixArray::~CompressedSuffixArray() {
    delete[] this->oddEvenArrays;
}

size_t CompressedSuffixArray::_lookup(size_t i, unsigned char k) {
    //printf("lookup is happening\n");
    //printf("level is %d\n",k);
    if (k == this->levels) {
        return this->values[i];
    }

    //printf("i is %d, size is %d\n",i,companionArrays[k].size());
    size_t comp_ki = companionArrays[k][i]-1;
    //printf("comp_ki is %d\n",comp_ki);
    size_t rnk = rank(oddEvenArrays[k], comp_ki);
    //printf("rnk is %d\n",rnk);
    size_t tmp = _lookup(rnk - 1, k + 1);
    //printf("tmp is %d\n",tmp);
    return (2 * tmp) + (oeGet(oddEvenArrays[k],i) - 1);
}

size_t CompressedSuffixArray::realSize() const {
    //size of values array
    size_t s = _realSize * sizeof(int);
    for (int i=0; i<levels; i++) {
        size_t v1 = companionArrays[i].realSize();
        s += v1;
        size_t v2 = (sizeof(unsigned char) * companionArrays[i].size()) / 8;
        s += v2;
    }
    return s;
}

void CompressedSuffixArray::print() {
    for (size_t i=0;i<this->size();i++) {
        printf("%d ", this->operator[](i));
    }
    printf("\n");
}

//#define DEBUG
#ifdef DEBUG
int main() {
    string a = "acgtatgca$";
    //string a = "aaccggttctctc$";
    /*
    string a = "";
    char cs[4] = {'a','c','g','t'};
    for(int i=0;i<4100;i++) {
        a += cs[rand()%4];
    }
    a += '$';
    */
    /*
    SuffixArray b(a);
    //printf("original realsize is %d bytes\n",b.realSize());
    b.print();

    CompressedSuffixArray c(a);
    //printf("compressed realsize is %d bytes\n",c.realSize());

    c.print();
    */
    unsigned char b[8];
    for (int i=0;i<8;i++) {
        b[i] = 0xff;
    }
    printRankArray(b, 8*8);
    /*
    printf("c[0] is %d\n",c[0]);
    printf("c[1] is %d\n",c[1]);
    printf("c[2] is %d\n",c[2]);
    */
    //printf("%d\n", c[24]);
    /*
    int* z = (int*)malloc(32);
    z[0] = 4; z[1] = 7; z[2] = 1;
    z[3] = 6; z[4] = 8; z[5] = 3;
    z[6] = 5; z[7] = 2;
    SuffixArray foo(z,8);
    OddEvenArray B = foo.makeBArray();
    printOeArray(B,8);
    */
    /*
    OddEvenArray B = b.makeBArray();
    for (size_t i=0; i<a.length(); i++) {
        printf("%d ",oeGet(B,i));
    }
    printf("\n");

    for (size_t i=0; i<a.length(); i++) {
        printf("%d ",rank(B,i));
    }
    printf("\n");
    CompanionArray psi(&b,B,0);
    for (size_t i=0; i<a.length(); i++) {
        printf("%d ",psi[i]);
    }
    printf("\n");
    */
}
#endif
