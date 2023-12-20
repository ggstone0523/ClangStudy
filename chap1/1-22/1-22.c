#include<stdio.h>
#define MAXCHAR 100

int main()
{
	char c;
	char clist[MAXCHAR];
	int i, charlen, count;

	charlen = 0;
	while((c = getchar()) != EOF) {
	        ++count;
		clist[charlen] = c;
		++charlen;
	        if(c == ' ') {
			if(count > 25) {
				putchar('\n');
				count = 0;
			}
			for(i = 0; i < charlen; i++) {
				putchar(clist[i]);
			}
			charlen = 0;
		}		
	}
	if(charlen > 0) {
		if(count > 25) {
			putchar('\n');
		}
		for(i = 0; i < charlen; i++) {
			putchar(clist[i]);
		}
	}

	return 0;
}

