CC=gcc
CFLAGS=-I"C:/Program Files/Npcap/Include"
LDFLAGS=-L"C:/Program Files/Npcap/Lib" -lpcap

all: sniffer

sniffer: src/sniffer.c
	$(CC) $(CFLAGS) src/sniffer.c -o sniffer.exe $(LDFLAGS)

clean:
	rm -f sniffer.exe