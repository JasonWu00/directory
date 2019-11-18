all: main.o
	gcc -o testfile main.o

main.o: main.c
	gcc -c main.c

run:
	./testfile

clean:
	rm -rf *.o
	rm -rf testfile
