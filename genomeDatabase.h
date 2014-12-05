#ifndef _GENOMEDATABASE_H
#define _GENOMEDATABASE_H
#include "suffixArray.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

class GenomeEntry {
    public:
        GenomeEntry(const string&, const string&);
        string genome;
        string label;
        CompressedSuffixArray* suffixArray;
};

class GenomeDatabase{
	private:
        //use a fancy data structure? idrk
		vector<GenomeEntry> entries;

        /**
         * searches one suffixarray for the string
         * @param: SA to search through
         * @param: string to search for
         * @return: the index it was found at, or -1
         */
		int binarySearch(const GenomeEntry&, const string&, size_t, size_t);

        //label then genome
        GenomeEntry* buildEntry(const string&, const string&);

    public:
        GenomeDatabase();
        //arg0 is labels, arg1 is genomes
		GenomeDatabase(vector<string>, vector<string>);

        //arg0 is label, arg1 is genome
        void insert(string, string);

		vector<string> getGenomeLabel(const string&);
};
#endif
