#include<stdio.h>
int main() {
	int i, lim;
	char c;
	char s[100];

	i = 0;
	lim = 100;
	while(i < lim - 1) {
		c = getchar();
		if(c == '\n') {
			break;
		} else if(c == EOF) {
			break;
		}
		s[i] = c;
		++i;
	}

	return 0;
}
