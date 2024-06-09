#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <stdio.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

int isoccurerror = 0;

void filecopy(int fd1, int fd2);

void filecopy(int fd1, int fd2) {
	char c;
	
	while(read(fd1, &c, 1) > 0)
		if(write(fd2, &c, 1) != 1)
			isoccurerror = 1;
}

int main(int argc, char *argv[]) {
	int fd;
	char *prog = argv[0];
	char str[1024];
	struct timeval start, end;

	gettimeofday(&start, NULL);
	if(argc == 1)
		filecopy(STDIN, STDOUT);
	else
		while(--argc > 0)
			if((fd = open(*++argv, O_RDONLY, 0)) == -1) {
				strcat(str, prog);
				strcat(str, ": can't open ");
				strcat(str, *argv);
				strcat(str, "\n");
				write(STDERR, str, strlen(str));
				exit(1);
			} else {
				filecopy(fd, STDOUT);
				close(fd);
			}
	if(isoccurerror) {
		strcat(str, prog);
		strcat(str, ": error writing stdout\n ");
		write(STDERR, str, strlen(str));
		exit(2);
	}
	gettimeofday(&end, NULL);

	printf("nolibcat execution time: %ld\n", ((end.tv_sec * 1000000) + end.tv_usec) - ((start.tv_sec * 1000000) + start.tv_usec));

	return 0;
}
