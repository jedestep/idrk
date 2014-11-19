CPP = g++
CPPFLAGS = -lm -mpopcnt -g -O3 -Wall

%.o: %.c %.h
	$(CPP) $(CPPFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.gch a.out
