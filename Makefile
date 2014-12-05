CPP = g++
CPPFLAGS = -std=c++11 -lm -mpopcnt -g -O3 -I sdsl-lib/include -L sdsl-lib/lib -lsdsl -ldivsufsort -ldivsufsort64

dbmain: genomeDatabase.o suffixArray.o oeArray.o companionArray.o
	$(CPP) -o $@ $^ $(CPPFLAGS)

sizeCheck: sizeCheck.o suffixArray.o oeArray.o companionArray.o
	$(CPP) -o $@ $^ $(CPPFLAGS)

suffArrayTest: oeArray.o companionArray.o
	$(CPP) -c -o suffixArray.o suffixArray.cpp $(CPPFLAGS) -DDEBUG
	$(CPP) -o $@ suffixArray.o $^ $(CPPFLAGS) 

%.o: %.cpp %.h
	$(CPP) $(CPPFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.gch a.out
	rm -f dbmain
	rm -f sizeCheck
	rm -f suffArrayTest
