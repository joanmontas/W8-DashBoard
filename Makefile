output: main.o linklist.o widget.o
	gcc main.o linklist.o widget.o -o w8TermExec -lm -lpthread

main.o: main.c
	gcc -c main.c

widget.o: dependencies/widget.c dependencies/widget.h
	gcc -c linklist.o dependencies/widget.c

linklist.o: dependencies/linklist.c dependencies/linklist.h
	gcc -c dependencies/linklist.c
clean:
	rm linklist.o
	rm widget.o
	rm main.o

