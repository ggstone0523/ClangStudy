#include <stdio.h>

#define MAXLEN 1024

int main(int argc, char *argv[]) {
	FILE *fp;
	int idx = 0;
	char str[MAXLEN];

	if(argc < 2) {
		printf("Usage: ./a.out file1 ...\n");
		return 0;
	}

	while(++idx < argc) {
		if((fp = fopen(argv[idx], "r")) == NULL) {
			printf("file open error!\n");
			return 0;
		}
		printf("NAME: %s\n\n", argv[idx]);
		while(fgets(str, MAXLEN, fp) != NULL)
			printf("%s\n", str);
		printf("PAGE: %d\n", idx);
		if(idx+1 < argc)
			printf("\n\n");
		fclose(fp);
	}

	return 0;
}
