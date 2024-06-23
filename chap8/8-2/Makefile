all: build test clean

build:
	gcc -o bitsfp bitsfp.c
	gcc -o fieldsfp fieldsfp.c

test:
	./bitsfp
	./fieldsfp

clean:
	rm -rf ./bitsfp ./fieldsfp
