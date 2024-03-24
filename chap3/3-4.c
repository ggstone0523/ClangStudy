#include <stdio.h>

void itoa(int n, char s[]);
void reverse(char s[]);
int abs(int n);

/* reason of problem;
 * in previous code, -1 * n is no effect when n is largest negative number;
 * this is beacuse when doing -1 * largest negative number, 
 * an overflow occurs and becomes the same as largets negative number.
 * Therefore, since the logic proceeds when n is a negative number,
 * an error occurred in the logic that assumed that n was converted to a positive number.
 * */
void itoa(int n, char s[]) {
	int i, sign;

	sign = n;
	i = 0;
	do {
		s[i++] = abs(n % 10) + '0';
	} while ((n = abs(n / 10)) > 0);
	if(sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

void reverse(char s[]) {
	int frontP = 0;
	int backP = 0;
	char temp;

	while(s[backP] != '\0')
		backP++;
	backP--;
	
	while(frontP < backP) {
		temp = s[frontP];
		s[frontP] = s[backP];
		s[backP] = temp;
		frontP++;
		backP--;
	}
}

int abs(int n) {
	if(n < 0)
		return -n;
	else
		return n;
}

int main() {
	int n = -2147483648;
	char s[1024];

	itoa(n, s);

	printf("%s\n", s);
	return 0;
}
