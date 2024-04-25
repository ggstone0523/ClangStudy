#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINE 1024
#define MAXLEN 1024

char *strs[MAXLINE] = {NULL, };
char *stk[MAXLINE];
int strsidx = 0;
int stkidx = 0;

char getLine();
int atoI(char* i);

char getLine() {
	char line[MAXLEN];
	char *buf;
	char c;
	int idx = 0;

	while((c = getchar()) != '\n' && c != EOF && idx < MAXLEN) {
		line[idx] = c;
		idx++;
	}

	if(strsidx == MAXLEN)
		strsidx = 0;
	
	if(idx == 0 && c == EOF) {
		return EOF;
	}

	if(idx == MAXLEN)
		line[idx-1] = '\0';
	else
		line[idx] = '\0';
	
	buf = (char*)malloc(sizeof(char) * (idx + 1));
	
	idx = 0;
	while(line[idx] != '\0') {
		*(buf+idx) = line[idx];
		idx++;
	}
	*(buf+idx) == '\0';
	
	if(strs[strsidx] != NULL) {
		free(strs[strsidx]);
	}
	strs[strsidx] = buf;
	strsidx++;

	return c;
}

int atoI(char* i) {
        int val = 0;

        while(isdigit(*i)) {
                val = val * 10 + (*i - '0');
                i++;
        }

        return val;
}

int main(int argc, char *argv[]) {
	int n = 10;

	if(argc != 2) {
		printf("Usage: ./tail -2\n");
		return 0;
	}

	if(*argv[1] == '-') {
		n = atoI(argv[1]+1);
	}

	if(n > MAXLINE) {
		n = MAXLINE;
	}

	while(getLine() != EOF);
	while(n > 0) {
		--strsidx;
		stk[stkidx] = strs[strsidx];
		--n;
		stkidx++;
		if(strsidx == 0 && strs[MAXLINE-1] != NULL)
			strsidx = MAXLINE-1;
		else if(strsidx == 0 && strs[MAXLINE-1] == NULL)
			break;
	}


	while(stkidx > 0) {
		--stkidx;
		printf("%s\n", stk[stkidx]);
	}

	return 0;	
}
