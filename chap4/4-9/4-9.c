#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define NUMBER '0'
#define UEOF '#'
#define SIN 1 + '>' // 4-5,4-6 homework answer: SIN - FALSE is defined for switch statements;
#define COS 2 + '>'
#define TAN 3 + '>'
#define ASIN 4 + '>'
#define ACOS 5 + '>'
#define ATAN 6 + '>'
#define ATAN2 7 + '>'
#define SINH 8 + '>'
#define COSH 9 + '>'
#define TANH 10 + '>'
#define EXP 11 + '>'
#define LOG 12 + '>'
#define LOG10 13 + '>'
#define POW 14 + '>'
#define SQRT 15 + '>'
#define CEIL 16 + '>'
#define FLOOR 17 + '>'
#define FABS 18 + '>'
#define LDEXP 19 + '>'
#define FREXP 20 + '>'
#define MODF 21 + '>'
#define FMOD 22 + '>'
#define PVAL 23 + '>'
#define FALSE 24 + '>'
#define VARIABLE 25 + '>'
#define MAXOP 100
#define MAXVAL 100
#define BUFSIZE 100
#define STRELEMENTNUM 23
#define NUMOFVAL 26

int sp = 0;
double val[MAXVAL];
char buf[BUFSIZE];
char *arrstrelement[STRELEMENTNUM] = { // 4-5,4-6 homework answer: array of calculation's str elements for compare calculation formula's string elements;
	"sin", "cos", "tan", "asin", "acos",
	"atan", "atan2", "sinh", "cosh", "tanh",
	"exp", "log", "log10", "pow", "sqrt",
	"ceil", "floor", "fabs", "ldexp", "frexp",
	"modf", "fmod", "pval"
};
int bufp = 0;
int getvaridx = -1; // 4-6 homework answer: index of arrresultvar;
double arrresultvar[NUMOFVAL]; // 4-6 homework answer: save variable in calculation formula;
int arrresultvarbitcheck = 0; // 4-6 homework answer: check variable in calculation formula has never been assigned;
int pval = 0; // 4-6 homework answer: save most recently printed value;
int isthereprecal = 0; // 4-6 homework answer: check if there was a previous calculation;

void push(double f);
double pop();
void printtop(); // 4-4 homework answer: print stack's top element;
double copytop(); // 4-4 homework answer: copy and return stack's top element;
void swaptop(); // 4-4 homework answer: swap stack's top element and second top element;
void clear(); // 4-4 homework answer: clear stack;
int isempty(); // 4-6 homework answer: check if stack is empty; 

int getval(char c); // 4-6 homework answer: check character in calculation is name of variable;

int getstrelement(char c); // 4-5,4-6 homework answer: check if calculation's str elements in calculation formula;

int getch();
void ungetch(int c);
void testpushbackeof(); // 4-9 homework answer: test pushed-back EOF

/* 4-7 homework answer:
 * push back an entire string onto the input,
 * don't need to know about buf and bufp, can just use ungetch;
 */
void ungets(char s[]);

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

int isempty() {
	return sp == 0;
}

int getch() {
	char c;
	if(bufp > 0) {
		return buf[--bufp];
	} else { // 4-9 homework answer: return '#' when getchar function's return value is EOF;
		c = getchar();
		return (c == EOF) ? UEOF : c;
	}
}

void ungetch(int c) {
	if(bufp >= BUFSIZE) {
		printf("ungetch: too many character\n");
	} else {
		if(c == EOF) { // 4-9 homework answer: '#' save to buffer when c variable is EOF;
			buf[bufp++] = UEOF;
		} else {
			buf[bufp++] = c;
		}
	}
}

void testpushbackeof() { // 4-9 homework answer: test pushed-back EOF
	ungetch(EOF);
	printf("EOF: %c\n\n", getch());
}

/* 4-7 homework answer:
 * push back an entire string onto the input,
 * don't need to know about buf and bufp, can just use ungetch;
 */
void ungets(char s[]) {
	int i = 0;
	while(s[i] != '\0')
		i++;
	while(--i >= 0)
		ungetch(s[i]);
}

int getval(char c) { // 4-6 homework answer: check character in calculation is name of variable;
	char n;
	n = getch();
	ungetch(n);
	if((n >= 'a' && n <= 'z') || (n >= 'A' && n <= 'Z')) {
		return 0;
	} else {
		getvaridx = tolower(c) - 'a';
		return 1;
	}
}

int getstrelement(char c) { // 4-5,4-6 homework answer: check if calculation's str elements in calculation formula;
	int i = 0;
	char strelement[MAXOP];

	strelement[i++] = c;
	while(((strelement[i++] = tolower((c = getch()))) >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
	strelement[--i] = '\0';
	ungetch(c);
	for(i = 0; i < STRELEMENTNUM; i++) {
		if(strcmp(strelement, arrstrelement[i]) == 0) {
			return i + '?';
		}
	}
	return FALSE;
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
	if(!isdigit(c) && c != '.') {
		if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
			if(getval(c)) {
				return VARIABLE;
			} else {
				return getstrelement(c); // 4-5 homework answer: call getmathlib for check if mathlib's string in calculation formula;
			}
		} else {
			return c;
		}
	}
	i = 0;
	if(isdigit(c))
		while(isdigit(s[++i] = c = getch()));
	if(c == '.')
		while(isdigit(s[++i] = c = getch()));
	s[i] = '\0';
	if(c != UEOF) // 4-9 homework answer: change EOF to UEOF('#')
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

	testpushbackeof(); // 4-9 homework answer: test pushed-back EOF

	while((type = getop(s)) != UEOF) { // 4-9 homework answer: change EOF to UEOF('#')
		switch(type) {
		case NUMBER:
			push(atof(s));
			break;
		case VARIABLE: // 4-6 homework answer: add case VARIABLE for calculation of variable in calculation formula;
			if((getvaridx != -1) && (arrresultvarbitcheck & (1 << getvaridx)))
				push(arrresultvar[getvaridx]);
			break;
		case '=': // 4-6 homework answer: add case '=' for substitution operation;
			if(getvaridx != -1) {
				arrresultvar[getvaridx] = pop();
				push(arrresultvar[getvaridx]);
				arrresultvarbitcheck |= (1 << getvaridx);
			} else {
				printf("error: variable not decleared\n");
			}
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
		case PVAL: // 4-6 homework answer: add case PVAL for calculation of most recently printed value;
			if(isthereprecal == 1) 
				push(pval);
			else
				printf("error: previous calculation is none\n");
			break;
		case '\n':
			/* 4-6 homework answer: get pval from top of stack when calculation formula is end, 
			 * and set isthereprecal for previous calculation is exist;
			 */
			pval = copytop();
			isthereprecal = 1;
			printf("\t%.8g\n", pop());
			if(!isempty()) {
				printf("error: there's a problem with the formula\n");	
			}
			break;
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	}
	return 0;
}
