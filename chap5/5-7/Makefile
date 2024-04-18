all: build start clean

build:
	gcc -o homework homework.c
	gcc -o original original.c

start:
	cat test
	./homework < test
	./original < test

clean:
	rm -rf ./homework ./original
