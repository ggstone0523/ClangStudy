#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[]) {
	int (*lettercasefunc)(int) = NULL;
	char c;
	
	if(strstr(argv[0], "lower") != NULL)
		lettercasefunc = tolower;
	else if(strstr(argv[0], "upper") != NULL)
		lettercasefunc = toupper;
	else {
		printf("This program must in folder named that include word \"lower\" or \"upper\"\n");
		return 0;
	}

	while((c = getchar()) != EOF)
		putchar(lettercasefunc(c));

	return 0;
}
