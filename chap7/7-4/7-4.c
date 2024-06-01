#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

void minscanf(char *fmt, ...);
int atoo(char *s);
int atox(char *s);
int getstr(char s[], char *p);

int atoo(char *s) {
	int ival = 0;
	if(*s == '0')
		s++;

	while(*s != '\0') {
		if(*s >= '0' && *s <= '7')
			ival = ival * 8 + (*s - '0');
		s++;
	}

	return ival;	
}

int atox(char *s) {
	int ival = 0;
	
	if(*s == '0') {
		s++;
		if(*s == 'x' || *s == 'X')
			s++;
		else
			s--;
	}

	while(*s != '\0') {
		if(*s >= '0' && *s <= '9')
			ival = ival * 16 + (*s - '0');
		else if(*s >= 'a' && *s <= 'f')
			ival = ival * 16 + (*s - 'a' + 10);
		else if(*s >= 'A' && *s <= 'F')
			ival = ival * 16 + (*s - 'A' + 10);
		s++;
	}

	return ival;	
	
}

int getstr(char s[], char *p) {
	int isminus = 1;
	int sidx = 0;
	char c;
	
	for(c = getchar(); c != *(p+1) && c!= '\n'; c = getchar()) {
		if(c == '-') {
			isminus = -1;
			continue;
		}
		s[sidx] = c;
		sidx++;	
	}
	s[sidx] = '\0';

	return isminus;
}

void minscanf(char *fmt, ...) {
	va_list ap;
	char c;
	char s[1024];
	char *cval, *p;
	char **sval;
	int *ival;
	double *dval;
	int isminus = 1;

	va_start(ap, fmt);
	for(p = fmt; *p; p++) {
		if(*p != '%')
			continue;
		
		isminus = 1;
		switch(*++p) {
		case 'd':
			ival = va_arg(ap, int *);
			isminus = getstr(s, p);
			*ival = atoi(s) * isminus;
			break;
		case 'u':
			ival = va_arg(ap, int *);
			getstr(s, p);
			*ival = atoi(s);
			break;
		case 'i':
			ival = va_arg(ap, int *);
			getstr(s, p);
			if(s[0] == '0') {
				if(s[1] == 'x' || s[1] == 'X')
					*ival = atox(s);
				else
					*ival = atoo(s);
			} else
				*ival = atoi(s);
			break;
		case 'e':
		case 'g':
		case 'f':
			dval = va_arg(ap, double *);
			isminus = getstr(s, p);
			*dval = atof(s) * isminus;
			break;
		case 's':
			sval = va_arg(ap, char **);
			getstr(s, p);
			*sval = strdup(s);
			break;
		case 'c':
			cval = va_arg(ap, char *);
			*cval = getchar();
			getchar();
			break;
		case 'o':
			ival = va_arg(ap, int *);
			getstr(s, p);
			*ival = atoo(s);
			break;
		case 'x':
			ival = va_arg(ap, int *);
			getstr(s, p);
			*ival = atox(s);
			break;
		default:
			break;
		}
	}
	va_end(ap);
}

int main() {
	int d, o, x, i;
	unsigned int u;
	char c;
	char *s;
	double f, e, g;
	
	minscanf("%d %c %s %f %o %x %u %i %e %g", &d, &c, &s, &f, &o, &x, &u, &i, &e, &g);
	printf("%d %c %s %f %d %d %d %d %f %f\n", d, c, s, f, o, x, u, i, e, g);

	return 0;
}
