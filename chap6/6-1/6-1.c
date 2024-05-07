#include <stdio.h>
#include <ctype.h>

#define MAXSIZE 1024

char buf[MAXSIZE];
int bufidx = -1;

char getch();
void ungetch(char c);
int getword(char *word, int lim);
char word[MAXSIZE];

char getch() {
	return ((bufidx < 0) ? getchar() : buf[bufidx--]);
}

void ungetch(char c) {
	if(bufidx >= MAXSIZE-1) {
		printf("error: size is over!\n");
	} else {
		bufidx++;
		buf[bufidx] = c;
	}
}

int getword(char *word, int lim) {
	char prevc;
	char c;
	int whatisthischar = 0;
	char *w = word;

	while(isspace(c = getch()));

	if(c != EOF)
		*w++ = c;

	if(!isalpha(c)) {
		switch(c) {
		case '_':
			whatisthischar = 0;
			break;
		case '"':
			whatisthischar = 1;
			break;
		case '/':
			if((c = getch()) == '/') {
				*w++ = c;
				whatisthischar = 2;
			} else if(c == '*') {
				*w++ = c;
				whatisthischar = 3;
			} else {
				ungetch(c);
				*w = '\0';
				return 0;
			}
			break;
		case '#':
			whatisthischar = 4;
			break;
		default:
			*w = '\0';
			return c;
		}
	}

	switch(whatisthischar) {
	case 0:
		for(; --lim > 0; w++) {
			if(!isalnum(*w = getch()) && *w != '_') {
				ungetch(*w);
				break;
			}
		}
		break;
	case 1:
		prevc = c;
		for(; --lim > 0; w++) {
			c = getch();
			if((prevc != '\\') && (c  == '"')) {
				break;
			}
			prevc = c;
			*w = c;
		}
		*w = c;
		w++;
		break;
	case 2:
		for(; --lim > 0; w++) {
			if((*w = getch()) == '\n') {
				ungetch(*w);
				break;
			}
		}
		break;
	case 3:
		prevc = c;
		for(; --lim > 0; w++) {
			c = getch();
			if((prevc == '*') && (c == '/')) {
				break;
			}
			prevc = c;
			*w = c;
		}
		*w = c;
		w++;
		break;
	case 4:
		for(; --lim > 0; w++) {
			if((*w = getch()) == ' ') {
				ungetch(*w);
				break;
			}
		}
		break;
	default:
		printf("error!\n");
		break;

	}

	*w = '\0';
	return word[0];
}

int main() {
	while(getword(word, MAXSIZE) != EOF) {
		printf("%s\n", word);
	}

	return 0;
}
