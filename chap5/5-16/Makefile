all: build test clean

build:
	gcc 5-16.c

test:
	./a.out -n -r < testfilenum
	./a.out -nr < testfilenum
	./a.out -rn < testfilenum
	./a.out -r -n < testfilenum
	./a.out -n < testfilenum
	./a.out -r < testfilestr
	./a.out < testfilestr
	./a.out -f < testfileulestr
	./a.out -rf < testfileulestr
	./a.out < testfileulestr
	./a.out -d < testfileulestr
	./a.out -df < testfileulestr
	./a.out < testfiledictstr
	./a.out -d < testfiledictstr
	./a.out -df < testfiledictstr

clean:
	rm -rf ./a.out
