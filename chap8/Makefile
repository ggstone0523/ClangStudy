all: build test clean

build:
	gcc -o libcat libcat.c
	gcc -o nolibcat nolibcat.c

test:
	@echo "----------------------------------------------------------------------------"
	./libcat testfile1 testfile2
	@echo "----------------------------------------------------------------------------"
	./nolibcat testfile1 testfile2
	@echo "----------------------------------------------------------------------------"

clean:
	rm -rf ./libcat ./nolibcat
:q
