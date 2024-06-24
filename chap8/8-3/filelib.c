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
	int flag;
	int fd;
} FILET;

FILET _iob[OPEN_MAX];

enum _flags {
	_READ = 01,
	_WRITE = 02,
	_UNBUF = 04,
	_EOF = 010,
	_ERR = 020
};

FILET *fopent(char *name, char *mode);
int _fillbuft(FILET *fp);
void _flushbuft(char c, FILET *fp);
void fflusht(FILET *fp);
void fcloset(FILET *fp);

#define getc(p) (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuft(p))
#define putc(x,p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuft((x),p))

FILET *fopent(char *name, char *mode) {
	int fd;
	FILET *fp;

	if(*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
	for(fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if((fp->flag & (_READ | _WRITE)) == 0)
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
	fp->flag = (*mode == 'r') ? _READ : _WRITE;
	return fp;
}

int _fillbuft(FILET *fp) {
	int bufsize;

	if((fp->flag&(_READ|_EOF|_ERR)) != _READ)
		return EOF;
	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZE;
	if(fp->base == NULL)
		if((fp->base = (char *)malloc(bufsize)) == NULL)
			return EOF;
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	if(--fp->cnt < 0) {
		if(fp->cnt == -1)
			fp->flag |= _EOF;
		else
			fp->flag |= _ERR;
		fp->cnt = 0;
		return EOF;
	}

	return (unsigned char)*fp->ptr++;
}

void _flushbuft(char c, FILET *fp) {
	if((fp->flag&(_WRITE|_EOF|_ERR)) != _WRITE)
		exit(0);
	if(fp->flag & _UNBUF == _UNBUF)
		write(fp->fd, &c, 1);
	else {
		if(fp->base == NULL) {
			fp->base = (char *)malloc(BUFSIZE);
			fp->ptr = fp->base;
			fp->cnt = BUFSIZE;
			if(fp->base == NULL) {
				fp->flag |= _ERR;
				fp->cnt = 0;
			} else {
				write(fp->fd, &c, 1);
			}
		} else {
			write(fp->fd, fp->base, BUFSIZE - (fp->cnt + 1));
			write(fp->fd, &c, 1);
			fp->ptr = fp->base;
			fp->cnt = BUFSIZE;
		}
	}

}

void fflusht(FILET *fp) {
	if((fp->flag&(_WRITE|_EOF|_ERR)) != _WRITE)
		exit(0);
	if(fp->base == NULL) {
		fp->base = (char *)malloc(BUFSIZE);
		fp->ptr = fp->base;
		fp->cnt = BUFSIZE;
		if(fp->base == NULL) {
			fp->flag |= _ERR;
			fp->cnt = 0;
		}
	} else {
		write(fp->fd, fp->base, BUFSIZE - fp->cnt);
		fp->ptr = fp->base;
		fp->cnt = BUFSIZE;
	}
}

void fcloset(FILET *fp) {
	if(fp->base != NULL)
		free(fp->base);
	close(fp->fd);
}

int main() {
	FILET *fp1, *fp2;
	char c;
	int i = 0;

	fp1 = fopent("readfile", "r");
	fp2 = fopent("writefile", "w");
	
	for(i = 0; i < 2048; i++) {
		c = getc(fp1);
		putc(c, fp2);
	}
	fflusht(fp2);

	fcloset(fp1);
	fcloset(fp2);

	return 0;
}
