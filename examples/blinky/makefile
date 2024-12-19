CXXFLAGS=`pkg-config etherbone saftlib --cflags` 
LDFLAGS=`pkg-config etherbone saftlib --libs`

blinky: sdb_blinky_standalone.cpp
	g++ -o $@ $< $(CXXFLAGS) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f sdb_blinky_standalone