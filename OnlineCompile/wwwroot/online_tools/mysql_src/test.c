#include "common.h"


int main( )
{ 
	char buf[1024]= {0};
	if(GetQueryString( buf) < 0){ 
		perror( "getQueryString");
		return 1;
	}
	printf( "buf =%s\n", buf);
	return 0;
}
