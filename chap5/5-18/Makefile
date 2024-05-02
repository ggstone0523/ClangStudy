all: build test clean

build:
	gcc -o dcl dcl.c

test:
	@echo "\033[34m./dcl < testfile\033[37m"
	@./dcl < testfile
	@echo "\033[34mcat testfile\033[37m"
	@cat testfile
	@echo "\033[34m./dcl < testerrorfile\033[37m"
	@./dcl < testerrorfile
	@echo "\033[34mcat testerrorfile\033[37m"
	@cat testerrorfile

clean:
	rm -rf ./dcl
