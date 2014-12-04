#include "suffixArray.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <ctime>

int main() {
    std::ifstream listing("data/index.txt");
    /*
    std::string buf;
    std::string s = "";
    std::getline(infile,buf); //skip over the sequence designator
    while (std::getline(infile,buf)) {
        s += buf;
    }
    //s = "accaccaccaccacaaacacaccacccaccab";
    //s += '$';
    for (int i=0; i<s.length() / 100000; i++) {
        printf("building SA %d\n",i);
        string z = s.substr(i*100000,(i+1)*100000);
        std::clock_t start;
        start = std::clock();
        SuffixArray b(z);
        std::cout << "Time to build standard SA: " << (std::clock() - start)/(double)(CLOCKS_PER_SEC/1000) << " ms\n";
        std::cout << "Total size (bytes) of standard SA: " << b.realSize() << "\n";
    }
    //b.print();
    */
    std::string buf;
    long standardTotal = 0;
    long compTotal = 0;
    while (std::getline(listing,buf)) {
        std::ifstream genomeFile(buf);
        string genome;
        string buf2;
        while(getline(genomeFile,buf2)) {
            genome += buf2;
        }
        genome += '$';
        std::clock_t start;
        start = std::clock();
        SuffixArray b(genome);
        std::cout << "Time to build standard SA: " << (std::clock() - start)/(double)(CLOCKS_PER_SEC/1000) << " ms\n";
        std::cout << "Total size (bytes) of standard SA: " << b.realSize() << "\n";
        standardTotal += b.realSize();

        start = std::clock();
        CompressedSuffixArray c(genome);
        std::cout << "Time to build compressed SA: " << (std::clock() - start)/(double)(CLOCKS_PER_SEC/1000) << " ms\n";
        std::cout << "Total size (bytes) of compressed SA: " << c.realSize() << "\n\n";
        compTotal += c.realSize();
    }

    std::cout << "Overall size of standard suffix arrays: " << standardTotal << "\n";
    std::cout << "Overall size of compressed suffix arrays: " << compTotal << "\n";
}
