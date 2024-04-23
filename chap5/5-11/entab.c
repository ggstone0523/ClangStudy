#include <stdio.h>
#include <ctype.h>

int N;

char __entab(void);
int atoi(char* i);

char __entab(void) {
	char c;
	int count, spaceCount, i, j;

	count = 0;
	spaceCount = 0;
	while((c = getchar()) != '\n' && c != EOF){
		if(count == N){
			if(spaceCount > 0) {
				putchar('\t');
			}
			count = 0;
			spaceCount = 0;
		}
		
		if(c ==' ') {
		        ++spaceCount;
		} else {
			for(i = 0; i < spaceCount; i++){
				putchar(' ');
			}
			putchar(c);
			spaceCount = 0;
		}

		++count;
	}
	if(c == '\n')
		putchar(c);

	return c;
}

int atoi(char* i) {
	int val = 0;

	while(isdigit(*i)) {
		val = val * 10 + (*i - '0');
		i++;
	}

	return val;
}

int main(int argc, char *argv[]) {
        N = 8;

        do {
                if(--argc > 0) {
                        N = atoi(*++argv);
		}

        } while(__entab() != EOF);

        return 0;
}
