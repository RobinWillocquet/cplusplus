CXX=g++
CXXFLAGS=-Wall -ggdb
RM=rm -f

intstacktest : intstacktest.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o:%.cpp; $(CXX) $(CXXFLAGS) -o $@ -c $<
intstacktest.o : intstacktest.cpp intstack.h
Integer.o = Integer.cpp Integer.h



clean :
	$(RM) intstacktest.o Integer.o intstacktest Integer.h.gch intstack.h.gch foo integer