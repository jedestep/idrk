#include "genomeDatabase.h"
#include "malloc.h"
#include "stdio.h"

GenomeEntry::GenomeEntry(const string& label, const string& genome) {
    this->label = label;
    this->genome = genome;
    this->suffixArray = new SuffixArray(genome);
}

GenomeDatabase::GenomeDatabase(vector<string> labels, vector<string> genomes) {
    for (int i = 0; i < labels.size(); i++) {
        GenomeEntry e(labels[i],genomes[i]);
        entries.push_back(e);
    }
}

void GenomeDatabase::insert(string label, string genome) {
    GenomeEntry e(label,genome);
    entries.push_back(e); 
}

int GenomeDatabase::binarySearch(const GenomeEntry& ge, const string& search, size_t min, size_t max) {

    if (max < min) {
        return -1;
    }
    int mid = (min + (max - min)/2);
    string str = ge.genome.substr(ge.suffixArray->get(mid)-1);
    if (str.compare(search) < 0) {
        return binarySearch(ge, search, mid+1, max);
    } else if (str.compare(search) > 0) {
        auto res = std::mismatch(search.begin(), search.end(), str.begin());
        if (res.first == search.end()) {
            return mid;
        }
        return binarySearch(ge, search, min, mid-1);
    } else {
        return mid;
    }
}

vector<string> GenomeDatabase::getGenomeLabel(const string& read) {
    vector<string> result;
    for (int i = 0; i < entries.size(); i++) {
        int r = binarySearch(entries[i], read, 0, entries[i].suffixArray->size()-1);
        if ( r >= 0) {
            result.push_back(entries[i].label);
        }
    }
    return result;
}
int main() {
    string a = "acgtattgca$";
    string b = "aacgtatcga$";
    vector<string> genomes;
    genomes.push_back(a);
    genomes.push_back(b);
    string la = "one";
    string lb = "two";
    vector<string> labels;
    labels.push_back(la);
    labels.push_back(lb);
    GenomeDatabase db(labels, genomes);
    string one = "acgt";
    string two = "attg";
    string three = "gac";
    vector<string> resOne = db.getGenomeLabel(one);
    vector<string> resTwo = db.getGenomeLabel(two);
    vector<string> resThree = db.getGenomeLabel(three);
    std::copy(resOne.begin(), resOne.end(), std::ostream_iterator<string>(std::cout, " "));
    std::cout << "\n";
    std::copy(resTwo.begin(), resTwo.end(), std::ostream_iterator<string>(std::cout, " "));
    std::cout << "\n";
    std::copy(resThree.begin(), resThree.end(), std::ostream_iterator<string>(std::cout, " "));
    std::cout << "\n";
}
