#include <stdio.h>

float fahrToCelsius(float fahr);

/* print Fahrenheit-Celsius table
 * for fahr = 1, 20, ..., 300; floating-point version */

int main()
{
	float fahr, celsius;
	int lower, upper, step;

	lower = 0; /* lower limit of temperature table */
	upper = 300; /* upper limit */
	step = 20; /* step size */

	fahr = lower;
	while(fahr <= upper){
		celsius = fahrToCelsius(fahr);
		printf("%3.0f %6.1f\n", fahr, celsius);
		fahr = fahr + step;
	}

	return 0;
}

/* Get Celsius using Fahr  */
float fahrToCelsius(float fahr)
{
	return (5.0/9.0) * (fahr - 32.0);
}
