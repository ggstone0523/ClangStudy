#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define MAXSIZE 1024

struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};
struct troot {
	char sword[MAXWORD];
	struct tnode *root;
	struct troot *left;
	struct troot *right;
};
char buf[MAXSIZE];
int bufidx = -1;
struct troot *troothead = NULL;

struct tnode *addtree(struct tnode *p, char *w);
void treeprint(struct tnode *p);
int getword(char *word, int lim);
struct tnode *talloc();
char *strDup(char *s);
char getch();
void ungetch(char c);
struct troot *getroot(char *w, struct troot *troothead, int n);
void multitreeprint(struct troot *troothead);

char getch() {
	return ((bufidx < 0) ? getchar() : buf[bufidx--]);
}

void ungetch(char c) {
	if(bufidx >= 1023) {
		printf("buffer size over!\n");
		return;
	} else {
		bufidx++;
		buf[bufidx] = c;
	}
}

int getword(char *word, int lim) {
	int c;
	int prevc;
	char *w = word;
	int whatiswordtype = 0;

	while(isspace(c = getch()));

	if(c != EOF)
		*w++ = c;
	if(!isalpha(c)) {
		if(c == '\"')
			whatiswordtype = 1;
		else if (c == '/'){
			c = getch();
			if(c == '/')
				whatiswordtype = 2;
			else if(c == '*')
				whatiswordtype = 3;
			else {
				ungetch(c);
				*w = '\0';
				return c;
			}
		} else {
			*w = '\0';
			return c;
		}
	}

	switch(whatiswordtype) {
	case 0:
		for(; --lim > 0; w++)
			if(!isalnum(*w = getch())) {
				ungetch(*w);
				break;
			}
		break;
	case 1:
		prevc = c;
		c = getch();
		while((!((prevc != '\\') && (c == '"'))) && (c != EOF)) {
			prevc = c;
			c = getch();
		}
		return c;
	case 2:
		while((c = getch()) != '\n' && (c != EOF));
		return c;
	case 3:
		prevc = c;
		c = getch();
		while((!((prevc == '*') && (c == '/'))) && (c != EOF)) {
			prevc = c;
			c = getch();
		}
		return c;
	}

	*w = '\0';
	return word[0];
}

char *strDup(char *s) {
	char *p;

	p = (char *)malloc(strlen(s) + 1);
	if(p != NULL)
		strcpy(p, s);
	return p;
}

struct tnode *talloc() {
	return (struct tnode *)malloc(sizeof(struct tnode));
}

struct troot *tralloc() {
	return (struct troot *)malloc(sizeof(struct troot));
}

void multitreeprint(struct troot *troothead) {
	if(troothead != NULL) {
		multitreeprint(troothead->left);
		printf("%s\n", troothead->sword);
		treeprint(troothead->root);
		printf("\n");
		multitreeprint(troothead->right);
	}
}

void treeprint(struct tnode *p) {
	if(p != NULL) {
		treeprint(p->left);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->right);
	}
}

struct tnode *addtree(struct tnode *p, char *w) {
	int cond;

	if(p == NULL) {
		p = talloc();
		p->word = strDup(w);
		p->count = 1;
		p->left = p->right = NULL;
	} else if((cond = strcmp(w, p->word)) == 0)
		p->count++;
	else if(cond < 0)
		p->left = addtree(p->left, w);
	else
		p->right = addtree(p->right, w);
	return p;
}

struct troot *gettroot(char *w, struct troot **troothead, int n) {
	struct troot *temp = *troothead;
	struct troot *prevtemp;
	char word[MAXWORD];
	int cmpret = 0;
	int rightorleft = 0;
	
	if(*troothead == NULL) {
		*troothead = tralloc();
		strncpy((*troothead)->sword, w, n);
		(*troothead)->sword[n] = '\0';
		(*troothead)->left = NULL;
		(*troothead)->right = NULL;
		return *troothead;
	}

	while(temp !=  NULL) {
		cmpret = strncmp(temp->sword, w, n);
		prevtemp = temp;
		if(cmpret == 0) 
			return temp;
		else if(cmpret < 0) {
			temp = temp->right;
			rightorleft = 0;
		} else if(cmpret > 0) {
			temp = temp->left;
			rightorleft = 1;
		}
	}

	temp = tralloc();
	strncpy(temp->sword, w, n);
	temp->sword[n] = '\0';
	if(rightorleft) {
		prevtemp->left = temp;
	} else {
		prevtemp->right = temp;
	}
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

int main(int argc, char *argv[]) {
	struct troot *tnoderoot;
	char word[MAXWORD];
	int n = 6;

	if(argc == 2) {
		n = atoi(argv[1]);
	}

	tnoderoot = NULL;
	while(getword(word, MAXWORD) != EOF)
		if(isalpha(word[0])) {
			tnoderoot = gettroot(word, &troothead, n);
			tnoderoot->root = addtree(tnoderoot->root, word);
		}
	multitreeprint(troothead);
	return 0;
}
