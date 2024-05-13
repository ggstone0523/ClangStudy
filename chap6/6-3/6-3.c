#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1024

struct wordloc {
	int loc;
	struct wordloc *next;
};

struct wordval {
	char word[SIZE];
	struct wordloc *loclist;
	struct wordval *left;
	struct wordval *right;
};

struct wordloc *makewordloc();
struct wordval *makewordval();
char getword(char *word, int wordsize);
struct wordval *getwordval(char *word, int loc, struct wordval **wordvalhead);
void printwordval(struct wordval *wordvalhead);
int checknoiseword(char *word);
char getch();
void ungetch(char c);
struct wordval *wordvalhead = NULL;
char buf[SIZE];
int bufidx = -1;
int line = 1;

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

struct wordloc *makewordloc() {
	return (struct wordloc *)malloc(sizeof(struct wordloc));
}

struct wordval *makewordval() {
	return (struct wordval *)malloc(sizeof(struct wordval));
}

struct wordval *getwordval(char *word, int loc, struct wordval **wordvalhead) {
	struct wordval *p;
	struct wordval *prevp;
	struct wordloc *ploc;
	struct wordloc *prevploc;
	int cmpresult = 0;
	int leftorright = 0;
	
	if((*wordvalhead) == NULL) {
		*wordvalhead = makewordval();
		strncpy((*wordvalhead)->word, word, SIZE);
		(*wordvalhead)->left = NULL;
		(*wordvalhead)->right = NULL;
		(*wordvalhead)->loclist = makewordloc();
		(*wordvalhead)->loclist->loc = loc;
		(*wordvalhead)->loclist->next = NULL;

		return (*wordvalhead);
	}

	p = (*wordvalhead);
	while(p != NULL) {
		prevp = p;
		cmpresult = strcmp(p->word, word);
		if(cmpresult == 0) {
			if(p->loclist == NULL) {
				p->loclist = makewordloc();
				p->loclist->loc = loc;
			} else {
				prevploc = p->loclist;
				ploc = p->loclist;
				while(ploc != NULL) {
					if(ploc->loc == loc)
						return p;
					prevploc = ploc;
					ploc = ploc->next;
				}
				prevploc->next = makewordloc();
				prevploc->next->loc = loc;
			}
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
	p->loclist = makewordloc();
	p->loclist->loc = loc;
	p->loclist->next = NULL;
	if(leftorright)
		prevp->right = p;
	else
		prevp->left = p;
	return p;
}

int checknoiseword(char *word) {
	int listlen = 0;
	
	char *noisewords[] = {
		"the",
		"and",
		"is",
		"or",
		"between",
		"s",
		"a"
	};

	listlen = sizeof(noisewords) / sizeof(char *);
	while(listlen-- > 0) {
		if(strcmp(noisewords[listlen], word) == 0)
			return 0;
	}

	return 1;
}

void printwordval(struct wordval *wordvalhead) {
	struct wordloc *p;

	if(wordvalhead != NULL) {
		printwordval(wordvalhead->left);
		printf("%s:", wordvalhead->word);
		p = wordvalhead->loclist;
		while(p != NULL) {
			printf("%d ", p->loc);
			p = p->next;
		}
		putchar('\n');
		printwordval(wordvalhead->right);
	}
}

char getword(char *word, int wordsize) {
	char c;

	while(isspace(c = getch()) && c != '\n');

	if(c == '\n')
		line++;
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
		if(isalpha(word[0]) && checknoiseword(word)) {
			getwordval(word, line, &wordvalhead);
		}
	}
	printwordval(wordvalhead);

	return 0;
}
