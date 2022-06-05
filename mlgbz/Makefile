include ../Makefile

all: reader writer

reader: mlgbzreader.cpp                                              
	g++ $(CPPFLAGS) $(LDFLAGS) reader.cpp mlgbzreader.cpp vcdata.cpp -o test-reader $(LIBS)

writer: mlgbzwriter.cpp                                              
	g++ $(CPPFLAGS) $(LDFLAGS) writer.cpp mlgbzwriter.cpp vcdata.cpp -o test-writer $(LIBS)

clean:
	rm -f test-* *.out
