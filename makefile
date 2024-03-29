CC=g++
CFLAGS=-c -Wall -std=c++0x

all: complete

complete: main.o IPV4Address.o ipvxstatic.o 
	$(CC) main.o IPV4Address.o ipvxstatic.o -o ipvxtest

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

IPV4Address.o: IPV4Address.cpp
	$(CC) $(CFLAGS) IPV4Address.cpp 

ipvxstatic.o: ipvxstatic.cpp
	$(CC) $(CFLAGS) ipvxstatic.cpp

clean:
	rm -rf *.o
