#include<stdio.h>

int invert(int x, int p, int n);

int main() {
	printf("%d\n", invert(23, 3, 2));
	return 0;
}

int invert(int x, int p, int n) {
	int filter;
	filter = (~(-1 << n)) << (p + 1 - n);
	x = x ^ filter;
	return x;
}
