#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1024

struct wordval {
	char word[SIZE];
	int count;
	struct wordval *left;
	struct wordval *right;
};

struct wordcnt {
	int count;
	char word[SIZE];
	struct wordcnt *next;
};

struct wordval *makewordval();
struct wordcnt *makewordcnt();
char getword(char *word, int wordsize);
struct wordval *getwordval(char *word, struct wordval **wordvalhead);
void wordvalTowordcnt(struct wordval *wordvalhead);
void printwordcnt(struct wordcnt *wordcnthead);
char getch();
void ungetch(char c);
struct wordval *wordvalhead = NULL;
struct wordcnt *wordcnthead = NULL;
char buf[SIZE];
int bufidx = -1;

char getch() {
	return ((bufidx < 0) ? getchar() : buf[bufidx--]);
}

void ungetch(char c) {
	if(bufidx >= SIZE-1) {
		printf("buffer size over!\n");
		return;
	} else {
		bufidx++;
		buf[bufidx] = c;
	}
}

struct wordval *makewordval() {
	return (struct wordval *)malloc(sizeof(struct wordval));
}

struct wordcnt *makewordcnt() {
	return (struct wordcnt *)malloc(sizeof(struct wordcnt));
}

struct wordval *getwordval(char *word, struct wordval **wordvalhead) {
	struct wordval *p;
	struct wordval *prevp;
	int cmpresult = 0;
	int leftorright = 0;
	
	if((*wordvalhead) == NULL) {
		*wordvalhead = makewordval();
		strncpy((*wordvalhead)->word, word, SIZE);
		(*wordvalhead)->left = NULL;
		(*wordvalhead)->right = NULL;
		(*wordvalhead)->count = 1;

		return (*wordvalhead);
	}

	p = (*wordvalhead);
	while(p != NULL) {
		prevp = p;
		cmpresult = strcmp(p->word, word);
		if(cmpresult == 0) {
			p->count++;
			return p;
		} else if(cmpresult > 0) {
			p = p->left;
			leftorright = 0;
		} else {
			p = p->right;
			leftorright = 1;
		}
	}

	p = makewordval();
	strncpy(p->word, word, SIZE);
	p->left = NULL;
	p->right = NULL;
	p->count = 1;
	if(leftorright)
		prevp->right = p;
	else
		prevp->left = p;
	return p;
}

void wordvalTowordcnt(struct wordval *wordvalhead) {
	struct wordcnt *temp;
	struct wordcnt *p;
	struct wordcnt *prevp;
	
	if(wordvalhead != NULL) {
		wordvalTowordcnt(wordvalhead->left);
		temp = makewordcnt();
		strncpy(temp->word, wordvalhead->word, SIZE);
		temp->count = wordvalhead->count;
		temp->next = NULL;
		p = wordcnthead;
		prevp = wordcnthead;
		while(p != NULL) {
			if(p->count < temp->count) {
				if(p != wordcnthead) {
					temp->next = p;
					prevp->next = temp;
				} else {
					temp->next = wordcnthead;
					wordcnthead = temp;
				}
				break;
			}
			prevp = p;
			p = p->next;
		}
		if(p == NULL && prevp == NULL)
			wordcnthead = temp;
		else if(p == NULL && prevp != NULL)
			prevp->next = temp;
		wordvalTowordcnt(wordvalhead->right);
	}
}

void printwordcnt(struct wordcnt *wordcnthead) {
	while(wordcnthead != NULL) {
		printf("%d: %s\n", wordcnthead->count, wordcnthead->word);
		wordcnthead = wordcnthead->next;
	}
}

char getword(char *word, int wordsize) {
	char c;

	while(isspace(c = getch()) && c != '\n');

	if(!isalpha(c)) {
		*word = '\0';
		return c;
	} 

	*word = c;
	word++;
	while(isalnum((c = getch())) && wordsize > 0) {
		*word = c;
		word++;
		wordsize--;
	}
	ungetch(c);
	*word = '\0';

	return c;
}

int main() {
	char word[SIZE];

	while(getword(word, SIZE) != EOF) {
		if(isalpha(word[0])) {
			getwordval(word, &wordvalhead);
		}
	}
	wordvalTowordcnt(wordvalhead);
	printwordcnt(wordcnthead);
	return 0;
}
