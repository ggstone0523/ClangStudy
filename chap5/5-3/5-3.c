#include <stdio.h>

void strCat(char s[], char t[]) {
	while(*s)
		s++;
	while(*s = *t) {
		s++;
		t++;
	}
}

int main() {
	char s[] = "hello";
	char t[] = " world!";
	printf("\"%s\" + \"%s\": ", s, t);
	strCat(s, t);
	printf("%s\n", s);
}
