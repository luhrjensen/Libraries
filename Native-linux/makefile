CC=g++
CFLAGS=-c -Wall
SOURCES=../kclmtr/serialPort.cpp ../kclmtr/KClmtr.cpp
OBJECTS=$(SOURCES:.cpp=.o)

all:  clean $(OBJECTS)
	ar  rcs libKClmtr.a $(OBJECTS)

.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o *.a
