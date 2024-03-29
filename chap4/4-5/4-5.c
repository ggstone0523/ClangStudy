#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define NUMBER '0'
#define SIN 1 + '0' // 4-5 homework answer: SIN - FALSE is defined for switch statements;
#define COS 2 + '0'
#define TAN 3 + '0'
#define ASIN 4 + '0'
#define ACOS 5 + '0'
#define ATAN 6 + '0'
#define ATAN2 7 + '0'
#define SINH 8 + '0'
#define COSH 9 + '0'
#define TANH 10 + '0'
#define EXP 11 + '0'
#define LOG 12 + '0'
#define LOG10 13 + '0'
#define POW 14 + '0'
#define SQRT 15 + '0'
#define CEIL 16 + '0'
#define FLOOR 17 + '0'
#define FABS 18 + '0'
#define LDEXP 19 + '0'
#define FREXP 20 + '0'
#define MODF 21 + '0'
#define FMOD 22 + '0'
#define FALSE 23 + '0'
#define MAXOP 100
#define MAXVAL 100
#define BUFSIZE 100
#define MATHLIBNUM 22

int sp = 0;
double val[MAXVAL];
char buf[BUFSIZE];
char *arrmathlib[MATHLIBNUM] = { // 4-5 homework answer: array of mathlib's string for compare calculation formula's mathlib string;
	"sin", "cos", "tan", "asin", "acos",
	"atan", "atan2", "sinh", "cosh", "tanh",
	"exp", "log", "log10", "pow", "sqrt",
	"ceil", "floor", "fabs", "ldexp", "frexp",
	"modf", "fmod"
};
int bufp = 0;

void push(double f);
double pop();
void printtop(); // 4-4 homework answer: print stack's top element;
double copytop(); // 4-4 homework answer: copy and return stack's top element;
void swaptop(); // 4-4 homework answer: swap stack's top element and second top element;
void clear(); // 4-4 homework answer: clear stack;

int getmathlib(char c); // 4-5 homework answer: check if mathlib's string in calculation formula;

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

int getch() {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
	if(bufp >= BUFSIZE)
		printf("ungetch: too many character\n");
	else
		buf[bufp++] = c;
}

int getmathlib(char c) { // 4-5 homework answer: check if mathlib's string in calculation formula;
	int i = 0;
	char mathlibstr[MAXOP];

	if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
		mathlibstr[i++] = c;
		while(((mathlibstr[i++] = tolower((c = getch()))) >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
		mathlibstr[--i] = '\0';
		ungetch(c);
		for(i = 0; i < MATHLIBNUM; i++) {
			if(strcmp(mathlibstr, arrmathlib[i]) == 0) {
				return i + '1';
			}
		}
		return FALSE;

	} else {
		return c;
	}
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
		return getmathlib(c); // 4-5 homework answer: call getmathlib for check if mathlib's string in calculation formula; 
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
	double op1;
	double op2;
	int op;
	char s[MAXOP];
	char mathlib[MAXOP];

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
		case SIN:			// 4-5 homework answer: case SIN - case FMOD for calculation using mathlib;
			push(sin(pop()));
			break;
		case COS:
			push(cos(pop()));
			break;
		case TAN:
			push(tan(pop()));
			break;
		case ASIN:
			push(asin(pop()));
			break;
		case ACOS:
			push(acos(pop()));
			break;
		case ATAN:
			push(atan(pop()));
			break;
		case ATAN2:
			op2 = pop();
			if(op2 != 0.0)
				push(atan2(pop(), op2));
			else
				printf("error: zero divisor\n");
			break;
		case SINH:
			push(sinh(pop()));
			break;
		case COSH:
			push(cosh(pop()));
			break;
		case TANH:
			push(tanh(pop()));
			break;
		case EXP:
			push(exp(pop()));
			break;
		case LOG:
			op1 = pop();
			if(op1 != 0.0)
				push(log(op1));
			else
				printf("error: argument is zero \n");
			break;
		case LOG10:
			op1 = pop();
			if(op1 != 0.0)
				push(log10(op1));
			else
				printf("error: argument is zero \n");
			break;
		case POW:
			op2 = pop();
			op1 = pop();
			if(op1 == 0 && op2 <= 0)
				printf("error: if x is zero, y is bigger then zero \n");
			else {
				if(op1 < 0) 
					push(pow(op1, (int)op2));
				else
					push(pow(op1, op2));
			}
			break;
		case SQRT:
			op1 = pop();
			if(op1 != 0.0)
				push(sqrt(op1));
			else
				printf("error: argument is zero \n");
			break;
		case CEIL:
			push(ceil(pop()));
			break;
		case FLOOR:
			push(floor(pop()));
			break;
		case FABS:
			push(fabs(pop()));
			break;
		case LDEXP:
			op1 = pop();
			push(ldexp(pop(), op1));
			break;
		case FREXP:
			frexp(pop(), &op);
			push(op);
			break;
		case MODF:
			op2 = modf(pop(), &op1);
			push(op1);
			push(op2);
			break;
		case FMOD:
			op1 = pop();
			op2 = pop();
			if(op1 != 0.0)
				push(fmod(op2, op1));
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
