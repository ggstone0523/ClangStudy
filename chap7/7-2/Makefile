all: build test clean

build:
	gcc 7-2.c

test:
	@echo "----------------------------------------"
	./a.out < testfile
	@echo "----------------------------------------"
	cat testfile
	@echo "----------------------------------------"

clean:
	rm -rf ./a.out
