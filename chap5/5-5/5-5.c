#include <stdio.h>

char *strncpy(char s[], char t[], int n);
char *strncat(char s[], char t[], int n);
int strncmp(char s[], char t[], int n);

char *strncpy(char s[], char t[], int n) {
	while(n > 0 && *t != '\0') {
		*s = *t;
		s++;
		t++;
		n--;
	}
	if(n > 0)
		*s = '\0';
	return s;
}

char *strncat(char s[], char t[], int n) {
	while(*s != '\0')
		s++;
	while(n > 0 && *t != '\0') {
		*s = *t;
		s++;
		t++;
		n--;
	}
	*s = '\0';
	return s;
}

int strncmp(char s[], char t[], int n) {
	while(n > 0 && *s != '\0' && *t != '\0' && *s == *t) {
		n--;
		s++;
		t++;
	}
	if(n == 0)
		return 0;
	else
		return *s - *t;
}

int main() {
	int cmp;
	
	char s1[] = "helloworld";
	char t1[] = "hi   ";
	int n1 = 5;
	
	char s2[100] = "hi";
	char t2[] = "helloworld";
	int n2 = 15;
	
	char s3[100] = "hello";
	char t3[] = "world";
	int n3 = 3;
	
	char s31[100] = "hello";
	char t31[] = "world";
	int n31 = 5;
	
	char s4[] = "hello";
	char t4[] = "helva";
	int n4 = 3;
	int n41 = 4;

	strncpy(s1, t1, n1);
	printf("%s\n", s1);
	
	strncpy(s2, t2, n2);
	printf("%s\n", s2);
	
	strncat(s3, t3, n3);
	printf("%s\n", s3);
	
	strncat(s31, t31, n31);
	printf("%s\n", s31);
	
	cmp = strncmp(s4, t4, n4);
	printf("%d\n", cmp);
	
	cmp = strncmp(s4, t4, n41);
	printf("%d\n", cmp);
	return 0;
}
