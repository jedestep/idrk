# Identification Database for Random k-mers
Authored by Jed Estep and Ashleigh Thomas

A DNA read identification database, based on a data structure [outlined](http://dl.acm.org/citation.cfm?id=335351) by R. Grossi and J. Vitter.

## Dependencies and Acknowledgements
This library depends on [sdsl-lite](https://github.com/simongog/sdsl-lite). A binary distribution for linux-x86\_64 is included in the ```sdsl-lib``` directory.
_(note to instructors; this should be usable on the ugrad cluster, as this is where it was compiled.)_

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
