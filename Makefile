CPP = g++
CPPFLAGS = -lm -mpopcnt -g -O3 -Wall

suffArrayTest: suffixArray.o oeArray.o companionArray.o
	$(CPP) $(CPPFLAGS) -o $@ $^

%.o: %.c %.h
	$(CPP) $(CPPFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.gch a.out
