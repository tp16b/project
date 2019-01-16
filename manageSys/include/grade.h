/*=====================================================
  *   Copyright(C) 2019   All rights reserved.
  * 
  *   文件名称：grade.h
  *   创 建 者：tp    tp_16b@163.com
  *   创建日期：2019年01月04日
  *   描    述：
====================================================*/
#pragma once 

#include "common.h"

struct Grade
{ 
	string grade_id_;
	string department_;
	int member_num_;

	Grade(const string& id="G00", const string& depart="计算机学院", int num=0)
		:grade_id_( id),department_( depart),member_num_(num){ }
	bool operator<(const Grade& rhs) const{ 
		if( grade_id_ < rhs.grade_id_)return true;
		else return false;
	}
	
};
class ManageGrade
{ 
typedef set<Grade>::iterator Ite;
private:
	set<Grade> contain_;
public:
	int addGrade(const string& , const string& , int);
	int eraseGrade(const string&);
	int changeGrade(const string&);
	void showGrade( ) ;
	void saveGrades(MYSQL&);
	Ite findGrade(const string& g_id){ return contain_.find(Grade(g_id)); }
};
