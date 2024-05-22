#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define HASHSIZE 64
#define CHBUFSIZE 1024

struct keyvalue {
	char *key;
	char *value;
	struct keyvalue *next;
};
struct keyvalue *hashtable[HASHSIZE];
char buf[CHBUFSIZE];
int bufidx = -1;

unsigned int hash(char *s);
struct keyvalue *lookup(char *key);
void install(char *key, char *value);
char getch();
void ungetch(char c);
int getword(char word[]);

char getch() {
	return (bufidx < 0) ? getchar() : buf[bufidx--];
}

void ungetch(char c) {
	if(bufidx >= CHBUFSIZE - 1)
		printf("SIZE IS OVER!\n");
	else {
		bufidx++;
		buf[bufidx] = c;
	}
}

unsigned int hash(char *s) {
	unsigned int hashval = 0;

	for(;*s != '\0'; s++)
		hashval = *s + hashval * 31;

	hashval = hashval % HASHSIZE;
	return hashval;
}

struct keyvalue *lookup(char *key) {
	int hashval = hash(key);
	struct keyvalue *tablevalue;

	tablevalue = hashtable[hashval];
	while(tablevalue != NULL) {
		if(strcmp(tablevalue->key, key) == 0)
			break;
		tablevalue = tablevalue->next;
	}
	return tablevalue;
}

void install(char *key, char *value) {
	int hashval = hash(key);
	struct keyvalue *tablevalue;
	struct keyvalue *temp;

	if((tablevalue = lookup(key)) == NULL) {
		tablevalue = (struct keyvalue *)malloc(sizeof(struct keyvalue));
		tablevalue->key = strdup(key);
		tablevalue->next = NULL;
		if(hashtable[hashval] == NULL) 
			hashtable[hashval] = tablevalue;
		else {
			temp = hashtable[hashval];
			while(temp->next != NULL)
				temp = temp->next;
			temp->next = tablevalue;
		}

	} else {
		free(tablevalue->value);
	}
	tablevalue->value = strdup(value);
}

int getword(char word[]) {
	char c;
	int wordidx = 0;
	
	c = getch(); 
	while((isalnum(c) || c == '#') && wordidx < 1024) {
		word[wordidx++] = c;
		c = getch();
	}
	if(wordidx == 1024)
		wordidx--;
	word[wordidx] = '\0';
	ungetch(c);
	return c;
}

int main() {
	char word[1024];
	char key[1024];
	char value[1024];
	int isdefine = 0;
	struct keyvalue *tablevalue;

	while(getword(word) != EOF) {
		if((tablevalue = lookup(word)) != NULL) {
			printf("%s", tablevalue->value);
		} else {
			printf("%s", word);
		}
		putchar(getch());
		
		if(isdefine == 1) {
			strcpy(key, word);
			isdefine++;
		} else if(isdefine == 2) {
			strcpy(value, word);
			isdefine++;
		} else if(isdefine == 3) {
			install(key, value);
			isdefine = 0;
		}
		if(strcmp(word, "#define") == 0)
			isdefine++;
	}

	return 0;
}
