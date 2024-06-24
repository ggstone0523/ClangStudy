all: build test clean

build:
	gcc -o filelib filelib.c

test:
	./filelib
	cat writeseekfile

clean:
	rm -rf ./filelib
