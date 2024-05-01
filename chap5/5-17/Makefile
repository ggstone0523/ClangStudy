all: build test clean

build:
	gcc 5-17.c

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
	./a.out -s0d1d2d3d < testfilefield
	./a.out -s1d < testfilefield
	./a.out -s0d1d4d3d < testfilefield
	./a.out -s0rd < testfilefield
	./a.out -s0dr1d2rd3d < testfilefield
	cat testfilefield

clean:
	rm -rf ./a.out
