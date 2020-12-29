CXX=g++
CXXFLAGS=-Wall -ggdb
RM=rm -f

testmorse : testmorse.o morse.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o:%.cpp; $(CXX) $(CXXFLAGS) -o $@ -c $<
testmorse.o : testmorse.cpp morse.h
morse.o : morse.cpp morse.h



clean :
	$(RM) morse.o testmorse.o