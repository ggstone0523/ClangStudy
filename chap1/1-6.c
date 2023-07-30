#include <stdio.h>

/* test getchar() != EOF is 0 or 1 */
int main()
{
	int c;

	while(c = getchar() != EOF)
		printf("%d\n", c);
	printf("%d\n", c);

	return 0;
}
