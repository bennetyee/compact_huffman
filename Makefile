CFLAGS=-Wall -Wextra -O3 -g

osu_hamming: main.o osu_hamming.o scaffolding.o
	$(CC) -o $@ $^

main.o osu_hamming.o: scaffolding.h osu_hamming.h

scaffolding.o: scaffolding.h

clean:
	rm -f osu_hamming *.o *~

.PHONY:	clean
