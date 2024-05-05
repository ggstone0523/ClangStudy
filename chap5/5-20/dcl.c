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
int isdataandqual(char token[]);
void dataandqual(char datatype[]);

int tokentype;
int prevtoken = 0;
int bufidx = -1;
int isargu = 0;
int isinparens = 0;
char token[MAXTOKEN];
char name[MAXTOKEN];
char argu[MAXTOKEN] = {'\0', };
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
		isinparens = 1;
		dcl();
		if(tokentype != ')')
			printf("error: missing )\n");
		else if(isargu) {
			strcat(out, " (argument: ");
			strcat(out, argu);
			strcat(out, ")");
			strcat(out, " function returning");
			isargu = 0;
		}
		isinparens = 0;
	} else if(tokentype == NAME) {
		if(isdataandqual(token) == 1 && isinparens) {
			isargu = 1;
			strcpy(argu, token);	
			while(gettoken() == NAME || tokentype == ',') {
				strcat(argu, " ");
				if(tokentype == ',')
					strcat(argu, ",");
				else
					strcat(argu, token);
			}
			prevtoken = 1;
		} else
			strcpy(name, token);
	} else
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

	if(tokentype == '(') {
		dirdcl();
	}
}

int gettoken() {
	int c;
	char *p = token;

	if(prevtoken) {
		prevtoken = 0;
		return tokentype;
	}

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

int isdataandqual(char token[]) {
	int i = 0;
	char *dataarr[] = {"int", "float", "double",  "char", "signed", "unsigned", "short", "long", "const", "static", "void"};
	
	for(i = 0; i < 11; i++) {
		if(strcmp(token, dataarr[i]) == 0)
			return 1;
	}
	return 0;
}

void dataandqual(char datatype[]) {
	strcpy(datatype, token);
	while(gettoken() == NAME) {
		if(isdataandqual(token) == 0)
			break;
		else {
			strcat(datatype, " ");
			strcat(datatype, token);
		}
	}
	prevtoken = 1;
}

int main() {
	while(gettoken() != EOF) {
		dataandqual(datatype);
		out[0] = '\0';
		dcl();
		if(tokentype != '\n')
			printf("syntax error\n");
		printf("%s: %s %s\n", name, out, datatype);
	}

	return 0;
}
