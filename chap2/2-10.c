#include <stdio.h>

char lower(char c);

/*
 * This function change upper to lower;
 * if c is lower or other character,
 *  this function return same value c;
 */
char lower(char c) {
	return (c >= 65 && c <= 90) ? c + 32 : c;
}

int main() {
	printf("from %c to %c\n", 'A', lower('A')); 
	printf("from %c to %c\n", 'c', lower('c')); 
	printf("from %c to %c\n", '2', lower('2')); 
	return 0;
}
