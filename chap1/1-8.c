#include <stdio.h>

/* count space and tab in input */
int main()
{
	int c, nst;

	nst = 0;
	while((c = getchar()) != EOF)
	       if(c == ' ' || c == '\t')
		       ++nst;
	printf("%d\n", nst);

	return 0;
}
