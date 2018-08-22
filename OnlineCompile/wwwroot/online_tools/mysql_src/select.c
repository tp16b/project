#include "common.h"
#include <mysql/mysql.h>

int main( )
{ 
	char buf[1024] = {0};	
	int r= GetQueryString(buf);
	if( r < 0)	 { perror("GetQueryString"); return 1;}
	//1. 连接
	MYSQL* fp = mysql_init(NULL);   

//	printf( "%s\n", mysql_get_client_info( ));
	MYSQL* connect_fp = mysql_real_connect( fp, "127.0.0.1"
			, "root", "", "test", 3306, NULL, 0);
	if(connect_fp == NULL){ 
		perror("mysql_real_connect faild");
		mysql_close(fp);
		return 1;
	}	
	//2.构建sql语句
	char sql[1024]= { 0};
	char name[64] = { 0};
	int id = -1;
	sscanf(buf ,"id=%d&name=%s", &id, name);
	sprintf(sql, "SELECT * FROM stu WHERE id=%d and name='%s'", id, name) ;
	
	//3.查询
	int ret = mysql_query(connect_fp, sql);
	if( ret < 0){ 
		printf( "<html><h2>查询失败了...</h2></html>");
		mysql_close(fp);
		return 1;
	}
	MYSQL_RES* result = mysql_store_result( connect_fp);
	//4. 得到查询结果。获取行数， 列数
	int rows = mysql_num_rows(result);
	int cols = mysql_num_fields(result);

	//5. 获取列名，  结果内容   
	MYSQL_FIELD* field = mysql_fetch_fields(result);
	if( field == NULL){ 
		perror("mysql_fetch_fields");
		return 1;
	}
	printf("<html>");
	for( int i = 0; i< cols; ++i )
		printf("%s\t", field[i].name);
	printf( "<br>");
	for(int i = 0; i< rows; ++i){ 
		MYSQL_ROW row = mysql_fetch_row(result);
		for( int j =0; j < cols; ++j){ 
			printf("%s\t", row[ j]);
		}
		printf( "<br>");
	}
	printf( "<br>");
	printf( "</html>");
	free(result);
	mysql_close( fp);

	return 0;
}
