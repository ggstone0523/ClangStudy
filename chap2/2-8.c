#include <stdio.h>

int rightrot(int x, int n);

int rightrot(int x, int n) {
	return ((x >> n) | ((x & ((1 << n) - 1)) << ((sizeof(int) * 8) - n)));
}

int main() {
	printf("10 >> 3 = %d\n", rightrot(10, 3));
	return 0;
}
