all: build start clean

build:
	gcc 4-10.c -lm

start:
	./a.out < test
	./a.out < errortest

clean:
	rm -rf a.out
