CC = g++
CFlags = -g -Wall -pthread
AR = ar
ARFlags = -rcs

KClmtrDIR = ../../kclmtr
OUT = ../../bin/native\ c++/libKClmtr.a

all: KClmtr.a

KClmtr.a: KClmtr.o
	$(AR) $(ARFlags) $(OUT) KClmtr.o serialPort.o Flicker.o Measurement.o

KClmtr.o: serialPort.o Flicker.o Measurement.o
	$(CC) $(CFlags) -c  $(KClmtrDIR)/KClmtr.cpp

serialPort.o:
	$(CC) $(CFlags) -c $(KClmtrDIR)/serialPort.cpp

Flicker.o:
	$(CC) $(CFlags) -c $(KClmtrDIR)/Flicker.cpp

Measurement.o:
	$(CC) $(CFlags) -c $(KClmtrDIR)/Measurement.cpp

clean:
	rm -f *.o
	rm -f $(OUT)
