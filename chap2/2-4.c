#include<stdio.h>
#include<string.h>
#define MAXLEN 1024

void squeeze(char s1[], char s2[]);

int main() {
	char s1[] = "abcde";
	char s2[] = "hello, my little friend";

	squeeze(s1, s2);
	printf("%s\n", s2);
	return 0;
}

void squeeze(char s1[], char s2[]) {
	char s3[MAXLEN];
	int lens1 = strlen(s1);
	int lens2 = strlen(s2);
	int i, j, k;

	i = 0;
	j = 0;
	k = 0;
	while(j < lens2) {
		while(i < lens1) {
			if(s1[i++] == s2[j]) {
				--i;
				break;
			}
		}
		if(i == lens1) {
			s3[k++] = s2[j];
		}
		i = 0;
		++j;
	}
	s3[k] = '\0';
	k = 0;
	while(k < lens2 && s3[k] != '\0') {
		s2[k] = s3[k];
		++k;
	}
	s2[k] = s3[k];
	return;
}
