#ifndef _COMPANIONARRAY_H
#define _COMPANIONARRAY_H

#include <string>

using std::string;

class CompanionArray {

    private:
        int foo;
    
    public:
        const int& operator[](size_t idx) const {
            return 0;
        } //TODO
};

#endif
