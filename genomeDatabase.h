#ifndef _GENOMEDATABASE_H
#define _GENOMEDATABSE_H
#include <string>
using std::string
struct genomeEntry{
	unsigned char* genome;
	SuffixArray suffixArray;
};
class GenomeDatabase{
	protected:
		string*[] suffixArrays;
	private:
		void setUp(string*[]);
		void makeSuffixArray(string*);
		string* binarySearch(string);
    public:
		GenomeDatabase();
		GenomeDatabase(string*[]);
		string* getGenome(string);
};
