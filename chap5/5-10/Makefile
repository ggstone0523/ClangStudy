all: build start clean

build:
	gcc -o expr 5-10.c

start:
	./expr 2 3 4 + '*'
	./expr 10 5 3 - '/'
	./expr 10.5 -3.4 72 + +
	./expr .34 10. +
	./expr 0.20 10.0 +
	./expr -3 -4 -
	./expr

clean:
	rm -rf ./expr
