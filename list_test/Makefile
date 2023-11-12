

CC=gcc
CFLAGS=-Wall -g -I/usr/src/linux-headers-5.4.0-165/include  -I/usr/src/linux-headers-5.4.0-165/arch/arm/include
LDFLAGS=
LIBS=
TARGET=main

all: $(TARGET)

$(TARGET): main_01.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) main_01.o $(LIBS)

main_01.o: main_01.c list.h 
	$(CC) $(CFLAGS) -c main_01.c 

