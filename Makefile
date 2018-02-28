CC=cc
CFLAGS= -std=c11 -Wall


all: matrix_test.app

matrix_test.app: matrix_test.o test.o matrix.o
	$(CC) $(CFLAGS) *.o -o matrix_test.app

matrix.o: matrix.c
	$(CC) $(CFLAGS) -c matrix.c

test.o: test.c
	$(CC) $(CFLAGS) -c test.c

matrix_test.o: matrix_test.c
	$(CC) $(CFLAGS) -c matrix_test.c

clean:
	rm -rf *.o
	rm -rf *.app
