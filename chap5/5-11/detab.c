#include <stdio.h>
#include <ctype.h>

int N;

char __detab(void);
int atoi(char* i);

char __detab(void) {
	char c;
	int count, i, k, idx;

	count = 0;
	while((c = getchar()) != '\n' && c != EOF){
		if(c == '\t'){
			k = count % N;
			for(i=0; i < N - k; ++i){
				putchar(' ');
			}
			count = 0;
		} else {
			putchar(c);
			++count;
		}
	}
	if(c == '\n')
		putchar(c);

	return c;
}

int atoi(char* i) {
	int val = 0;

	while(isdigit(*i)) {
		val = val * 10 + (*i - '0');
		i++;
	}

	return val;
}

int main(int argc, char *argv[]) {
	N = 8;

	do {
		if(--argc > 0)
			N = atoi(*++argv);
	} while(__detab() != EOF);

	return 0;
}
