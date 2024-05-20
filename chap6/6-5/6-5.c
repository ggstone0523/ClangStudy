#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASHSIZE 101

struct nlist {
	struct nlist *next;
	char *name;
	char *defn;
};
static struct nlist *hashtab[HASHSIZE];

unsigned int hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
int undef(char *s);
void printhashtable();

unsigned int hash(char *s) {
	unsigned int hashval;

	for(hashval = 0; *s != '\0'; s++) {
		hashval = *s + 31 * hashval;
	}
	return hashval % HASHSIZE;
}

struct nlist *lookup(char *s) {
	struct nlist *np;

	for(np = hashtab[hash(s)]; np != NULL; np = np->next)
		if(strcmp(s, np->name) == 0)
			return np;
	return NULL;
}

struct nlist *install(char *name, char *defn) {
	struct nlist *np;
	unsigned int hashval;

	if((np = lookup(name)) == NULL) {
		np = (struct nlist *)malloc(sizeof(*np));
		if(np == NULL || (np->name = strdup(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else
		free((void *)np->defn);
	if((np->defn = strdup(defn)) == NULL)
		return NULL;
	return np;
}

int undef(char *s) {
	struct nlist *np;
	struct nlist *prevnp;

	for(np = hashtab[hash(s)]; np != NULL; np = np->next)
		if(strcmp(s, np->name) == 0) {
			if(np == hashtab[hash(s)])
				hashtab[hash(s)] = np->next;
			else
				prevnp->next = np->next;
			free(np);
			return 1;	
		}
		prevnp = np;
	return 0;
}

void printhashtable() {
	int i;
	struct nlist *np;

	for(i = 0; i < HASHSIZE; i++) {
		if(hashtab[i] != NULL) {
			printf("%d:", i);
			for(np = hashtab[i]; np != NULL; np = np->next) {
				printf(" {%s, %s}", np->name, np->defn);
			}
			putchar('\n');
		}
	}
}

int main() {
	struct nlist *np;
	
	install("yusun", "firstname");
	install("choi", "lastname");
	install("KAI", "corp");
	install("kookmin univ", "university");
	install("tomato", "food");

	printhashtable();
	printf("-----------------------------------------------------\n");
	np = lookup("yusun");
	printf("key: yusun, lookup: %s\n", np->defn);

	printf("-----------------------------------------------------\n");
	printhashtable();
	printf("-----------------------------------------------------\n");
	undef("choi");
	printf("delete \"choi\" key\n");
	undef("tomato");
	printf("delete \"tomato\" key\n");
	printf("-----------------------------------------------------\n");
	printhashtable();

	return 0;
}
