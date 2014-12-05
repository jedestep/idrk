# Identification Database for Random k-mers
Authored by Jed Estep and Ashleigh Thomas

A DNA read identification database, based on a compressed suffix array data structure [outlined](http://dl.acm.org/citation.cfm?id=335351) by R. Grossi and J. Vitter.

## Dependencies and Acknowledgements
This library depends on [sdsl-lite](https://github.com/simongog/sdsl-lite). A binary distribution for linux-x86\_64 is included in the ```sdsl-lib``` directory.
_(note to instructors; this should be usable on the ugrad cluster, as this is where it was compiled.)_

Since sdsl-lite is only available on 64 bit architectures, this cannot be built on a 32 bit machine. Additionally, the SSE4.2 extension to x86 is required (via the ```g++``` flag ```-mpopcnt```).

Special thanks to [this](http://codeforces.com/blog/entry/4025) suffix array implementation for purposes of experimentation and inspiration.

## Make Targets
- ```dbmain```: run a test of the database. It loads the FASTA files listed in ```data/index.txt```, then queries for every line of ```data/queries.txt```. The expected results are
    ```
    ex_read_a
    ex_read_b
    ex_read_c
    ex_read_d
    ex_read_e
    ex_read_f
    ex_read_f

    ex_read_a
    ```
- ```sizeCheck```: builds a compressed and uncompressed SA of all the fasta files in ```data/index.txt``` and reports the time and space used by each.
- ```suffArrayTest```: displays a regular and compressed SA for a random string, as well as the regular and compressed sizes.

## Code Organization
- ```suffixArray.h``` contains the API for both standard and compressed suffix arrays. The interesting functions are the non-default constructors and the function ```CompressedSuffixArray::_lookup```. The implementation of ```CompressedSuffixArray``` is based off the paper cited above.
- ```oeArray.h``` contains the API for the arrays _B_ and _rank_ outlined in the paper. Note that _rank_ is never represented explicitly.
- ```companionArray.h``` contains the API for the array _Psi_ outlined in the paper. Here we use a different implementation which relies on sdsl-lite.
- ```genomeDatabase.h``` contains a basic storage and search API for determining the source of a read (or more generally, any input string). The primary public operation it supports is ```getGenomeLabel```, which returns a list of stored strings in which the input string is contained.
