#include <stdio.h>
#include <ctype.h>
#include <limits.h>

#define BUFSIZE 100
#define NUMBER '0'

int getLine(char s[], int lim);
int atoi(char s[]);
double atof(char s[]);
void itoa(int n, char s[]);
void itob(int n, char s[], int b);
void itoapad(int n, char s[], int w);
int htoi(char s[]);
void reverse(char s[]);
int strindex(char s[], char t[]);
int getch();
void ungetch(int c);
int getop(char s[]);

char buf[BUFSIZE];
char *bufp = buf;
int bufidx = 0;

int getLine(char s[], int lim) {
	int c, slim;
	slim = lim;
	while(lim > 0 && (c = getchar()) != EOF && c != '\n') {
		*s = c;
		lim--;
		s++;
	}
	*s = '\0';
	return slim - lim;
}

int atoi(char s[]) {
	int val = 0;
	int sign = 1;
	while(isspace(*s))
		s++;
	if(*s == '-' || *s == '+') {
		if(*s == '-')
			sign = -1;
		s++;
	}
	while(isdigit(*s)) { 
		val = val * 10 + (*s - '0');
		s++;
	}
	return val * sign;
}

double atof(char s[]) {
	double val = 0;
	double dotaval = 0;
	int decimalpoint = 1;
	int eten = 0;
	int etensign = 1;
	double etenval = 1.0;
	int sign = 1;

	while(isspace(*s))
		s++;
	if(*s == '-' || *s == '+') {
		if(*s == '-')
			sign = -1;
		s++;
	}
	while(isdigit(*s)) { 
		val = val * 10 + (*s - '0');
		s++;
	}
	if(*s == '.')
		s++;
	while(isdigit(*s)) { 
		dotaval = dotaval * 10 + (*s - '0');
		decimalpoint *= 10;
		s++;
	}
	dotaval /= decimalpoint;
	val = val + dotaval;
	if(*s == 'e' || *s == 'E')
		s++;
	if(*s == '-') {
		etensign = -1;
		s++;
	}
	while(isdigit(*s)) {
		eten = eten * 10 + (*s - '0');
		s++;
	}
	if(etensign == 1) {
		while(eten > 0) {
			eten--;
			etenval *= 10;
		}
	}
	else {
		while(eten > 0) {
			eten--;
			etenval *= 10;
		}
		etenval = 1 / etenval;
	}

	return val * sign * etenval;

}

void itoa(int n, char s[]) {
	char sign = '\0';
	char *prevs = s;
	unsigned int un = n;

	if(n < 0) {
		sign = '-';
		un = -n;
	}
	while(un != 0) {
		*s = (un % 10) + '0';
		un /= 10;
		s++;
	}
	if(sign != '\0') {
		*s = sign;
		s++;
	}
	*s = '\0';
	reverse(prevs);
}

void itob(int n, char s[], int b) {
	char sign = '\0';
	char *prevs = s;
	unsigned int un = n;
	int remain = 0;

	if(n < 0) {
		sign = '-';
		un = -n;
	}
	while(un != 0) {
		remain = un % b;
		if(remain <= 9)
			remain += '0';
		else
			remain = remain - 10 + 'A';
		*s = remain;
		un /= b;
		s++;
	}
	if(sign != '\0') {
		*s = sign;
		s++;
	}
	*s = '\0';
	reverse(prevs);
}

void itoapad(int n, char s[], int w) {
	char sign = '\0';
	char *prevs = s;
	unsigned int un = n;

	if(n < 0) {
		sign = '-';
		un = -n;
	}
	while(un != 0) {
		*s = (un % 10) + '0';
		un /= 10;
		s++;
		w--;
	}
	if(sign != '\0') {
		*s = sign;
		s++;
		w--;
	}
	while(w > 0) {
		*s = ' ';
		s++;
		w--;
	}

	*s = '\0';
	reverse(prevs);
}

int htoi(char s[]) {
	int val = 0;
	int num;
	while(isspace(*s))
		s++;
	if(*s++ == '0' && (*s == 'x' || *s == 'X'))
		s++;
	else
		return 0;
	while(isdigit(*s) || ((*s >= 'A') && (*s <= 'F')) || ((*s >= 'a') && (*s <= 'f'))) {
		if((*s >= 'A') && (*s <= 'F'))
			num = *s - 'A' + 10;
		else if((*s >= 'a') && (*s <= 'f'))
			num = *s - 'a' + 10;
		else
			num = *s - '0';
		s++;
		val = val * 16 + num;
	}
	return val;
}

void reverse(char s[]) {
	char *p1 = s;
	char *p2 = s;
	char temp;

	while(*p2 != '\0') {
		p2++;
	}
	p2--;
	while(p1 < p2) {
		temp = *p1;
		*p1 = *p2;
		*p2 = temp;
		p1++;
		p2--;	
	}
}

int strindex(char s[], char t[]) {
	char *prevt = t;
	char *prevs = s;
	int prevsizet = 0;
	int idx = 0;
	int sizet = 0;
	while(*t != '\0') {
		t++;
		sizet++;
	}
	t = prevt;
	while(*s != '\0' && *t != '\0') {
		prevs = s;
		prevsizet = sizet;
		for(t = prevt; *s != '\0' && *t != '\0' && *s == *t; t++, s++)
			sizet--;
		if(sizet == 0)
			return idx;
		s = prevs;
		sizet = prevsizet;
		s++;
		idx++;
	}
	return -1;
}

int getch() {
	char c;
	if(bufidx > 0) {
		c = *bufp;
		bufidx--;
		bufp--;
	} else {
		c = getchar();
	}
	return c;
}

void ungetch(int c) {
	bufp++;
	bufidx++;
	*bufp = c;
}

int getop(char s[]) {
	int c, prevc;
	
	while((*s = c = getch()) == ' ' || c == '\t');
	s++;
	*s = '\0';
	if(!isdigit(c) && c != '.' && c != '-' && c != '+')
		return c;
	if(c == '-' || c == '+') {
		prevc = c;
		c = getch();
		if(!isdigit(c)) {
			ungetch(c);
			return prevc;
		}
		if(prevc == '+')
			s--;
		*s = c;
		s++;
	}
	if(isdigit(c)) {
		while(isdigit(*s = c = getch()))
			s++;
	}
	if(c == '.') {
		s++;
		while(isdigit(*s = c = getch()))
			s++;
	}
	*s = '\0';
	if(c != EOF)
		ungetch(c);
	return NUMBER;
}

int main() {
	char s[1024];
	char rs[] = "hello";
	char opstr[1024];
	int lim = 1024;
	int rval = 0;
	int switchval = 0;

	rval = getLine(s, lim);
	printf("%s's length is %d\n", s, rval);
	rval = getLine(s, lim);
	printf("%s's length is %d\n", s, rval);

	printf("int: str %s is %d\n", "  328", atoi("  328"));
	printf("int: str %s is %d\n", "  +328", atoi("  +328"));
	printf("int: str %s is %d\n", "-12345", atoi("-12345"));
	
	printf("hex: str %s is %d\n", "  0x497", htoi("  0X497"));
	printf("hex: str %s is %d\n", "0xafd4", htoi("0xafd4"));

	reverse(rs);
	printf("hello's reverse is %s\n", rs);

	itoa(328, s);
	printf("int: str %d is %s\n", 328, s);
	itoa(-12345, s);
	printf("int: str %d is %s\n", -12345, s);
	itoa(INT_MIN, s);
	printf("int: str %d is %s\n", INT_MIN, s);

	itob(4827, s, 16);
	printf("hex: str %d is %s\n", 4827, s);
	itob(4827, s, 8);
	printf("oct: str %d is %s\n", 4827, s);
	itob(4827, s, 2);
	printf("bin: str %d is %s\n", 4827, s);
	itob(-37495, s, 16);
	printf("hex: str %d is %s\n", -37495, s);
	itob(-37495, s, 8);
	printf("oct: str %d is %s\n", -37495, s);
	itob(-37495, s, 2);
	printf("bin: str %d is %s\n", -37495, s);

	itoapad(38237, s, 10);
	printf("%d: %s\n", 38237, s);
	itoapad(38237, s, 3);
	printf("%d: %s\n", 38237, s);
	itoapad(-38237, s, 10);
	printf("%d: %s\n", -38237, s);

	rval = strindex("hello", "ello");
	printf("%s start %d in %s\n", "ello", rval, "hello");
	rval = strindex("hello", "elh");
	printf("%s start %d in %s\n", "elh", rval, "hello");
	rval = strindex("hello", "ell");
	printf("%s start %d in %s\n", "ell", rval, "hello");
	rval = strindex("hello", "ll");
	printf("%s start %d in %s\n", "ll", rval, "hello");
	rval = strindex("hello", "llo");
	printf("%s start %d in %s\n", "llo", rval, "hello");

	printf("str %s is %f\n", "32.25", atof("32.25"));
	printf("str %s is %f\n", "-32.25", atof("-32.25"));
	printf("str %s is %f\n", "+32.25", atof("+32.25"));
	printf("str %s is %f\n", ".25", atof(".25"));
	printf("str %s is %f\n", "32.", atof("32."));
	printf("str %s is %f\n", "-32.0", atof("-32.0"));
	printf("str %s is %lf\n", "32.25e-3", atof("32.25e-3"));
	printf("str %s is %f\n", "-32.25E3", atof("-32.25E3"));

	while((switchval = getop(opstr)) != EOF) {
		switch(switchval) {
		case NUMBER:
			printf("NUMBER: %s\n", opstr);
			break;
		case '\n':
			printf("end of str\n");
			break;
		default:
			printf("default: %s\n", opstr);
			break;
		}
	}

	return 0;
}
