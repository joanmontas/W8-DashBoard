output: main.o linklist.o widget.o
	gcc main.o linklist.o widget.o -o w8TermExec -lm -lpthread

main.o: main.c
	gcc -c main.c

widget.o: widget.c widget.h
	gcc -c linklist.o widget.c

linklist.o: linklist.c linklist.h
	gcc -c linklist.c
clean:
	rm linklist.o
	rm widget.o
	rm main.o

