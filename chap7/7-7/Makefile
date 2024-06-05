all: build test1 test2 clean

build:
	gcc 7-7.c

test1:
	@echo "-------------------------------------------------"
	./a.out -nf3 car testfile1 testfile2 testfile3

test2:
	@echo "-------------------------------------------------"
	./a.out -n car < testfile1

clean:
	@echo "-------------------------------------------------"
	rm -rf ./a.out
