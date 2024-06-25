#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <pwd.h>

#define DIRSIZ 14
#define NAME_MAXX 14
#define MAX_PATH 1024

struct directx {
	ino_t d_ino;                   
	char d_name[DIRSIZ];              
};

typedef struct {
	long ino;
	char name[NAME_MAXX+1];
} Direntx;

typedef struct {
	int fd;
	Direntx d;
} DIRx;

DIRx *opendirx(char *dirname);
Direntx *readdirx(DIRx *dfd);
void closedirx(DIRx *dfd);
void dirwalk(char *, void (*fcn)(char *));
void fsize(char *);

DIRx *opendirx(char *dirname) {
	int fd;
	struct stat stbuf;
	DIRx *dp;

	if((fd = open(dirname, O_RDONLY, 0)) == -1 || fstat(fd, &stbuf) == -1 || (stbuf.st_mode & S_IFMT) != S_IFDIR || (dp = (DIRx *)malloc(sizeof(DIRx))) == NULL)
		return NULL;
	dp->fd = fd;
	return dp;
}

void closedirx(DIRx *dp) {
	if(dp) {
		close(dp->fd);
		free(dp);
	}
}

Direntx *readdirx(DIRx *dp) {
	struct directx dirbuf;
	static Direntx d;

	while(read(dp->fd, (char *)&dirbuf, sizeof(dirbuf)) == sizeof(dirbuf)) {
		if(dirbuf.d_ino == 0)
			continue;
		d.ino = dirbuf.d_ino;
		strncpy(d.name, dirbuf.d_name, DIRSIZ);
		d.name[DIRSIZ] = '\0';
		return &d;
	}

	return NULL;
}


void fsize(char *name) {
	struct stat stbuf;
    	struct passwd *pws;

	if(stat(name, &stbuf) == -1) {
		fprintf(stderr, "fsize: can't access %s\n", name);
		return;
	}
	if((stbuf.st_mode & S_IFMT) == S_IFDIR)
		dirwalk(name, fsize);
	pws = getpwuid(stbuf.st_uid);
	printf("%81s %5ld %s\n", pws->pw_name, stbuf.st_size, name);
}

void dirwalk(char *dir, void (*fcn)(char *)) {
	char name[MAX_PATH];
	struct dirent *dp;
	DIR *dfd;

	if((dfd = opendir(dir)) == NULL) {
		fprintf(stderr, "dirwalk: can't open %s\n", dir);
		return;
	}
	while((dp = readdir(dfd)) != NULL) {
		if((strcmp(dp->d_name, "..") == 0) || (strcmp(dp->d_name, ".") == 0))
			continue;
		if(strlen(dir) + strlen(dp->d_name)+2 > sizeof(name))
			fprintf(stderr, "dirwalk: name %s/%s too long\n", dir, dp->d_name);
		else {
			sprintf(name, "%s/%s", dir, dp->d_name);
			(*fcn)(name);
		}
	}
	closedir(dfd);
}

int main(int argc, char **argv) {
	if(argc == 1)
		fsize(".");
	else
		while(--argc > 0)
			fsize(*++argv);
	return 0;
}
