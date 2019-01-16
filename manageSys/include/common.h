#pragma once 

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>// FILE HANDLING
#include <string>
#include <cstring>
#include <cassert>
#include <cstdio>
#include <unistd.h>

#include <list>
#include <set>
#include <map>
#include <mysql/mysql.h>
#define F_NOT_FOUND -1
#define USN_NOT_FOUND -2
#define SUCCESS 0
#define ADMIN_PASS "123"

using namespace std;

static int flag;
static inline void clrscr() {system("clear");}

static inline void title(){
	//clrscr();
	cout<<"==============================================================================="<<endl;
	cout<<"***************************** 学信通学籍管理系统 ******************************"<<endl;
	cout<<"==============================================================================="<<endl;
}

/*字符串转大写(linux没有原生strupr)*/
static char* strupr(char* src){
	if( src == NULL) assert(false);

	while (*src != '\0'){
		if (*src >= 'a' && *src <= 'z')
			//在ASCII表里大写字符的值比对应小写字符的值小32.
			//*p -= 0x20; // 0x20的十进制就是32
			*src -= 32;
		src++;
	}
	return src;
}

/*字符串转小写(linux没有原生strlwr)*/
static char* strlwr(char* src){
	if( src == NULL) assert(false);

	while (*src != '\0'){
		if (*src > 'A' && *src <= 'Z') *src += 32;
		src++;
	}
	return src;
}
static void getdate(char *tday){
	time_t tim;
	tim=time(NULL);
	struct tm *d=localtime(&tim);
	sprintf(tday,"%02d/%02d/%d",d->tm_mday,d->tm_mon+1,d->tm_year+1900);
}

//sets current date in file
//static void setbits(){
//	ofstream setb;
//	char today[11];
//	getdate(today);
//	switch(subject){
//		case 1 :setb.open("math.dat");
//				setb<<today;
//				break;
//		case 2 :setb.open("co.dat");
//				setb<<today;
//				break;
//		case 3 :setb.open("mp.dat");
//				setb<<today;
//				break;
//		case 4 :setb.open("oop.dat");
//				setb<<today;
//				break;
//	}
//	setb.close();
//};

//return true if attendence is already entered

