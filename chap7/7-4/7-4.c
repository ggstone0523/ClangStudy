#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

void minscanf(char *fmt, ...);
int atoo(char *s);
int atox(char *s);

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

void minscanf(char *fmt, ...) {
	va_list ap;
	char c;
	char s[1024];
	int sidx = 0;
	char *cval, *p;
	char **sval;
	int *ival;
	double *dval;
	int isminus = 1;

	va_start(ap, fmt);
	for(p = fmt; *p; p++) {
		if(*p != '%')
			continue;
		
		sidx = 0;
		isminus = 1;
		switch(*++p) {
		case 'd':
			ival = va_arg(ap, int *);
			for(c = getchar(); c != *(p+1) && c!= '\n'; c = getchar()) {
				if(c == '-') {
					isminus = -1;
					continue;
				}
				s[sidx] = c;
				sidx++;	
			}
			s[sidx] = '\0';
			*ival = atoi(s) * isminus;
			break;
		case 'u':
			ival = va_arg(ap, int *);
			for(c = getchar(); c != *(p+1) && c!= '\n'; c = getchar()) {
				s[sidx] = c;
				sidx++;	
			}
			s[sidx] = '\0';
			*ival = atoi(s);
			break;
		case 'i':
			ival = va_arg(ap, int *);
			for(c = getchar(); c != *(p+1) && c!= '\n'; c = getchar()) {
				s[sidx] = c;
				sidx++;	
			}
			s[sidx] = '\0';
			if(s[0] == '0') {
				if(s[1] == 'x' || s[1] == 'X')
					*ival = atox(s);
				else
					*ival = atoo(s);
			} else
				*ival = atoi(s);
			break;
		case 'f':
			dval = va_arg(ap, double *);
			for(c = getchar(); c != *(p+1) && c != '\n'; c = getchar()) {
				if(c == '-') {
					isminus = -1;
					continue;
				}
				s[sidx] = c;
				sidx++;
			}
			s[sidx] = '\0';
			*dval = atof(s) * isminus;
			break;
		case 's':
			sval = va_arg(ap, char **);
			for(c = getchar(); c != *(p+1) && c != '\n'; c = getchar()) {
				s[sidx] = c;
				sidx++;
			}
			s[sidx] = '\0';
			*sval = strdup(s);
			break;
		case 'c':
			cval = va_arg(ap, char *);
			*cval = getchar();
			getchar();
			break;
		case 'o':
			ival = va_arg(ap, int *);
			for(c = getchar(); c != *(p+1) && c!= '\n'; c = getchar()) {
				s[sidx] = c;
				sidx++;	
			}
			s[sidx] = '\0';
			*ival = atoo(s);
			break;
		case 'x':
			ival = va_arg(ap, int *);
			for(c = getchar(); c != *(p+1) && c!= '\n'; c = getchar()) {
				s[sidx] = c;
				sidx++;	
			}
			s[sidx] = '\0';
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
	double f;
	
	minscanf("%d %c %s %f %o %x %u %i", &d, &c, &s, &f, &o, &x, &u, &i);
	printf("%d %c %s %f %d %d %d %d\n", d, c, s, f, o, x, u, i);

	return 0;
}
