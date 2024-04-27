#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000
#define MAXLEN 1024
char *lineptr[MAXLINES];

int getLine(char line[], int maxline);
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);
void swap(void *v[], int i, int j);
int numcmp(char *, char *);
int ulestrcmp(char *, char *);
void qSort(void *lineptr[], int left, int right, int (*comp)(void *, void *));
void qSortReverse(void *lineptr[], int left, int right, int (*comp)(void *, void *));

int getLine(char line[], int maxline) {
	int i = 0;
	char c;

	while((c = getchar()) != '\n' && c != EOF) {
		if(i < maxline) {
			line[i] = c;
			i++;
		}
	}
	line[i] = '\n';

	return i;
}

int readlines(char *lineptr[], int maxlines) {
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while((len = getLine(line, MAXLEN)) > 0) {
		if(nlines >= maxlines || (p = malloc(sizeof(char) * len)) == NULL)
			return -1;
		else {
			line[len] = '\0';
			strcpy(p, line);
			lineptr[nlines] = p;
			nlines++;
		}
	}
	return nlines;
}

void writelines(char *lineptr[], int nlines) {
	while(--nlines >= 0)
		printf("%s\n", *lineptr++);
}

void swap(void *v[], int i, int j) {
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

int numcmp(char *s1, char *s2) {
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);
	if(v1 < v2)
		return -1;
	else if(v1 > v2)
		return 1;
	else
		return 0;
}

int ulestrcmp(char *s1, char *s2) {
	char temps1[MAXLEN];
	char temps2[MAXLEN];
	int i;
	
	i = 0;
	while(*s1 != '\0') {
		temps1[i] = tolower(*s1);
		i++;
		s1++;
	}
	temps1[i] = *s1;

	i = 0;
	while(*s2 != '\0') {
		temps2[i] = tolower(*s2);
		i++;
		s2++;
	}
	temps2[i] = *s2;

	return strcmp(temps1, temps2);
}

void qSort(void *v[], int left, int right, int (*comp)(void *, void *)) {
	int i, last;

	if(left >= right)
		return;
	swap(v, left, (left + right)/2);
	last = left;
	for(i = left + 1; i <= right; i++)
		if((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qSort(v, left, last-1, comp);
	qSort(v, last+1, right, comp);
}

void qSortReverse(void *v[], int left, int right, int (*comp)(void *, void *)) {
	int i, last;

	if(left >= right)
		return;
	swap(v, left, (left + right)/2);
	last = left;
	for(i = left + 1; i <= right; i++)
		if((*comp)(v[i], v[left]) > 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qSortReverse(v, left, last-1, comp);
	qSortReverse(v, last+1, right, comp);
}

int main(int argc, char *argv[]) {
	int nlines;
	int numeric = 0;
	void (*sort)(void *v[], int, int, int (*)(void *, void *)) = qSort;
	int (*cmp)(void *, void *) = (int (*)(void *, void *))strcmp;

	while(--argc > 0) {
		while(*(++argv[argc]) != '\0') {
			switch(*argv[argc]) {
				case 'n':
					cmp = (int (*)(void *, void *))numcmp;
					break;
				case 'r':
					sort = qSortReverse;
					break;
				case 'f':
					cmp = (int (*)(void *, void *))ulestrcmp;
					break;
			}
		}
	}

	if((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		(*sort)((void **)lineptr, 0, nlines-1, cmp);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("input too big to sort\n");
		return 1;
	}
}
