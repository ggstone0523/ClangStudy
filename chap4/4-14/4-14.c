#include <stdio.h>

#define swap(t, x, y) {t temp; temp = x; x = y; y = temp;}

int main() {
	float x, y;
	int a, b;
	x = 1.2;
	y = 5.6;
	a = 1;
	b = 2;

	printf("x: %f, y: %f\n", x, y);
	swap(float, x, y);
	printf("x: %f, y: %f\n", x, y);

	printf("\n");
	
	printf("a: %d, b: %d\n", a, b);
	swap(int, a, b);
	printf("a: %d, b: %d\n", a, b);
	return 0;
}
