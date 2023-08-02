#include <stdio.h>

#define IN 1 /* inside a word */
#define OUT 0 /* outside a word */

/* reads a file and outputs one word per line  */
int main()
{
	int c, state;

	state = OUT;

	while((c = getchar()) != EOF)
	{
		if(c == ' ' || c == '\n' || c == '\t' || c == ','){
			if(state != OUT)
				putchar('\n');
			if(c == ','){
				putchar(c);
				putchar('\n');
			}
			state = OUT;
		}
		else if(state == OUT)
			state = IN;
		
		if(state == IN)
			putchar(c);
	}

	return 0;
}
