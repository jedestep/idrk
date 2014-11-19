#ifndef _NTIDE_H
#define _NTIDE_H

#include <string>

using std::string;

typedef unsigned char byte;

char NtideToChar(byte b) {
    switch(b) {
        case 0: return 'A';
        case 1: return 'C';
        case 2: return 'G';
        case 3: return 'T';
    };
}

typedef struct Ntide4 {
    byte nt1 : 2;
    byte nt2 : 2;
    byte nt3 : 2;
    byte nt4 : 2;
} ntide4;
const string Ntide4ToString(const Ntide4&);

template <int N>
struct NtideGroup {
    Ntide4 group[N];
};
template <int N>
const string NtideGroupToString(const NtideGroup<N>&);
#endif
