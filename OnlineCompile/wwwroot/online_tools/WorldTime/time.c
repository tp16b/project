#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main( )
{ 
	time_t t = time( NULL);
	int time_diff = 1;
	t += time_diff*3600;
	struct tm* tp =localtime(&t);

	printf("<html><h2>%02d: %02d</h2></html>" ,tp->tm_hour, tp->tm_min);
	return 0;
}

//struct tm { 
//	int tm_sec;         /* seconds */
//	int tm_min;         /* minutes */
//	int tm_hour;        /* hours */
//	int tm_mday;        /* day of the month */
//	int tm_mon;         /* month */
//	int tm_year;        /* year */
//	int tm_wday;        /* day of the week */
//	int tm_yday;        /* day in the year */
//	int tm_isdst;       /* daylight saving time */
//} ;

