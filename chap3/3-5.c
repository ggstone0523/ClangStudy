#include <stdio.h>
#include <limits.h>

void itoa(unsigned int n, char s[], unsigned int b);
void reverse(char s[]);
int abs(int n);

void itoa(unsigned int n, char s[], unsigned int b) {
	unsigned int i, orginN;
	int sign;

	sign = (INT_MAX < n ? -1 : 1);
	i = 0;
	n = (b == 10 ? abs((int)n) : n);
	do {
		if((orginN = abs(n % b)) > 9)
			s[i++] = abs(n % b) + 7 + '0';
		else
			s[i++] = abs(n % b) + '0';
	} while ((n = abs(n / b)) > 0);
	if(sign < 0 && b == 10)
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
	int n1 = -5;
	int n2 = 12345;
	int b1 = 2;
	int b2 = 8;
	int b3 = 10;
	int b4 = 16;
	char s[1024];

	itoa(n1, s, b1);
	printf("%d, %d: %s\n", n1, b1, s);
	itoa(n1, s, b2);
	printf("%d, %d: %s\n", n1, b2, s);
	itoa(n1, s, b3);
	printf("%d, %d: %s\n", n1, b3, s);
	itoa(n1, s, b4);
	printf("%d, %d: %s\n", n1, b4, s);
	
	itoa(n2, s, b1);
	printf("%d, %d: %s\n", n2, b1, s);
	itoa(n2, s, b2);
	printf("%d, %d: %s\n", n2, b2, s);
	itoa(n2, s, b3);
	printf("%d, %d: %s\n", n2, b3, s);
	itoa(n2, s, b4);
	printf("%d, %d: %s\n", n2, b4, s);
	return 0;
}
