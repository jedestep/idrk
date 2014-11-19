#include <stdio.h>
#include "ntide.h"

const string Ntide4ToString(const Ntide4& n) {
    const string s = "";
    return s + NtideToChar(n.nt1) + NtideToChar(n.nt2) + NtideToChar(n.nt3) + NtideToChar(n.nt4);
}

template <int N>
const string NtideGroupToString(const NtideGroup<N>& ng) {
    const string s = "";
    for (int i=0; i<N; i++) {
        s += Ntide4ToString(ng.group[i]);
    }
    return s;
}

int main() {
    Ntide4 a = {0,2,1,3};
    Ntide4 b = {1,1,1,0};
    Ntide4 c = {2,3,3,1};
}
