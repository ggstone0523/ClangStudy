#include<stdio.h>

int setbits(int x, int p, int n, int y);

int main() {
	printf("%d\n", setbits(15, 2, 2, 1));
}

int setbits(int x, int p, int n, int y) {
	int filter = -1;
	filter = ~(filter << n);
	y = y & filter;
	filter = ~(filter << (p + 1 - n));
	y = y << (p + 1 - n);
	x = x & filter;
	x = x | y;
	return x;
}
