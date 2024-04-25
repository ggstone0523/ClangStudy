all: build test clean

build:
	gcc -o tail ./tail.c

test:
	./tail -3 < testfile

clean:
	rm -rf ./tail
