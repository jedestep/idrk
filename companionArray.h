#ifndef _COMPANIONARRAY_H
#define _COMPANIONARRAY_H

#include <string>
#include "suffixArray.h"
#include "oeArray.h"
#include <sdsl/vectors.hpp>

using std::string;
using namespace sdsl;

class SuffixArray;

class CompanionArray {
    private:
        /**
         * The oeArray corresponding to the current level
         */
        OddEvenArray oeArray;
        unsigned char level;
        enc_vector<>* values;
        size_t _size;
        size_t _realSize;

    public:
        /**
         * Build this array given a suffix array, an oeArray, and the current level
         */
        CompanionArray(SuffixArray*, const OddEvenArray&, unsigned char);
        ~CompanionArray();

        int operator[](size_t idx) const;
        size_t size() {return _size;}
        size_t realSize() {return _realSize;}
        void print();
};

#endif
