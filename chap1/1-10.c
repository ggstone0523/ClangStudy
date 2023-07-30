#include <stdio.h>

/* change tab to /t, backspace to /b, \ to \\ in input and show user */
int main()
{
	int c;

	while((c = getchar()) != EOF) {
	       if (c == '\t') {
		       putchar('\\');
		       putchar('t');
	       } else if (c == '\b') {
	       	       putchar('\\');
		       putchar('b');
	       } else if (c == '\\') {
	               putchar('\\');
		       putchar('\\');
	       } else {
	               putchar(c);
	       }
	}
	
	return 0;
}
