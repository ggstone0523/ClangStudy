#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 1000

int main(int argc, char *argv[]) {
	FILE *fp;
	char line[MAXLINE];
	long lineno = 0;
	int c, except = 0, number = 0, found = 0, filenum = 0, lineidx = 0, isstdin = 1, isfilenameprint = 0;
	char *pattern;

	while(--argc > 0 && (*++argv)[0] == '-')
	       while(c = *++argv[0])
		       	switch(c) {
		       	case 'x':
			       	except = 1;
			       	break;
		       	case 'n':
			       	number = 1;
			       	break;
			case 'f':
				if(*(argv[0] + 1) < '1' || *(argv[0] + 1) > '9') {
					printf("f option's x is must >= 1 and <= 9\n");
					return 0;
				}
				while((*++argv[0] >= '1' && *argv[0] <= '9') && (lineidx < MAXLINE))
					line[lineidx++] = *argv[0];
				line[lineidx] = '\0';
				filenum = atoi(line);
				--argv[0];
				isstdin = 0;
				break;
		       	default:
			       	printf("find: illegal option %c\n", c);
			       	argc = 0;
			       	found = -1;
			       	break;
		       	}

	if(argc < 1)
		printf("Usage: find -x -n -fx(x >= 1) pattern\n");
	else {
		printf("FIND PATTERN PROGRAM\n");
		pattern = strdup(*argv);
		while(--filenum >= 0 || isstdin) {
			lineno = 0;
			found = 0;
			isfilenameprint = 0;
			
			if(isstdin) {
				fp = stdin;
				isstdin = 0;
			} else
				if((fp = fopen(*++argv, "r")) == NULL) {
					printf("FILE OPEN ERROR!\n");
					return 0;
				}

			while(fgets(line, MAXLINE, fp) != NULL) {
				lineno++;
				if((strstr(line, pattern) != NULL) != except) {
					if(!isfilenameprint) {
						if(fp == stdin)
							printf("\ninput: stdin\n");
						else
							printf("\nfile name: %s\n", *argv);
						isfilenameprint = 1;
					}
					if(number)
						printf("%ld:", lineno);
					printf("%s", line);
					found++;
				}
			}
			
			if(found > 0) {
				printf("found line number: %d\n", found);
			}
			if(fp != stdin)
				fclose(fp);
		}
	}

	return 0;
}
