#include <stdio.h>

#define STACKSIZE 1024
#define WORDSIZE 1024

int stack[STACKSIZE];
int stackidx = 0;

void push(int i);
int pop();
int top();
int strsize(char s[]);

void push(int i) {
	if(stackidx == STACKSIZE) {
		printf("size is over!\n");
		return;
	}
	stack[stackidx] = i;
	stackidx++;
}

int pop() {
	if(stackidx == 0) {
		printf("stack is empty!\n");
		return -1;
	}
	stackidx--;
	return stack[stackidx];
}

int top() {
	if(stackidx == 0) {
		printf("stack is empty!\n");
		return -1;
	}
	return stack[stackidx-1];
}

int main() {
	double farg, sarg;
	char s[WORDSIZE];
	char c;

	while(scanf("%s", s) == 1) {
		switch(*s) {
		case '+':
			sarg = pop();
			farg = pop();
			push(farg + sarg);
			break;
		case '-':
			if(*(s+1) >= '0' && *(s+1) <= '9') {
				sscanf(s, "%lf", &farg);
				push(farg);
			} else {
				sarg = pop();
				farg = pop();
				push(farg - sarg);
			}
			break;
		case '*':
			sarg = pop();
			farg = pop();
			push(farg * sarg);
			break;
		case '/':
			sarg = pop();
			farg = pop();
			push(farg / sarg);
			break;
		default:
			if(*s >= '0' && *s <= '9') {
				sscanf(s, "%lf", &farg);
				push(farg);
			}
			break;
		}
		
		c = getchar();
		if(c == '\n') {
			if(stackidx == 1)
				printf("Answer: %d\n", pop());
			else
				printf("Input postfix expression is error!\n");
			stackidx = 0;
		}
	}

	return 0;
}
