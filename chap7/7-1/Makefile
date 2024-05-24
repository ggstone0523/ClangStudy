all: build test clean

build:
	gcc 7-1.c
	cp ./a.out ./lower/
	cp ./a.out ./upper/

test:
	@echo "--------------------------------------"
	cat testfile
	@echo "--------------------------------------"
	./lower/a.out < testfile
	@echo "--------------------------------------"
	./upper/a.out < testfile
	@echo "--------------------------------------"
	./a.out < testfile
	@echo "--------------------------------------"

clean:
	rm -rf ./lower/a.out ./upper/a.out ./a.out
