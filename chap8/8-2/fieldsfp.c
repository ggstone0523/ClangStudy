#include <fcntl.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define PERMS 0666
#define OPEN_MAX 20
#define BUFSIZE 1024

typedef struct _iobuf {
	int cnt;
	char *ptr;
	char *base;
	int read;
	int write;
	int unbuf;
	int eof;
	int err;
	int fd;
} FILET;

FILET _iob[OPEN_MAX];

FILET *fopent(char *name, char *mode);
int _fillbufT(FILET *);

FILET *fopent(char *name, char *mode) {
	int fd;
	FILET *fp;

	if(*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
	for(fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if((fp->read == 0) && (fp->write == 0))
			break;
	if(fp >= _iob + OPEN_MAX)
		return NULL;

	if(*mode == 'w')
		fd = creat(name, PERMS);
	else if(*mode == 'a') {
		if((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	} else 
		fd = open(name, O_RDONLY, 0);
	if(fd == -1)
		return NULL;
	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	if(*mode == 'r')
		fp->read = 1;
	else
		fp->write = 1;
	return fp;
}

int _fillbuft(FILET *fp) {
	int bufsize;

	if((fp->read != 1) || ((fp->read == 1) && ((fp->eof == 1) || (fp->err == 1))))
		return EOF;
	if(fp->unbuf == 1)
		bufsize = 1;
	else
		bufsize = BUFSIZE;
	if(fp->base == NULL)
		if((fp->base = (char *)malloc(bufsize)) == NULL)
			return EOF;
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	if(--fp->cnt < 0) {
		if(fp->cnt == -1)
			fp->eof = 1;
		else
			fp->err = 1;
		fp->cnt = 0;
		return EOF;
	}

	return (unsigned char)*fp->ptr++;
}

int main() {
	FILET *fp;
	struct timeval start, end;

	gettimeofday(&start, NULL);
	
	fp = fopent("testfile", "r");
	_fillbuft(fp);
	
	gettimeofday(&end, NULL);
	printf("fieldsfp execution time: %ld\n", ((end.tv_sec * 1000000) + end.tv_usec) - ((start.tv_sec * 1000000) + start.tv_usec));
	printf("%s\n", fp->base);

	return 0;
}
