#pragma once 

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <cassert>
#include <cstdio>
#include <unistd.h>

#include <list>
#include <set>
#include <map>
#include <mysql/mysql.h>
#define SUCCESS 0
#define ADMIN_PASS "123"

using namespace std;

//static int flag;
inline void clrscr() {system("clear");}

inline void title(){
	cout<<"==============================================================================="<<endl;
	cout<<"***************************** 学信通学籍管理系统 ******************************"<<endl;
	cout<<"==============================================================================="<<endl;
}


static void GetDate(char *tday){
	time_t tim;
	tim=time(NULL);
	struct tm *d = localtime(&tim);
	sprintf(tday,"%d/%02d/%02d", d->tm_year+1900, d->tm_mon+1, d->tm_mday);
}


