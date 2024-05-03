all: build test clean

build:
	gcc -o undcl undcl.c

test:
	./undcl < testfile

clean:
	rm -rf ./undcl
