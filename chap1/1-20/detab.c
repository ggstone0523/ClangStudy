#include <stdio.h>

#define N 10 /* location of tab stop */

int printDetab(void);

int main()
{
	while(printDetab() > 0);

	return 0;
}

/* change tab to space */
int printDetab(void)
{
	char c;
	int count, i;

	count = 0;
	while((c = getchar()) != '\n' && c != EOF){
		if(c == '\t'){
			for(i=0; i < N - (count % N); ++i){
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

	return count;
}
