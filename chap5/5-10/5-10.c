#include <stdio.h>
#include <ctype.h>
#define STKMAX 1024
#define ELSE 'E'
#define NUMBER 'N'

double stack[STKMAX];
int stkidx = 0;

void push(double val);
double pop();
double atof(char *f);
int ops(char *op);

void push(double val) {
	stack[stkidx] = val;
	stkidx++;
}

double pop() {
	stkidx--;
	return stack[stkidx];
}

int isstkempty() {
	return (stkidx == 0) ? 1 : 0;
}

double atof(char *f) {
	double val = 0.0;
	double dotval = 0.0;
	int dotnum = 1;
	int sign = 1;

	if(*f == '-') {
		sign = -1;
		f++;
	} else if(*f == '+') {
		f++;
	}

	while(isdigit(*f)) {
		val = val * 10 + (*f - '0');
		f++;
	}
	if(*f == '.') {
		f++;
	}
	while(isdigit(*f)) {
		dotval = dotval * 10 + (*f - '0');
		dotnum *= 10;
		f++;
	}
	dotval /= dotnum;
	return sign * (val + dotval);
}

int ops(char *op) {
	if(*(op+1) == '\0' && (*op == '-' || *op == '+' || *op == '*' || *op == '/'))
		return *op;
	
	if(!(isdigit(*op) || *op == '-' || *op == '+' || *op == '.'))
		return ELSE;
	op++;
	while(*op != '\0') {
		if(!(isdigit(*op) || *op == '.'))
			return ELSE;
		op++;
	}
	return NUMBER;

}

int main(int argc, char *argv[]) {
	int idx = 1;
	double op2;

	if(argc < 4) {
		printf("Usage: ./expr 1 2 +\n");
		return 0;
	}

	while(idx < argc) {
		switch(ops(argv[idx])) {
			case '+':
				push(pop() + pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '*':
				push(pop() * pop());
				break;
			case '/':
				op2 = pop();
				if(op2 == 0.0)
					printf("div error!\n");
				else
					push(pop() / op2);
				break;
			case NUMBER:
				push(atof(argv[idx]));
				break;
			default:
				printf("error!\n");
				break;
		}
		idx++;
	}
	
	op2 = pop();
	if(isstkempty())
		printf("answer: %f\n", op2);
	else
		printf("calculation error!\n");
	return 0;
}
