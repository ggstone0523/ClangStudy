#include <stdio.h>

/* print a histogram of the frequencies of different characters in its input */
int main()
{
	int c, i, j;
	int ndigit[26];

	for(i = 0; i < 22; ++i)
		ndigit[i] = 0;

	while((c = getchar()) != EOF) {
		if('a' <= c && c <= 'z')
			++ndigit[c-'a'];
		else if('A' <= c && c <= 'Z')
			++ndigit[c-'A'];
	}

	for(i = 30; i >= 1; --i){
		printf("%2d", i);
		for(j = 0; j < 26; ++j){
			if(ndigit[j] >= i)
				printf("  X");
			else
				printf("   ");
		}
		putchar('\n');
	}
	printf("  ");
	for(i = 0; i < 26; ++i){
		printf("  %c", i + 'A');
	}
	putchar('\n');
	return 0;
}
