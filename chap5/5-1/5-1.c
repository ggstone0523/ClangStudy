#include <stdio.h>
#include <ctype.h>

#define SIZE 1024
#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch();
void ungetch(int c);
int getint(int *pn);

int getch() {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
	if(bufp >= BUFSIZE)
		printf("ungetch: too many character\n");
	else
		buf[bufp++] = c;
}

int getint(int *pn) {
	int c, sign;
	
	while(isspace(c = getch()));

	if(!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);
		return 0;
	}

	sign = (c == '-') ? -1 : 1;

	if(c == '+' || c == '-') {
		c = getch();
	}

	/* 5-1 homework answer: add logic for if don't have a digit that follows + or -, 
	 * 			+ or - will be preceded by the digit that comes out first;
	 */
	do {
		if(!isspace(c))
			break;
	} while(c = getch());

	for(*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if(c != EOF)
		ungetch(c);
	return c;
}

int main() {
	int n;
	int array[SIZE] = {0,};
	int idx;

	for(n = 0; n < SIZE && getint(&array[n]) != EOF; n++);

	for(idx = 0; idx < n; idx++)
		printf("%d\n", array[idx]);

	return 0;
}
