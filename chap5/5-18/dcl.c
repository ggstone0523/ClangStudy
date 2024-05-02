#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define MAXLEN 1024

enum { NAME, PARENS, BRACKETS };

void dcl();
void dirdcl();
char getch();
void ungetch(char c);
int gettoken();

int tokentype;
int bufidx = -1;
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

void dcl() {
	int ns;

	for(ns = 0; gettoken() == '*';)
		ns++;
	dirdcl();
	while(ns-- > 0)
		strcat(out, " pointer to");
}

void dirdcl() {
	int type;

	if(tokentype == '(') {
		dcl();
		if(tokentype != ')')
			printf("error: missing )\n");
	} else if(tokentype == NAME)
		strcpy(name, token);
	else
		printf("error: expected name or (dcl)\n");

	while((type = gettoken()) == PARENS || type == BRACKETS) {
		if(type == PARENS)
			strcat(out, " function returning");
		else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
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
		} else if (c == '\n' || c == EOF){
			printf("error: missing )\n");
			strcpy(token, "()");
			ungetch(c);
			return tokentype = PARENS;
		} else {
			ungetch(c);
			return tokentype = '(';
		}
	} else if(c == '[') {
		for(*p++ = c; (*p++ = getch()) != ']' && (isdigit(*(p-1))););
		if(*(p-1) != ']') {
			printf("error: missing ]\n");
			ungetch(*(p-1));
			*(p-1) = ']';
		}
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

int main() {
	while(gettoken() != EOF) {
		strcpy(datatype, token);
		out[0] = '\0';
		dcl();
		if(tokentype != '\n')
			printf("syntax error\n");
		printf("%s: %s %s\n", name, out, datatype);
	}

	return 0;
}
