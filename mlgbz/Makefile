include ../Makefile

all: in out bz

in: readerDemo.cpp
	g++ $(CPPFLAGS) $(LDFLAGS) readerDemo.cpp -o test-in $(LIBS)
                                                                
out: ouputDemo.cpp                                              
	g++ $(CPPFLAGS) $(LDFLAGS) ouputDemo.cpp -o test-out $(LIBS)

reader: mlgbzreader.cpp                                              
	g++ $(CPPFLAGS) $(LDFLAGS) reader.cpp mlgbzreader.cpp vcdata.cpp -o test-reader $(LIBS)

writer: mlgbzwriter.cpp                                              
	g++ $(CPPFLAGS) $(LDFLAGS) writer.cpp mlgbzwriter.cpp vcdata.cpp -o test-writer $(LIBS)

clean:
	rm -f test-* *.out
