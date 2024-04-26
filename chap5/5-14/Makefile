all: build test clean

build:
	gcc 5-14.c

test:
	./a.out -n -r < testfilenum
	./a.out -nr < testfilenum
	./a.out -rn < testfilenum
	./a.out -r -n < testfilenum
	./a.out -n < testfilenum
	./a.out -r < testfilestr
	./a.out < testfilestr

clean:
	rm -rf ./a.out
