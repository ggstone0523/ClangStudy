#include <stdio.h>

/* print Celsius-fahrenheit table
 * for celsius = 0, 10, ... , 100 */

int main()
{
	float fahr, celsius;
	int lower, upper, step;

	lower = 0; /* lower limit of temperature table */
	upper = 100; /* upper limit */
	step = 10; /* step size */

	celsius = lower;
	while (celsius <= upper) {
		fahr = (celsius * (9.0/5.0)) + 32.0;
		printf("%3.0f\t%6.1f\n", celsius, fahr);
		celsius = celsius + step;
	}

	return 0;
}
