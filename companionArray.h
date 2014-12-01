#ifndef _COMPANIONARRAY_H
#define _COMPANIONARRAY_H

#include <string>
#include "suffixArray.h"
#include "oeArray.h"

using std::string;

class SuffixArray;

class CompanionArray {
    private:
        //The SuffixArray corresponding to the CURRENT level
        SuffixArray* suffArray;
        //The OddEvenArray corresponding to the CURRENT level
        OddEvenArray oeArray;
        unsigned char level;
        int* values;

    public:
        CompanionArray(SuffixArray*, const OddEvenArray&, unsigned char);
        ~CompanionArray();

        const int& operator[](size_t idx) const;
};

#endif
