#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

unsigned long htoi(char str[]);
unsigned long nSquare(unsigned long a, int x);

int main() {
	char *str = "0x1234abCD";
	printf("%s: %lu\n", str, htoi(str));
	return 0;
}

unsigned long htoi(char str[]) {
	unsigned long n, i, len, cnum;

	n = 0;
	len = strlen(str);
	for(i=0; i < len; i++) {
		if(str[i] >= '0' && str[i] <= '9') {
			cnum = str[i] - '0';
		} else if(str[i] >= 'a' && str[i] <= 'f') {
			cnum = str[i] - 'a' + 10;
		} else if(str[i] >= 'A' && str[i] <= 'F') {
			cnum = str[i] - 'A' + 10;
		} else if(i == 1 && (str[i] == 'x' || str[i] == 'X') && str[0] == '0') {
			cnum = 0;
		} else {
			printf("Wrong Input!!\n");
			return 0;
		}
		n = n + nSquare(16, len - i) * cnum;
	}
	return n;
}

unsigned long nSquare(unsigned long a, int x) {
	int i = 0;
	unsigned long n = 1;
	if(x == 0) {
		return 1;
	}
	for(i=1; i < x; i++) {
		n = n * a;
	}
	return n;
}
