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

        struct SuffixComparator {
            int gap;
            int len;
            string s;
            bool operator()(int i, int j) {
                if (s[i] != s[j]) {
                    return s[i] < s[j];
                }
                i += gap;
                j += gap;
                return (i < len && j < len) ? s[i] < s[j] : i > j;
            }
        };

    public:
        SuffixArray();
        SuffixArray(const string&);
        SuffixArray(int*, size_t);
        ~SuffixArray();

        void print();

        // Labels positions as odd or even
        OddEvenArray makeBArray() const;

        size_t size() const { return _size; }
        //the 1+ is to account for storing the size
        size_t realSize() const { return sizeof(int)*(1+_size); }
        const int& operator[](size_t idx) const {
            return values[idx];
        }
};

class CompressedSuffixArray : SuffixArray {
    private:
        unsigned char levels;
        OddEvenArray* oddEvenArrays; //B_k
        CompanionArray* companionArrays; //Psi_k
        size_t _realSize;

        size_t _lookup(size_t, unsigned char);

    public:
        CompressedSuffixArray();
        CompressedSuffixArray(const string&);
        ~CompressedSuffixArray();

        void print();
        size_t realSize() const;

        size_t operator[](size_t index) { return this->_lookup(index, (unsigned char)0); };

};
#endif
