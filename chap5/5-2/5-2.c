#include <stdio.h>
#include <ctype.h>

#define SIZE 1024
#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch();
void ungetch(int c);
int getfloat(double *pn);

int getch() {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
	if(bufp >= BUFSIZE)
		printf("ungetch: too many character\n");
	else
		buf[bufp++] = c;
}

// 5-2 homework answer: type of getfloat function's return function value is int;
int getfloat(double *pn) {
	int c, sign, point;
	
	while(isspace(c = getch()));

	if(!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);
		return 0;
	}

	sign = (c == '-') ? -1 : 1;

	if(c == '+' || c == '-') {
		c = getch();
	}

	for(*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');

	if(c == '.') { // 5-2 homework answer: Added logic to calculate the decimal point after the dot;
		c = getch();		
	} else {
		*pn *= sign;
		return c;
	}

	for(point = 1; isdigit(c); c = getch(), point *= 10)
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	*pn /= point;
	
	if(c != EOF)
		ungetch(c);
	return c;
}

int main() {
	int n;
	double array[SIZE] = {0.0,};
	int idx;

	for(n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++);

	for(idx = 0; idx < n; idx++)
		printf("%f\n", array[idx]);

	return 0;
}
