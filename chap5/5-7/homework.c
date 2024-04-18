#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#define MAXLINES 5000
#define MAXLEN 1000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int maxlines, char lines[MAXLINES][MAXLEN]);
void writelines(char *lineptr[], int nlines);

void qSort(char *v[], int left, int right);
void swap(char *v[], int i, int j);

int getLine(char s[], int lim);

int getLine(char s[], int lim) {
	int c, i;

	for(i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if(c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

// 5-7 homework answer: store lines in an array supplied by main, not using malloc to maintain storage
int readlines(char *lineptr[], int maxlines, char lines[MAXLINES][MAXLEN]) {
	int len, nlines, idx;

	nlines = 0;
	idx = 0;
	
	while((len = getLine(lines[idx], MAXLEN)) > 0) {
		if(nlines >= maxlines)
			return -1;
		else {
			lines[idx][len-1] = '\0';
			lineptr[nlines++] = lines[idx];
			idx++;
		}
	}

	return nlines;
}

void writelines(char *lineptr[], int nlines) {
	while(nlines-- > 0)
		printf("%s\n", *lineptr++);
}

void qSort(char *v[], int left, int right) {
	int i, last;
	
	if(left >= right)
		return;
	swap(v, left, (left+right)/2);
	last = left;
	for(i = left+1; i <= right; i++)
		if(strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qSort(v, left, last-1);
	qSort(v, last+1, right);
}

void swap(char *v[], int i, int j) {
	char *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

int main() {
	int nlines;
	char lines[MAXLINES][MAXLEN];
	struct timeval stop, start;
	
	gettimeofday(&start, NULL);
	if((nlines = readlines(lineptr, MAXLINES, lines)) >= 0) {
		qSort(lineptr, 0, nlines-1);
		writelines(lineptr, nlines);
		gettimeofday(&stop, NULL);
		printf("time 1:%lu\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);	
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
}

