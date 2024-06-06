all: build test1 test2 clean

build:
	gcc -o find 7-7.c

test1:
	@echo "-------------------------------------------------"
	./find -nf3 car testfile1 testfile2 testfile3

test2:
	@echo "-------------------------------------------------"
	./find -n car < testfile1

clean:
	@echo "-------------------------------------------------"
	rm -rf ./find
