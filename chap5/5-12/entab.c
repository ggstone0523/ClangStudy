#include <stdio.h>
#include <ctype.h>

int N;
int M;

char __entab(void);
int atoi(char* i);

char __entab(void) {
	char c;
	char prevc = ' ';
	int count, spaceCount, i, j, allCount;

	count = 0;
	spaceCount = 0;
	allCount = 0;
	while((c = getchar()) != '\n' && c != EOF){
		if(prevc != c && prevc == ' ')
			allCount++;

		if(count == N){
			if(spaceCount > 0 && M <= allCount) {
				putchar('\t');
			} 
			count = 0;
			spaceCount = 0;
		}
		
		if(c ==' ') {
		        ++spaceCount;
			if(M > allCount) {
				putchar(' ');
				--spaceCount;
			}
		} else {
			for(i = 0; i < spaceCount; i++){
				putchar(' ');
			}
			putchar(c);
			spaceCount = 0;
		}

		++count;
		prevc = c;
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
	M = 0;

	if(argc > 3) {
		printf("Usage: entab -3 +8\n");
		return 0;
	}
	while(--argc > 0) {
		switch(*(*++argv)) {
			case '-':
				M = atoi((*argv)+1);
				break;
			case '+':
				N = atoi((*argv)+1);
				break;
			default:
				printf("error!\n");
				return 0;
				break;
		}
	}

        while(__entab() != EOF);

        return 0;
}
