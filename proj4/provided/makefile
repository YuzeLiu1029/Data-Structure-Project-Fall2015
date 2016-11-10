CCC = g++
CCFlags = -std=c++0x -Wall -g -pedantic
INCLUDES = -I.

all: clean test

clean:
	rm -f *.o *~
test:
	$(CCC) $(CCFlags) -o proj4.x proj4_driver.cpp


