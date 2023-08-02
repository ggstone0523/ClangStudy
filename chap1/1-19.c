#include <stdio.h>
#define MAXLINE 1000 /* maximum input line size */

int getLine(char line[], int maxline);
void reverse(char line[], int len);

/* print all input line that reversed */
int main()
{
	int len; /* current line length */
	char line[MAXLINE]; /* current input line */
	while((len = getLine(line,MAXLINE)) > 0){
		reverse(line, len);
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


/* reverse: reverses the character sting line  */
void reverse(char line[], int len)
{
	int i;
	char copy[len+1];

	if(line[len-1] == '\n'){
		for(i = 0; i < len-1; i++){
			copy[len-2-i] = line[i];
		}
		for(i = 0; i < len-1; i++){
			line[i] = copy[i];
		}
	} else {
		for(i = 0; i < len; i++){
			copy[len-1-i] = line[i];
		}
		for(i = 0; i < len; i++){
			line[i] = copy[i];
		}
	}
}
