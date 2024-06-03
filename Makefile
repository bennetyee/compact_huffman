CFLAGS=-Wall -Wextra -O3 -g
TARGET=compact_hamming

$(TARGET): main.o compact_hamming.o scaffolding.o
	$(CC) -o $@ $^

main.o compact_hamming.o: scaffolding.h compact_hamming.h

scaffolding.o: scaffolding.h

clean:
	rm -f $(TARGET) *.o *~

.PHONY:	clean
