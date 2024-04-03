#include <stdio.h>

char bufc = '\0';
int toggle = 0;

int getch();
void ungetch(int c);

int getch() {
	if(toggle) {
		toggle ^= 1;
		return bufc;
	} else {
		return getchar();
	}
}

void ungetch(int c) {
	if(!toggle) {
		toggle ^= 1;
		bufc = c;
	}
}

int main() {
	char a, b, c;
	a = getch();
	b = getch();
	ungetch(a);
	printf("%c\n", getch());
	c = getch();
	ungetch(b);
	ungetch(c);
	printf("%c\n", getch());
	ungetch(c);
	printf("%c\n", getch());
	return 0;
}
