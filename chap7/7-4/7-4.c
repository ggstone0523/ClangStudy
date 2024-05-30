#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

void minscanf(char *fmt, ...);

void minscanf(char *fmt, ...) {
	va_list ap;
	char c;
	char s[1024];
	int sidx = 0;
	char *cval, *p;
	char **sval;
	int *ival;
	double *dval;

	va_start(ap, fmt);
	for(p = fmt; *p; p++) {
		if(*p != '%')
			continue;
		
		sidx = 0;
		switch(*++p) {
		case 'd':
			ival = va_arg(ap, int *);
			for(c = getchar(); c != *(p+1) && c!= '\n'; c = getchar()) {
				s[sidx] = c;
				sidx++;	
			}
			s[sidx] = '\0';
			*ival = atoi(s);
			break;
		case 'f':
			dval = va_arg(ap, double *);
			for(c = getchar(); c != *(p+1) && c != '\n'; c = getchar()) {
				s[sidx] = c;
				sidx++;
			}
			s[sidx] = '\0';
			*dval = atof(s);
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
		default:
			break;
		}
	}
	va_end(ap);
}

int main() {
	int i;
	char c;
	char *s;
	double f;

	//minscanf("%d", &i);
	//printf("%d\n", i);
	
	minscanf("%d %c %s %f", &i, &c, &s, &f);
	printf("%d %c %s %f\n", i, c, s, f);

	return 0;
}
