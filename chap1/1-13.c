#include <stdio.h>

#define IN 1
#define OUT 0

/* print a histogram of the length of words in its input */
int main()
{
	int c, i, j, nword, state;
	int ndigit[22];

	state = OUT;

	for(i = 0; i < 22; ++i)
		ndigit[i] = 0;

	while((c = getchar()) != EOF) {
		if(c == ' ' || c == '\n' || c == '\t' || c == ','){
			if(state != OUT)
				++ndigit[nword];
			nword = 0;
                        if(c == ',')
                                ++ndigit[1];
                        state = OUT;
                }
                else if(state == OUT)
                        state = IN;

		if(state == IN)
                        ++nword;
	}

	for(i = 30; i >= 1; --i){
		printf("%2d", i);
		for(j = 1; j < 22; ++j){
			if(ndigit[j] >= i)
				printf("  X");
			else
				printf("   ");
		}
		putchar('\n');
	}
	printf("  ");
	for(i = 1; i < 22; ++i){
		printf("%3d", i);
	}
	putchar('\n');
	return 0;
}
