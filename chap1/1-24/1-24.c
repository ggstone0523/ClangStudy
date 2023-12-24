#include<stdio.h>
#include<stdlib.h>

void printError(char c);

int main() {
	char stack[1000];
	int top = -1;

	int singleQuotesStack = 0;
	int doubleQuotesStack = 0;

	int commentsInLine = 0;
	int commentsOverLine = 0;

	int numberEscapeSeq = 0;

	char c, beforeC;

	beforeC = ' ';
	while((c = getchar()) != EOF) {
		if(c == '\\' && singleQuotesStack != 1 && doubleQuotesStack != 1) {
			printError('\\');
		} else if(beforeC == '\\' && (singleQuotesStack == 1 || doubleQuotesStack == 1) && c != 'a' && c != 'b' && c != 'f' && c != 'n' && c != 'r' && c != 't' && c != 'v' && c != '\\' && c != '\'' && c != '"' && c != '?' && c != '0' && c != 'n' && c != 'x' && c != 'u') {
			printError(c);
		} else if(beforeC == '\\' && (singleQuotesStack == 1 || doubleQuotesStack == 1) && (c == 'n' || c == 'x' || c == 'u')) {
			numberEscapeSeq = 1;
			beforeC = c;
			continue;
		} else if(beforeC == '\\' && (singleQuotesStack == 1 || doubleQuotesStack == 1) && (c == '\'' || c == '"')) {
			beforeC = c;
			continue;
		}

		if(c == '\'' && singleQuotesStack == 0 && doubleQuotesStack == 0 && commentsInLine == 0 && commentsOverLine == 0) {
			singleQuotesStack = 1;
			beforeC = c;
			continue;
		} else if(c == '"' && singleQuotesStack == 0 && doubleQuotesStack == 0 && commentsInLine == 0 && commentsOverLine == 0) {
			doubleQuotesStack = 1;
			beforeC = c;
			continue;
		} else if(c == '\'' && singleQuotesStack == 1) {
			if(numberEscapeSeq == 1) {
				printError('8');
			}
			singleQuotesStack = 0;
			beforeC = c;
			continue;
		} else if(c == '"' && doubleQuotesStack == 1) {
			if(numberEscapeSeq == 1) {
				printError('8');
			}
			doubleQuotesStack = 0;
			beforeC = c;
			continue;
		} else if(c == '\n' && singleQuotesStack == 1) {
			printError('\'');
		} else if(c == '\n' && doubleQuotesStack == 1) {
			printError('"');
		}

		if(beforeC == '/' && c == '*' && singleQuotesStack == 0 && doubleQuotesStack == 0 && commentsInLine == 0 && commentsOverLine == 0) {
			commentsOverLine = 1;
			beforeC = c;
			continue;
		} else if(beforeC == '/' && c == '/' && singleQuotesStack == 0 && doubleQuotesStack == 0 && commentsInLine == 0 && commentsOverLine == 0) {
			commentsInLine = 1;
			beforeC = c;
			continue;
		} else if(c == '\n') {
			numberEscapeSeq = 0;
			commentsInLine = 0;
			beforeC = c;
			continue;
		} else if(beforeC == '/' && c != '/' && c != '*' && singleQuotesStack == 0 && doubleQuotesStack == 0 && commentsInLine == 0 && commentsOverLine == 0) {
			printError('/');
		} else if(beforeC == '*' && c == '/') {
			commentsOverLine = 0;
			beforeC = c;
			continue;
		} else if(beforeC == '*' && c != '/' && singleQuotesStack == 0 && doubleQuotesStack == 0 && commentsInLine == 0 && commentsOverLine == 0) {
			printError('*');
		}
		beforeC = c;

		if(singleQuotesStack == 1 || doubleQuotesStack == 1 || commentsInLine == 1 || commentsOverLine == 1) {
			continue;
		}

		if(c == '(' || c == '[' || c == '{') {
			++top;
			stack[top] = c;
		} else if(c == ')') {
			if(top > -1 && stack[top] == '(') {
				--top;
			} else {
				printError('p');
			}
		} else if(c == ']') {
			if(top > -1 && stack[top] == '[') {
				--top;
			} else {
				printError('p');
			}
		} else if(c == '}') {
			if(top > -1 && stack[top] == '{') {
				--top;
			} else {
				printError('p');
			}
		}
	}
	if(commentsOverLine == 1) {
		printError('*');
	}
	printf("success!\n");
	return 0;
}

void printError(char c) {
	printf("Error : %c\n", c);
	exit(1);
}
