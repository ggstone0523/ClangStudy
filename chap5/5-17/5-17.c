#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000
#define MAXLEN 1024
char *lineptr[MAXLINES];
char *fieldlineptr[MAXLINES][MAXLEN];

int getLine(char line[], int maxline);
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);
void swap(void *v[], int i, int j);
int numcmp(char *, char *);
int dictcmp(char *, char *);
void tolowerstr(char temp[], char *v);
void qSort(void *lineptr[], int lowerupperEq, int left, int right, int (*comp)(void *, void *));
void qSortReverse(void *lineptr[], int lowerupperEq, int left, int right, int (*comp)(void *, void *));
void splitlinefield(char *fieldlineptr[][MAXLEN]);

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

int dictcmp(char *s1, char *s2) {
	int i = 0;
	char temps1[MAXLEN];
	char temps2[MAXLEN];

	i = 0;
	while(*s1 != '\0') {
		if(!(*s1 == ' ' || (*s1 >= 'a' && *s1 <= 'z') || (*s1 >= 'A' && *s1 <= 'Z') || (*s1 >= '0' && *s1 <= '9'))) {
			s1++;
			continue;
		}
		temps1[i] = *s1;
		i++;
		s1++;
	}
	temps1[i] = '\0';

	i = 0;
	while(*s2 != '\0') {
		if(!(*s2 == ' ' || (*s2 >= 'a' && *s2 <= 'z') || (*s2 >= 'A' && *s2 <= 'Z') || (*s2 >= '0' && *s2 <= '9'))) {
			s2++;
			continue;
		}
		temps2[i] = *s2;
		i++;
		s2++;
	}
	temps2[i] = '\0';

	return strcmp(temps1, temps2);
}

void tolowerstr(char temp[], char v[]) {
	int i = 0;

	while(v[i] != '\0') {
		temp[i] = tolower(v[i]);
		i++;
	}
}

void qSort(void *v[], int lowerupperEq, int left, int right, int (*comp)(void *, void *)) {
	int i, last, cmpAns;
	char tempi[MAXLEN];
	char templeft[MAXLEN];

	if(left >= right)
		return;
	swap(v, left, (left + right)/2);
	last = left;
	for(i = left + 1; i <= right; i++) {
		if(lowerupperEq) {
			tolowerstr(tempi, v[i]);
			tolowerstr(templeft, v[left]);
			cmpAns = (*comp)(tempi, templeft);
		} else
			cmpAns = (*comp)(v[i], v[left]);
		if(cmpAns < 0)
			swap(v, ++last, i);
	}
	swap(v, left, last);
	qSort(v, lowerupperEq, left, last-1, comp);
	qSort(v, lowerupperEq, last+1, right, comp);
}

void qSortReverse(void *v[], int lowerupperEq, int left, int right, int (*comp)(void *, void *)) {
	int i, last, cmpAns;
	char tempi[MAXLEN];
	char templeft[MAXLEN];

	if(left >= right)
		return;
	swap(v, left, (left + right)/2);
	last = left;
	for(i = left + 1; i <= right; i++) {
		if(lowerupperEq) {
			tolowerstr(tempi, v[i]);
			tolowerstr(templeft, v[left]);
			cmpAns = (*comp)(tempi, templeft);
		} else
			cmpAns = (*comp)(v[i], v[left]);
		if(cmpAns > 0)
			swap(v, ++last, i);
	}
	swap(v, left, last);
	qSortReverse(v, lowerupperEq, left, last-1, comp);
	qSortReverse(v, lowerupperEq, last+1, right, comp);
}

void splitlinefield(char *fieldlineptr[][MAXLEN]) {
	int ptrlineidx = 0;
	int ptrlenidx = 0;
	int len, nlines;
	int startlineidx = 0;
	int lineidx = 0;
	char *p, line[MAXLEN];

	nlines = 0;
	while((len = getLine(line, MAXLEN)) > 0) {
		if(nlines >= MAXLINES)
			return;
		else {
			lineidx = 0;
			ptrlenidx = 0;
			while(1) {
				startlineidx = lineidx;
				while(line[lineidx] != ',' && line[lineidx] != '\0' && line[lineidx] != '\n') {
					lineidx++;
				}
		                p = malloc(sizeof(char) * len);
				if(p == NULL)
					return;
				line[lineidx] = '\0';
				strcpy(p, &line[startlineidx]);
				fieldlineptr[ptrlineidx][ptrlenidx] = p;
				ptrlenidx++;
				if(lineidx == len) {
					break;
				}
				lineidx++;
			}
		}
		ptrlineidx++;
		nlines++;
	}

	int i, j;
	for(i = 0; i < ptrlineidx; i++) {
		for(j = 0; j < 7; j++) {
			printf("%s ", fieldlineptr[i][j]);
		}
		printf("\n");
	}
}

int main(int argc, char *argv[]) {
	int nlines;
	int lowerupperEq = 0;
	int fieldsort = 0;
	void (*sort)(void *v[], int, int, int, int (*)(void *, void *)) = qSort;
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
					lowerupperEq = 1;
					break;
				case 'd':
					cmp = (int (*)(void *, void *))dictcmp;
					break;
				case 's':
					fieldsort = 1;
					splitlinefield(fieldlineptr);
					return 0;
					break;
			}
		}
	}

	if((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		(*sort)((void **)lineptr, lowerupperEq, 0, nlines-1, cmp);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("input too big to sort\n");
		return 1;
	}
}
