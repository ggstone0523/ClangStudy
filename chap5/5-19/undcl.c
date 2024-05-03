#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define MAXLEN 1024

enum { NAME, PARENS, BRACKETS };

char getch();
void ungetch(char c);
int gettoken();

int tokentype;
int bufidx = -1;
int prevtoken = 0;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];
char buf[MAXLEN];

char getch() {
	return ((bufidx < 0) ? getchar() : buf[bufidx--]);
}

void ungetch(char c) {
	if(bufidx >= (MAXLEN - 1)) {
		printf("buf is full!\n");
	} else {
		bufidx++;
		buf[bufidx] = c;
	}
}

int gettoken() {
	int c;
	char *p = token;

	while((c = getch()) == ' ' || c == '\t');

	if(c == '(') {
		if((c = getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		} else {
			ungetch(c);
			return tokentype = '(';
		}
	} else if(c == '[') {
		for(*p++ = c; (*p++ = getch()) != ']' && (isdigit(*(p-1))););
		*p = '\0';
		return tokentype = BRACKETS;
	} else if(isalpha(c)) {
		for(*p++ = c; isalnum(c = getch());)
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	} else
		return tokentype = c;
}

int nexttype() {
	int type;

	prevtoken = 1;
	type = gettoken();
	return type;
}

int main() {
	int type;
	char temp[MAXTOKEN];

	while(gettoken() != EOF) {
		strcpy(out, token);
		while((type = (prevtoken ? type : gettoken())) != '\n') {
			prevtoken = 0;
			if(type == PARENS || type == BRACKETS)
				strcat(out, token);
			else if(type == '*') {
				if(((type = nexttype()) == PARENS) || (type == BRACKETS)) {
					sprintf(temp, "(*%s)", out);
				} else {
					sprintf(temp, "*%s", out);
				}
				strcpy(out, temp);
			} else if(type == NAME) {
				sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);
			} else
				printf("invalid input at %s\n", token);
		}
		printf("%s\n", out);
	}
	
	return 0;
}
