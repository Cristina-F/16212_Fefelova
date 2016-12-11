#include <stdio.h>

#define FEBRUARY 28
#define START_YEAR 1901
#define END_YEAR 2001

int main() {
	int year = 1901;
	int month = 1;
	int day = 1;
	int sunday = 0;
	for (year = START_YEAR; year < END_YEAR; year = year + 1) {
		for (month = 1; month <= 12; month = month + 1) {
			if (4 == month || 7 == month || 9 == month || 11 == month) {
				day = day + 30;
			}
			else if (2 == month && ((0 != year%100 && 0 == year%4) || 0 == year%400)) {
				day = day + FEBRUARY + 1;	
			}
			else if (2 == month && (0 != year%4 || 0 != year%400)) {
				day = day + FEBRUARY;
			}
			else {
				day = day + 31;
			}
			if (0 == day%7) {
				sunday = sunday + 1;
			}	
		}
	}
	printf ("Sunday: %d \n", sunday);
	return 0;
}
