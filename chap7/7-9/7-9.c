#include <stdio.h>
#include <sys/time.h>

// using for save time of isupper function
char asciiCodeArr[255];
void initAsciiCodeArr();
char isupperForSaveTime(char c);

// using for save space of isupper function
char isupperForSaveSpace(char c);

void initAsciiCodeArr() {
	int i = 0;
	for(; i < 255; i++)
		if(i >= 'A' && i <= 'Z')
			asciiCodeArr[i] = 1;
		else
			asciiCodeArr[i] = 0;
}

char isupperForSaveTime(char c) {
	return asciiCodeArr[c];
}

char isupperForSaveSpace(char c) {
	return c >= 'A' && c <= 'Z';
}

int main() {
	struct timeval start, end;
	unsigned long saveTimeTime, saveSpaceTime;
	char c;
	int i;

	// logic for save time of isupper function
	i = 0;
	initAsciiCodeArr();
	gettimeofday(&start, NULL);
	while(++i <= 1000000)
		for(c = 'A'; c <= 'Z'; c++)
			isupperForSaveTime(c);
	gettimeofday(&end, NULL);
	saveTimeTime = ((end.tv_sec * 1000000) + end.tv_usec) - ((start.tv_sec * 1000000) + start.tv_usec);
	
	// logic for save space of isupper function
	i = 0;
	gettimeofday(&start, NULL);
	while(++i <= 1000000)
		for(c = 'A'; c <= 'Z'; c++)
			isupperForSaveSpace(c);
	gettimeofday(&end, NULL);
	saveSpaceTime = ((end.tv_sec * 1000000) + end.tv_usec) - ((start.tv_sec * 1000000) + start.tv_usec);

	// print result
	printf("time of saveTime :%6lu\ntime of saveSpace:%6lu\n", saveTimeTime, saveSpaceTime);

	return 0;
}
