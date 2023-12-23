#include<stdio.h>
#define MAXLINE 1000

int isLineComments = 0;

void deleteComment(char line[]);
void putline(char line[]);
int getsline(char line[], int maxline);

int main()
{
	int len;
	char line[MAXLINE];

	while((len = getsline(line, MAXLINE)) > 0) {
		deleteComment(line);
		putline(line);
	}
	return 0;
}

void deleteComment(char line[]) {
	char beforeC, currC;
	int index = 0;
	int commentIndex = -1;
	int sQSt, dQSt;

	if(isLineComments == 1) {
		commentIndex = 1;
	}

	beforeC = ' ';
	sQSt = 0;
	dQSt = 0;
	while((currC = line[index]) != '\0') {
		if(currC == '\'') {
			if(sQSt == 0 && commentIndex == -1) {
				sQSt = 1;
			} else if(sQSt == 1) {
				sQSt = 0;
			}
		}
		if(currC == '\"') {
			if(dQSt == 0 && commentIndex == -1) {
				dQSt = 1;
			} else if(dQSt == 1) {
				dQSt = 0;
			}
		}
		if(beforeC == '/' && (currC == '/' || currC == '*') && commentIndex == -1 && sQSt == 0 && dQSt == 0) {
			commentIndex = index;
			line[index-1] = '\0';
			if(currC == '*') {
				isLineComments = 1;
			}
		}
		if(isLineComments == 1 && currC == '/' && beforeC == '*') {
			isLineComments = 0;
			commentIndex = -1;
		}
		if(commentIndex > -1) {
			line[index] = '\0';
		}
		++index;
		beforeC = currC;
	}
	commentIndex -= 2;
	while(commentIndex > -1) {
		if(line[commentIndex] != '\t' && line[commentIndex] != ' ') {
			break;
		}
		line[commentIndex] = '\0';
		--commentIndex;
	}
	if(commentIndex > -1) {
		line[commentIndex+1] = '\n';
	}
	return;
}

int getsline(char line[], int maxline) {
	char c;
	int index = 0;

	while((c = getchar()) != '\n') {
		if(c == EOF) {
			break;
		}
		if(index == maxline) {
			break;
		}
		line[index] = c;
		++index;
	}
	if(c == '\n') {
		line[index] = c;
	}
	line[index+1] = '\0';
	return index;
}

void putline(char line[]) {
	int index = 0;
	while(line[index] != '\0') {
		putchar(line[index]);
		++index;
	}
	return;
}
