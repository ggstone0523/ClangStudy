all: build test clean

build:
	gcc 6-3.c

test:
	./a.out < testfile
	cat testfile

clean:
	rm -rf ./a.out
