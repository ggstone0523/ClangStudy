all: build start error clean

build:
	gcc 4-6.c -lm

start:
	./a.out < test

error:
	./a.out < errortest

clean:
	rm -rf a.out
