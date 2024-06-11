#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void filecopy(FILE *, FILE *);

void filecopy(FILE *ifp, FILE *ofp) {
	char c;
	
	while((c = getc(ifp)) != EOF)
		putc(c, ofp);
}

int main(int argc, char *argv[]) {
	FILE *fp;
	char *prog = argv[0];
	struct timeval start, end;

	gettimeofday(&start, NULL);
	if(argc == 1)
		filecopy(stdin, stdout);
	else
		while(--argc > 0)
			if((fp = fopen(*++argv, "r")) == NULL) {
				fprintf(stderr, "%s: can't open %s\n", prog, *argv);
				exit(1);
			} else {
				filecopy(fp, stdout);
				fclose(fp);
			}
	if(ferror(stdout)) {
		fprintf(stderr, "%s: error writing stdout\n", prog);
		exit(2);
	}
	gettimeofday(&end, NULL);

	printf("libcat execution time: %ld\n", ((end.tv_sec * 1000000) + end.tv_usec) - ((start.tv_sec * 1000000) + start.tv_usec));

	return 0;
}
