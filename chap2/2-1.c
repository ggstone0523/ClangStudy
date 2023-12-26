#include<stdio.h>
#include<limits.h>
#include<float.h>

int main() {
	int a;
	unsigned int b;

	char c;
	unsigned char d;

	short e;
	unsigned short f;

	long g;
	unsigned long h;

	unsigned long beforeNum = 0;

	printf("unsigned char min: 0, max: %d\n", UCHAR_MAX);
	printf("signed char min: %d, max: %d\n", SCHAR_MIN, SCHAR_MAX);
	printf("unsigned int min: 0, max: %u\n", UINT_MAX);
	printf("signed int min: %d, max: %d\n", INT_MIN, INT_MAX);
	printf("unsigned short min: 0, max: %d\n", USHRT_MAX);
	printf("signed short min: %d, max: %d\n", SHRT_MIN, SHRT_MAX);
	printf("unsigned long min: 0, max: %lu\n", ULONG_MAX);
	printf("signed long min: %ld, max: %ld\n", LONG_MIN, LONG_MAX);

	for(d=0; d < beforeNum; d++);
	printf("unsigned char min: 0, max: %d\n", UCHAR_MAX);
	for(c=0; c < beforeNum; c++);
	printf("signed char min: %d, max: %d\n", SCHAR_MIN, SCHAR_MAX);
	for(b=0; b < beforeNum; b++);
	printf("unsigned int min: 0, max: %u\n", UINT_MAX);
	for(a=0; a < beforeNum; a++);
	printf("signed int min: %d, max: %d\n", INT_MIN, INT_MAX);
	for(f=0; f < beforeNum; f++);
	printf("unsigned short min: 0, max: %d\n", USHRT_MAX);
	for(e=0; e < beforeNum; e++);
	printf("signed short min: %d, max: %d\n", SHRT_MIN, SHRT_MAX);
	for(h=0; h < beforeNum; h++);
	printf("unsigned long min: 0, max: %lu\n", ULONG_MAX);
	for(g=0; g < beforeNum; g++);
	printf("signed long min: %ld, max: %ld\n", LONG_MIN, LONG_MAX);


	printf("float min: %f, max: %f\n", FLT_MIN, FLT_MAX);
	printf("double min: %lf, max: %lf\n", DBL_MIN, DBL_MAX);
	return 0;
}
