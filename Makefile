CPP = g++
CPPFLAGS = -std=c++11 -lm -mpopcnt -g -O3 -I sdsl-lib/include -L sdsl-lib/lib -lsdsl -ldivsufsort -ldivsufsort64

dbmain: genomeDatabase.o suffixArray.o oeArray.o companionArray.o
	$(CPP) -o $@ $^ $(CPPFLAGS)

testmain: main.o suffixArray.o oeArray.o companionArray.o
	$(CPP) -o $@ $^ $(CPPFLAGS)

suffArrayTest: suffixArray.o oeArray.o companionArray.o
	$(CPP) -o $@ $^ $(CPPFLAGS) 

%.o: %.c %.h
	$(CPP) $(CPPFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.gch a.out
