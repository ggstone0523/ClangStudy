#include <stdio.h>
#include <stdarg.h>

void minprintf(char *fmt, ...);

void minprintf(char *fmt, ...) {
	va_list ap;
	char *p, *sval;
	int ival;
	double dval;

	va_start(ap, fmt);
	for(p = fmt; *p; p++) {
		if(*p != '%') {
			putchar(*p);
			continue;
		}
		switch(*++p) {
		case 'd':
			ival = va_arg(ap, int);
			printf("%d", ival);
			break;
		case 'f':
			dval = va_arg(ap, double);
			printf("%f", dval);
			break;
		case 's':
			for(sval = va_arg(ap, char *); *sval; sval++)
				putchar(*sval);
			break;
		case 'o':
			ival = va_arg(ap, int);
			printf("%o", ival);
			break;
		case 'x':
			ival = va_arg(ap, int);
			printf("%x", ival);
			break;
		default:
			putchar(*p);
			break;
		}
	}
	va_end(ap);
}

int main() {
	char *str = "word";

	minprintf("hello world\n");
	minprintf("hello %s\n", str);
	minprintf("%d is one\n", 1);
	minprintf("%o\n", 'c');
	minprintf("%x\n", 'c');

	return 0;
}
