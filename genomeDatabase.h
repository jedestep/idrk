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
		vector<GenomeEntry> entries;

        /**
         * searches one suffixarray for the string
         * @param: SA to search through
         * @param: string to search for
         * @return: the index it was found at, or -1
         */
		int binarySearch(const GenomeEntry&, const string&, size_t, size_t);

    public:
        GenomeDatabase();
        /**
         * Construct a database with N entries.
         * N = length(arg0) = length(arg1)
         * @param a list of labels
         * @param a list of genome strings
         */
		GenomeDatabase(vector<string>, vector<string>);

        /**
         * Add one GenomeEntry to the database.
         * @param a label
         * @param a genome string
         */
        void insert(string, string);

        /**
         * Find the list of genomes in which the input string
         * occurs, and return their labels.
         * @param the string to search for
         * @return the vector of labels in which it was found
         */
		vector<string> getGenomeLabel(const string&);
};
#endif
