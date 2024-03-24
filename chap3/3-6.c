#include <stdio.h>

void itoa(int n, char s[], int minimumWidth);
void reverse(char s[]);
int abs(int n);

void itoa(int n, char s[], int minimumWidth) {
	int i, sign;

	sign = n;
	i = 0;
	do {
		s[i++] = abs(n % 10) + '0';
	} while ((n = abs(n / 10)) > 0);
	if(sign < 0)
		s[i++] = '-';
	while(i < minimumWidth)
		s[i++] = ' ';
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
	int n1 = 1;
	int n2 = 12;
	int n3 = 123;
	int n4 = 1234;
	int n5 = 12345;
	char s[1024];

	itoa(n1, s, 5);
	printf("%s\n", s);
	itoa(n2, s, 5);
	printf("%s\n", s);
	itoa(n3, s, 5);
	printf("%s\n", s);
	itoa(n4, s, 5);
	printf("%s\n", s);
	itoa(n5, s, 5);
	printf("%s\n", s);
	return 0;
}
