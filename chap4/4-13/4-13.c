#include <stdio.h>

void reverse(char s[]);

void reverse(char s[]) {
	static int left = 0;
	static int right  = 0;
	char temp = ' ';

	if(s[right] != '\0') {
		right++;
		reverse(s);
	}
	right--;

	if(left < right) {
		temp = s[left];
		s[left] = s[right];
		s[right] = temp;
		left++;
	} else {
		left = 0;
		right = 0;
	}
}

int main() {
	char odds[] = "hello";
	char evens[] = "static";

	reverse(odds);
	printf("reverse of hello: %s\n", odds);
	
	reverse(evens);
	printf("reverse of static: %s\n", evens);
	return 0;
}
