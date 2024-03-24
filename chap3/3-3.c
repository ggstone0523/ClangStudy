#include <stdio.h>

int expand(char s1[], char s2[]);

int expand(char s1[], char s2[]) {
	int startIdx;
	int lastIdx;
	int s1Index = 0;
	int sTol = 0;
	int s2Index = 0;

	while(s1[s1Index] == '-' && s1[s1Index] != '\0') {
		s2[s2Index] = s1[s1Index];
		s2Index++;
		s1Index++;
	}
	startIdx = s1Index;
	s2[s2Index] = s1[startIdx];
	s2Index++;
	s1Index++;

	for(;s1[s1Index] != '\0';) {
		while(s1[s1Index] == '-' && s1[s1Index] != '\0') {
			s1Index++;
		}
		if(s1[s1Index] == '\0')
			break;
		lastIdx = s1Index;
		s1Index++;
		
		if(startIdx != (lastIdx-1)) {
			for(sTol = (s1[startIdx]+1); sTol <= s1[lastIdx]; sTol++, s2Index++) {
				s2[s2Index] = sTol;
			}
		} else {
			s2[s2Index] = s1[lastIdx];
			s2Index++;
		}
		startIdx = lastIdx;
	}

	s1Index--;
	while(s1[s1Index] == '-') {
		s2[s2Index] = s1[s1Index];
		s2Index++;
		s1Index--;
	}
	s2[s2Index] = '\0';
	return 0;
}

int main() {
	char* s1 = "a-b-c";
	char* s2 = "a-z0-9";
	char* s3 = "-a-z";
	char* s4 = "a-bc";
	char* s5 = "-a-z0-";
	char buf[1024];

	expand(s1, buf);
	printf("%s to %s\n", s1, buf);
	
	expand(s2, buf);
	printf("%s to %s\n", s2, buf);
	
	expand(s3, buf);
	printf("%s to %s\n", s3, buf);
	
	expand(s4, buf);
	printf("%s to %s\n", s4, buf);
	
	expand(s5, buf);
	printf("%s to %s\n", s5, buf);
	return 0;
}
