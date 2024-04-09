#include <stdio.h>

void itoa(int n, char s[], int check);

void itoa(int n, char s[], int check) {
	static int idx = 0;
	
	if(n < 0) {
		s[idx++] = '-';
		n = -n;
	}
	if(n / 10)
		itoa(n / 10, s, check+1);
	s[idx++] = n % 10 + '0';
	if(check == 0) {
		s[idx] = '\0';
		idx = 0;
	}
}

int main() {
	int n = 12345;
	int minusn = -12345;
	char s[1024];

	itoa(n, s, 0);
	printf("%d to string: %s\n", n, s);

	itoa(minusn, s, 0);
	printf("%d to string: %s\n", minusn, s);

	return 0;
}
