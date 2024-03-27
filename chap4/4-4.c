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
void printtop(); // 4-4 homework answer: print stack's top element;
double copytop(); // 4-4 homework answer: copy and return stack's top element;
void swaptop(); // 4-4 homework answer: swap stack's top element and second top element;
void clear(); // 4-4 homework answer: clear stack;
void teststack(); // 4-4 homework test function;

int getch();
void ungetch(int c);
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

void printtop() { // 4-4 homework answer: function for print stack's top element;
	if(sp == 0) {
		printf("error: stack empty\n");
	} else
		printf("%g\n", val[sp-1]);
}

double copytop() { // 4-4 homework answer: function for copy and return stack's top element;
	if(sp == 0) {
		printf("error: stack empty\n");
		return 0.0;
	} else
		return val[sp-1];
}

void swaptop() { //  4-4 homework answer: function for swap stack's top element and second top element;
	int swap;
	if(sp >= 2) {
		swap = val[sp-1];
		val[sp-1] = val[sp-2];
		val[sp-2] = swap;

	} else
		printf("error: stack's element must be two or more\n");
}

void clear() { // 4-4 homework answer: function for clear stack;
	sp = 0;
}

void teststack() { // 4-4 homework test function;
	push(2.0);
	push(3.0);
	printtop();
	pop();
	printf("%g\n", copytop());
	push(3.0);
	swaptop();
	printf("%g\n", pop());
	printf("%g\n", pop());
	push(2.0);
	push(3.0);
	clear();
	printtop();

}

int getch() {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
	if(bufp >= BUFSIZE)
		printf("ungetch: too many character\n");
	else
		buf[bufp++] = c;
}

int getop(char s[]) {
	int i, c;
	while((s[0] = c = getch()) == ' ' || c == '\t');
	s[1] = '\0';
	if(c == '-') { // 4-3 homework answer: add if(c == '-') block for negative calculation;
		c = getch();
		ungetch(c);
		if(!isdigit(c)) {
			return '-';
		}
		s[0] = '-';
	}
	if(!isdigit(c) && c != '.')
		return c;
	i = 0;
	if(isdigit(c))
		while(isdigit(s[++i] = c = getch()));
	if(c == '.')
		while(isdigit(s[++i] = c = getch()));
	s[i] = '\0';
	if(c != EOF)
		ungetch(c);
	return NUMBER;
}

int main() {
	int type;
	double op2;
	char s[MAXOP];

	teststack(); // 4-4 homework test function;

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
		case '%': // 4-3 homework answer: add case '%' for modulus calculation;
			op2 = pop();
			if(op2 != 0.0)
				push((int)pop() % (int)op2);
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
