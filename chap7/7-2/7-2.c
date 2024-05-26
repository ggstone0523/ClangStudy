#include <stdio.h>
#include <ctype.h>

#define MAXSIZE 1024

int isPunctuationMark(char c);
char getch();
void ungetch(char c);
char buf[MAXSIZE];
int bufidx = -1;

char getch() {
	return (bufidx > -1) ? buf[bufidx--] : getchar();
}

void ungetch(char c) {
	if(bufidx >= MAXSIZE-1)
		printf("SIZE IS OVER\n");
	else
		buf[++bufidx] = c;
}

int isPunctuationMark(char c) {
	char punctMarks[] = {'\n', '.', ',', '?', '!', ':', ';'};
	int punctMarksLen = sizeof(punctMarks) / sizeof(char);

	while(--punctMarksLen > -1)
		if(c == punctMarks[punctMarksLen])
			return 1;
	return 0;
}

int main() {
	char c;
	int lineLen = 0;

	while((c = getch()) != EOF) {
		lineLen++;
		if(isgraph(c))
			printf("%c", c);
		else
			printf("0x%X", c);
		
		if((lineLen >= 10 && isPunctuationMark(c)) || (c == '\n')) {
			if((c = getch()) != '\n') {
				lineLen = 0;
				printf("\n");
			}
			ungetch(c);
		}
	}
	return 0;
}
