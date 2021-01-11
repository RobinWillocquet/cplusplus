CXX=g++
CXXFLAGS=-Wall -ggdb
RM=rm -f

testmorse : testmorse.o morse.o
	$(CXX) $(CXXFLAGS) $^ -o $@

testaudio : testaudio.o audiolib.o
	$(CXX) $(CXXFLAGS) $^ -o $@

progmorse : progmorse.o morse.o audiolib.o
	$(CXX) $(CXXFLAGS) $^ -o $@


%.o:%.cpp; $(CXX) $(CXXFLAGS) -o $@ -c $<
testmorse.o : testmorse.cpp morse.h
testaudio.o : testaudio.cpp audiolib.h AudioFile.h
progmorse.o : progmorse.cpp morse.h
morse.o : morse.cpp morse.h
audiolib.o : audiolib.cpp audiolib.h AudioFile.h



clean :
	$(RM) morse.o testmorse.o progmorse.o morse.h.gch morsetot.o audiolib.o testaudio.o morsetot testmorse progmorse testaudio morse