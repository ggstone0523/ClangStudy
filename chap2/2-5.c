#include<stdio.h>
#include<string.h>

int any(char s1[], char s2[]);

int main() {
	char s1[] = "you've got a friend from me";
	char s2[] = "fkl";
	int location;

	location = any(s1, s2);
	printf("%d\n", location);
	return 0;
}

int any(char s1[], char s2[]) {
	int lens1 = strlen(s1);
	int lens2 = strlen(s2);
	int i, j;

	i = 0;
	j = 0;
	while(i < lens1) {
		while(j < lens2) {
			if(s2[j++] == s1[i]) {
				return i;
			}
		}
		j = 0;
		++i;
	}
	return -1;
}
