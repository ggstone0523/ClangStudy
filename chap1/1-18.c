#include <stdio.h>
#define MAXLINE 1000 /* maximum input line size */

int getLine(char line[], int maxline);
int rmSpaceLine(char line[], int len);

/* print all input line that remove line's backpart space or tab and except null line */
int main()
{
	int len; /* current line length */
	char line[MAXLINE]; /* current input line */
	while((len = getLine(line,MAXLINE)) > 0){
		len= rmSpaceLine(line, len);
		if(len > 0)
			printf("%s", line);
	}
	return 0;
}


/* getline: read a line into s, return length */
int getLine(char s[], int lim)
{
	int c, i;

	for(i=0; i<lim-1 && (c=getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if(c == '\n'){
		s[i] = c;
		++i;
	}

	s[i] = '\0';
	return i;
}


/* rmSpaceLine: remove line's backpart space or tab, return length */
int rmSpaceLine(char line[], int len)
{
	--len;
	while(len > 0){
		--len;
		if(line[len] != ' ' && line[len] != '\t')
			break;
	}
	
	if(len == 0)
		return 0;

	line[len+1] = '\n';
	line[len+2] = '\0';

	return len+2;
}
