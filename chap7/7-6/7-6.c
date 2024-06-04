#include <stdio.h>

#define STRMAXLEN 1024

int isequal(char str1[], char str2[]);
void clearnextline(char str[]);

int isequal(char str1[], char str2[]) {
	int str1idx = 0;
	int str2idx = 0;

	while(str1[str1idx] != '\0' || str2[str2idx] != '\0') {
		if(str1[str1idx] != str2[str2idx])
			return 0;
		str1idx++;
		str2idx++;
	}
	
	return 1;
}

void clearnextline(char str[]) {
	int stridx = 0;
	
	while(str[stridx] != '\0') {
		if(str[stridx] == '\n') {
			str[stridx] = '\0';
			break;
		}
		stridx++;	
	}
}

int main(int argc, char *argv[]) {
	FILE *fp1;
	FILE *fp2;
	char str1[STRMAXLEN];
	char str2[STRMAXLEN];
	char *retfp1, *retfp2;
	int idx1 = 0, idx2 = 0;

	fp1 = fopen(argv[1], "r");
	fp2 = fopen(argv[2], "r");

	idx1++;
	idx2++;
	retfp1 = fgets(str1, STRMAXLEN, fp1);
	retfp2 = fgets(str2, STRMAXLEN, fp2);
	while((retfp1 != NULL) && (retfp2 != NULL)) {
		if(!isequal(str1, str2)) {
			clearnextline(str1);
			clearnextline(str2);
			printf("\"%s\" in \"%s\" and \"%s\" in \"%s\" is different!\n", str1, argv[1], str2, argv[2]);
			fclose(fp1);
			fclose(fp2);
			return 0;
		}
		idx1++;
		idx2++;
		retfp1 = fgets(str1, STRMAXLEN, fp1);
		retfp2 = fgets(str2, STRMAXLEN, fp2);
	}


	fclose(fp1);
	fclose(fp2);
	if(retfp1 != NULL && retfp2 == NULL) {
		clearnextline(str1);
		printf("No string in \"%s\" on the same line as \"%s\" in \"%s\" at line %d\n", argv[2], str1, argv[1], idx1);
	} else if(retfp1 == NULL && retfp2 != NULL) {
		clearnextline(str2);
		printf("No string in \"%s\" on the same line as \"%s\" in \"%s\" at line %d\n", argv[1], str2, argv[2], idx2);
	} else
		printf("\"%s\" and \"%s\" file is equal!\n", argv[1], argv[2]);
	return 0;
}
