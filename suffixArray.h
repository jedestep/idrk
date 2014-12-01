#ifndef _SUFFIXARRAY_H
#define _SUFFIXARRAY_H

#define SIGMA 4

#include "companionArray.h"
#include "oeArray.h"
#include <string>

using std::string;

class CompanionArray;

/**
 * An uncompressed suffix array.
 * Consists of a list of ints representing
 * the offsets of the suffixes of a string.
 * The string is not retained by this class.
 */
class SuffixArray {
    protected:
        int* values;
        size_t _size;

    public:
        SuffixArray();
        SuffixArray(const string&);
        ~SuffixArray();

        void print();

        // Labels positions as odd or even
        OddEvenArray makeBArray() const;

        size_t size() const { return _size; }
        const int& operator[](size_t idx) const {
            return values[idx];
        }
};

class CompressedSuffixArray : SuffixArray {
    private:
        //smallestSuffixArray int*; //in the text, this is SA_l
        unsigned char levels;
        OddEvenArray* oddEvenArrays; //B_k
        CompanionArray* companionArrays; //Psi_k

        const int& _lookup(size_t, unsigned char);

    public:
        CompressedSuffixArray();
        CompressedSuffixArray(const string&);

        const int& operator[](size_t index) { return this->_lookup(index, (unsigned char)0); };

};
#endif
