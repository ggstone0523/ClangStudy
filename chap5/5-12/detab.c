#include <stdio.h>
#include <ctype.h>

int N;
int M;

char __detab(void);
int atoi(char* i);

char __detab(void) {
	char c;
	char prevc = ' ';
	int count, i, k, idx, allCount;

	count = 0;
	allCount = 0;
	while((c = getchar()) != '\n' && c != EOF){
		if((prevc != c) && (prevc == ' ' || prevc == '\t')) {
			allCount++;
		}

		if(c == '\t'){
			if(M <= allCount) {
				k = count % N;
				for(i=0; i < N - k; ++i){
					putchar(' ');
				}
			} else {
				putchar('\t');
			}
			count = 0;
		} else {
			putchar(c);
			++count;
		}

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

        while(__detab() != EOF);

	return 0;
}
