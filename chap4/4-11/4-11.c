#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100
#define BUFSIZE 100

int sp = 0;
double val[MAXVAL];
char buf[BUFSIZE];
int bufp = 0;

void push(double f);
double pop();
int getch();
int getop(char s[]);


void push(double f) {
	if(sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

double pop() {
	if(sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

int getch() {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

int getop(char s[]) {
	int i, c;
	static char n = '\0';  // 4-11 homework answer: delete ungetch using internal static variable (43 - 48 line, 58-59 line)
	if(n != ' ' && n != '\t' && n != '\0')
		s[0] = c = n;
	else
		while((s[0] = c = getch()) == ' ' || c == '\t');
	n = '\0';
	s[1] = '\0';
	if(!isdigit(c) && c != '.')
		return c;
	i = 0;
	if(isdigit(c))
		while(isdigit(s[++i] = c = getch()));
	if(c == '.')
		while(isdigit(s[++i] = c = getch()));
	s[i] = '\0';
	if(c != EOF)
		n = c;
	return NUMBER;
}

int main() {
	int type;
	double op2;
	char s[MAXOP];

	while((type = getop(s)) != EOF) {
		switch(type) {
		case NUMBER:
			push(atof(s));
			break;
		case '+':
			push(pop() + pop());
			break;
		case '*':
			push(pop() * pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '/':
			op2 = pop();
			if(op2 != 0.0)
				push(pop() / op2);
			else
				printf("error: zero divisor\n");
			break;
		case '\n':
			printf("\t%.8g\n", pop());
			break;
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	}
	return 0;
}
