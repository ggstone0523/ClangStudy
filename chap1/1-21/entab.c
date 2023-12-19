#include <stdio.h>

#define N 8 /* location of tab stop */

int printEntab(void);

int main()
{
	while(printEntab() > 0);

	return 0;
}

/* change space to tab */
int printEntab(void)
{
	char c;
	int count, spaceCount, i;

	count = 0;
	spaceCount = 0;
	while((c = getchar()) != '\n' && c != EOF){
		if(count == 8){
			if(spaceCount > 1){
				putchar('\t');
			} else if(spaceCount == 1) {
				putchar(' ');
			}
			count = 0;
			spaceCount = 0;
		} 
		
		if(c ==' ') {
		        ++spaceCount;
		} else {
			for(i = 0; i < spaceCount; i++){
				putchar(' ');
			}
			putchar(c);
			spaceCount = 0;
		}
		++count;
	}
	if(c == '\n')
		putchar(c);

	return count;
}
