#include <stdio.h>
	int main() {
		int year = 1901;
		int month = 1;
		int day = 1;
		int february = 28;
		int sunday = 0;
		for(year = 1901; year < 2001; year++) {
				for(month=1;month<=12;month=month+1) {
					if(4 == month|| 7==month || 9==month ||11==month){
						day=day+30;
					}
					else if(2==month && ((year%100!=0 && year%4==0)|| year%400==0)){
							day=day+february+1;	
					}
					else if (2==month && (year%4!=0 || year%400!=0)) {
						day=day+february;
					}
					else {
						day=day+31;
					}
					if(day%7==0){
						sunday=sunday+1;
					}	
				}
		}
		printf("Sunday: %d \n", sunday);
		return 0;
	}
