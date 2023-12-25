#include<stdio.h>
#include<limits.h>
#include<float.h>

int main() {
	printf("unsigned char min: 0, max: %d\n", UCHAR_MAX);
	printf("signed char min: %d, max: %d\n", SCHAR_MIN, SCHAR_MAX);
	printf("unsigned int min: 0, max: %u\n", UINT_MAX);
	printf("signed int min: %d, max: %d\n", INT_MIN, INT_MAX);
	printf("unsigned short min: 0, max: %d\n", USHRT_MAX);
	printf("signed short min: %d, max: %d\n", SHRT_MIN, SHRT_MAX);
	printf("unsigned long min: 0, max: %lu\n", ULONG_MAX);
	printf("signed long min: %ld, max: %ld\n", LONG_MIN, LONG_MAX);
	printf("float min: %f, max: %f\n", FLT_MIN, FLT_MAX);
	printf("double min: %lf, max: %lf\n", DBL_MIN, DBL_MAX);
	return 0;
}
