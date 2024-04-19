#include <stdio.h>

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

// 5-8 homework answer: add error check logic to day_of_year and month_day function;
int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int day_of_year(int year, int month, int day) {
	int i, leap;

	if(year < 1) {
		printf("year must be 1 or more!\n");
		return -1;
	} else if((month < 1) || (month > 12)) {
		printf("month must be between 1 and 12!\n");
		return -1;
	}

	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

	if((day > daytab[leap][month]) || (day < 1)) {
		printf("day must be between 1 and %d\n", daytab[leap][month]);
		return -1;
	}

	for(i = 1; i < month; i++)
		day += daytab[leap][i];
	return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
	int i, leap;

	if(year < 1) {
		printf("year must be 1 or more!\n");
		return;
	}

	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

	if((leap == 0) && ((yearday < 1) || (yearday > 365))) {
		printf("yearday must be between 1 and 365\n");
		return;
	} else if((leap == 1) && ((yearday < 1) || (yearday > 366))) {
		printf("yearday must be between 1 and 366\n");
		return;
	}
	
	for(i = 1; yearday > daytab[leap][i]; i++) {
		yearday = yearday - daytab[leap][i];
	}
	*pmonth = i;
	*pday = yearday;
}

int main() {
	int month;
	int day;
	int yearday;

	yearday = day_of_year(1988, 2, 29);
	month_day(1988, yearday, &month, &day);
	printf("yearday is %d, month is %d, day is %d\n", yearday, month, day);

	yearday = day_of_year(0, 2, 29);
	
	yearday = day_of_year(1988, 13, 29);
	
	yearday = day_of_year(1988, 2, 40);
	
	month_day(0, 60, &month, &day);
	
	month_day(1988, 367, &month, &day);
	
	month_day(2023, 366, &month, &day);
	
	return 0;
}
