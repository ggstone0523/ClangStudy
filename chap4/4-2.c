#include <ctype.h>
#include <stdio.h>

double atof(char s[]);

double atof(char s[]) {
	double val, power, valueE;
	int i, j, sign, signE, E;

	for(i = 0; isspace(s[i]); i++);
	sign = (s[i] == '-') ? -1 : 1;

	if(s[i] == '+' || s[i] == '-')
		i++;
	for(val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if(s[i] == '.')
		i++;
	for(power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}
	val /= power;

	if(s[i] == 'e')
		i++;
	signE = (s[i] == '-') ? -1 : 1;
	if(s[i] == '+' || s[i] == '-')
		i++;
	for(E = 0; isdigit(s[i]); i++)
		E = E * 10 + (s[i] - '0');
	for(j = 0, valueE = 1; j < E; j++)
		valueE *= 10.0;
	if(signE == -1) {
		valueE = 1 / valueE;
	}
	return sign * val * valueE;
}


int main() {
	char line1[] = "123.45";
	char line2[] = "123.45e-6";

	printf("%11s: %11g\n", line1, atof(line1));
	printf("%11s: %11g\n", line2, atof(line2));
	return 0;
}
