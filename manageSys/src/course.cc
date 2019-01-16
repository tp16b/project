/*=====================================================
 *   Copyright(C) 2019   All rights reserved.
 * 
 *   文件名称：course.cc
 *   创 建 者：tp    tp_16b@163.com
 *   创建日期：2019年01月03日
 *   描    述：
 ====================================================*/

#include "course.h"

int ManageCourse::addCourse(const string& c_no, const string& c_name, int t, int c) 
{ 
	Course course(c_no, c_name, t, c);
	contain_.insert(course);	
	return SUCCESS;
}
int ManageCourse::changeCourse(const string& c_no) 
{ 
	Ite it = findCourse(c_no);
	if( it == contain_.end( )){ //no find
		return -1;	
	}

	//修改选择的课程
	string id,name; 
	int cnt, credit;
	cout<<"\n\t输入课程新id	: "; cin>>id;
	cout<<"\t输入课程名字	: "; cin>>name;
	cout<<"\t输入课程学时	: "; cin>>cnt;
	cout<<"\t输入课程学分	: "; cin>>credit;
	contain_.erase(it);
	contain_.insert(Course(id, name, cnt, credit));

	return SUCCESS;
}
int ManageCourse::eraseCourse(const string& c_no) 
{ 
	Ite it = findCourse(c_no);
	if( it == contain_.end( )){ //no find
		return -1;	
	}
	contain_.erase(it);
	return SUCCESS;
}

void ManageCourse::showCourse() 
{ 
	Ite it = contain_.begin();
	cout<<"\n\t--------------------------------------------------------";
	cout<<endl<<"\t课程代号\t课程名称\t课程学时\t课程学分"<<endl;
	while( it != contain_.end( )){ 
		cout<<"\t"<<it->course_id_<<"\t\t"<<it->course_name_<<"\t\t"<<it->times_<<"\t\t"<<it->credit_<<endl;
		++it;
	}
	cout<<"\n\t--------------------------------------------------------"<<endl;
}

void ManageCourse::saveCourses(MYSQL& mysql)
{ 
	char sql_buf[ 128];
	for( auto& e: contain_){ 
		sprintf(sql_buf, "insert into course values('%s','%s',%d,%d)", e.course_id_.c_str(),e.course_name_.c_str(), e.times_, e.credit_ );

		if(mysql_real_query(&mysql, sql_buf, (unsigned long)strlen(sql_buf))){
			cerr << "mysql_real_query failure！" << endl;
		}
	}

}
