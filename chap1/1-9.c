#include <stdio.h>

/* erase continuous space in input and show user */
int main()
{
	int c;
	int isSpaceCont = 0;

	while((c = getchar()) != EOF) {
	       if (isSpaceCont != 1 && c == ' ') {
		       isSpaceCont = 1;
		       putchar(c);
	       } else if (isSpaceCont == 1 && c != ' ') {
	       	       isSpaceCont = 0;
		       putchar(c);
	       } else if (isSpaceCont != 1 || c != ' '){
	               putchar(c);
	       }
	}
	
	return 0;
}
