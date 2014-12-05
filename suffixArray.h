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

        /**
         * Comparator used for power-of-2 method
         * See http://codeforces.com/blog/entry/4025
         */
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
        /**
         * Default constructor
         */
        SuffixArray();

        /**
         * Build a suffix array of the given string
         */
        SuffixArray(const string&);

        /**
         * Unofficial copy constructor
         */
        SuffixArray(int*, size_t);
        ~SuffixArray();

        /**
         * Print out the SA
         */
        void print();

        /**
         * Construct an oeArray from this SA
         */
        OddEvenArray makeBArray() const;

        /**
         * Returns the size
         */
        size_t size() const { return _size; }

        /**
         * Return the number of bytes used
         * the 1+ is to account for storing the size
         */
        size_t realSize() const { return sizeof(int)*(1+_size); }

        /**
         * Get the value of the SA at the requested index
         */
        virtual const int& operator[](size_t idx) const {
            return values[idx];
        }

        /**
         * Synonym for operator[]
         */
        virtual const int& get(size_t idx) const {
            return this->operator[](idx);
        }
};

class CompressedSuffixArray : public SuffixArray {
    private:
        unsigned char levels;
        OddEvenArray* oddEvenArrays; //B_k
        CompanionArray* companionArrays; //Psi_k
        size_t _realSize;

        /**
         * Look up an index using the lookup algorithm in RV05 [1].
         */
        size_t _lookup(size_t, unsigned char);

    public:
        /**
         * Default constructor
         */
        CompressedSuffixArray();

        /**
         * Constructs a CSA of the given string.
         * Requires building the original SA.
         */
        CompressedSuffixArray(const string&);
        ~CompressedSuffixArray();

        /**
         * Print out the CSA.
         * Should be equivalent to SuffixArray::print.
         */
        void print();
        /**
         * The number of bytes used to store this structure.
         */
        size_t realSize() const;

        /**
         * Synonym for _lookup(index, 0)
         */
        size_t operator[](size_t index) { return this->_lookup(index, (unsigned char)0); };
        /**
         * Synonym for operator[].
         */
        size_t get(size_t idx) {
            return this->operator[](idx);
        }

};
#endif
