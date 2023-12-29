#include<stdio.h>
#include<string.h>
#define MAXLEN 1024

void squeeze(char s1[], char s2[]);

int main() {
	char s1[] = "hello, my little friend";
	char s2[] = "abcde";

	squeeze(s1, s2);
	printf("%s\n", s1);
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
	while(i < lens1) {
		while(j < lens2) {
			if(s2[j++] == s1[i]) {
				--j;
				break;
			}
		}
		if(j == lens2) {
			s3[k++] = s1[i];
		}
		j = 0;
		++i;
	}
	s3[k] = '\0';
	k = 0;
	while(k < lens1 && s3[k] != '\0') {
		s1[k] = s3[k];
		++k;
	}
	s1[k] = s3[k];
	return;
}
