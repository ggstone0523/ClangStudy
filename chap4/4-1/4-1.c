#include <stdio.h>
#define MAXLINE 1000

int getLine(char line[], int max);
int strindex(char source[], char searchfor[]);

char pattern[] = "ould";

int main() {
	char line[MAXLINE];
	int found = 0;
	int foundIdx = 0;
	
	printf("Search for %s\n\n", pattern);

	while(getLine(line, MAXLINE) > 0) {
		if((foundIdx = strindex(line, pattern)) >= 0) {
			printf("%s: %d\n", line, foundIdx);
			found++;
		}
	}
	return found;
}

int getLine(char line[], int max) {
	int c, i;

	i = 0;
	while(--max > 0 && (c = getchar()) != EOF && c != '\n')
		line[i++] = c;
	if(c == '\n')
		line[i++] = c;
	line[i] = '\0';
	return i;
}

int strindex(char source[], char searchfor[]) {
	int i, j, k;
	for(i = 0; source[i] != '\0'; i++) {
		for(j = i, k = 0; ((searchfor[k] != '\0') && (source[j] == searchfor[k])); j++, k++);
		if((k > 0) && (searchfor[k] == '\0')) {
			return i + k - 1;
		}
	}
	return -1;
}
