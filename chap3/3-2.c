#include <stdio.h>

void escape(char s[], char t[]);
void escapeSeqHandle(char s[], char es, int *sCount);

void escapeSeqHandle(char s[], char es, int *sCount){
	s[*sCount] = '\\';
	(*sCount)++;
	s[*sCount] = es;
	
}

void escape(char s[], char t[]) {
	int sCount = 0;
	int tCount = 0;

	while(t[tCount] != '\0') {
		switch(t[tCount]) {
			case '\a':
				escapeSeqHandle(s, 'a', &sCount);
		 		break;		
			case '\b':
				escapeSeqHandle(s, 'b', &sCount);
		 		break;	
			case '\f':
				escapeSeqHandle(s, 'f', &sCount);
		 		break;	
			case '\n':
				escapeSeqHandle(s, 'n', &sCount);
		 		break;	
			case '\r':
				escapeSeqHandle(s, 'r', &sCount);
		 		break;	
			case '\t':
				escapeSeqHandle(s, 't', &sCount);
		 		break;	
			case '\v':
				escapeSeqHandle(s, 'v', &sCount);
		 		break;	
			case '\\':
				escapeSeqHandle(s, '\\', &sCount);
		 		break;	
			case '\'':
				escapeSeqHandle(s, '\'', &sCount);
		 		break;	
			case '\"':
				escapeSeqHandle(s, '\"', &sCount);
		 		break;	
			case '\?':
				escapeSeqHandle(s, '\?', &sCount);
		 		break;	
			default:
				s[sCount] = t[tCount];
				break;	
		}
		tCount++;
		sCount++;
	}
	s[sCount] = '\0';
}

int main() {
	char t[] = "hello	my	name\nis\a choi\f yusun,\bhihi.\vwhat's your hobby? \\ \" \r\n";
	char s[1024];
	
	escape(s, t);
	printf("%s\n", s);
}
