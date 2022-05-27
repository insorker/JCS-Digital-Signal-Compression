include ../Makefile

all: in out

in: readerDemo.cpp
	g++ $(CPPFLAGS) $(LDFLAGS) readerDemo.cpp -o test-in $(LIBS)
                                                                
out: ouputDemo.cpp                                              
	g++ $(CPPFLAGS) $(LDFLAGS) ouputDemo.cpp -o test-out $(LIBS)

clean:
	rm -f test-*
