CC = g++
CFlags = -g -Wall -pthread
AR = ar
ARFlags = rvs

KClmtrDIR = ../../kclmtr
OUT = ../../bin/native\ c++/g++/libKClmtr.a

all: KClmtr.a

KClmtr.a: KClmtr.o
	$(AR) $(ARFlags) $(OUT) KClmtr.o SerialPort.o Flicker.o Measurement.o Counts.o

KClmtr.o: SerialPort.o Flicker.o Measurement.o Counts.o
	$(CC) $(CFlags) -c $(KClmtrDIR)/KClmtr.cpp

SerialPort.o:
	$(CC) $(CFlags) -c $(KClmtrDIR)/SerialPort.cpp

Flicker.o:
	$(CC) $(CFlags) -c $(KClmtrDIR)/Flicker.cpp

Measurement.o:
	$(CC) $(CFlags) -c $(KClmtrDIR)/Measurement.cpp

Counts.o:
	$(CC) $(CFlags) -c $(KClmtrDIR)/Counts.cpp

clean:
	rm -f *.o
	rm -f $(OUT)
