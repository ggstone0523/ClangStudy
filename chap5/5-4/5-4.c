#include <stdio.h>

int strend(char s[], char t[]);

int strend(char s[], char t[]) {
	int idx = 0;
	while(*s != '\0')
		s++;
	while(*t != '\0') {
		idx++;
		t++;
	}
	s -= idx;
	t -= idx;
	while(*t != '\0' && *s == *t) {
		idx--;
		s++;
		t++;
	}
	if(idx == 0)
		return 1;
	else
		return 0;

}

int main() {
	char *s1 = "hello";
	char *t1 = "llo";
	
	char *s2 = "hello";
	char *t2 = "elo";

	printf("%s is in last of %s?: %c\n", t1, s1, strend(s1, t1) ? 'O' : 'X');
	printf("%s is in last of %s?: %c\n", t2, s2, strend(s2, t2) ? 'O' : 'X');
	return 0;
}
