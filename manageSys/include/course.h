/*=====================================================
  *   Copyright(C) 2019   All rights reserved.
  * 
  *   文件名称：course.h
  *   创 建 者：tp    tp_16b@163.com
  *   创建日期：2019年01月03日
  *   描    述：
====================================================*/
#pragma once

#include "common.h"

struct Course
{ 
	string course_id_;  //课程id
	string course_name_;//课程名
	int times_;         //学时
	int credit_;        //学分
//int	score_;         //分数 

	Course(const string& ci="C00", const string& cn="", int times=0, int c=0, int s=0)
		:course_id_( ci),course_name_( cn),times_(times),credit_(c) { }
	Course(const Course& c){ 
		course_id_ = c.course_id_;	
		course_name_ = c.course_name_;	
		times_ = c.times_;
		credit_ = c.credit_;
		//score_ = c.score_;
	}

	bool operator<(const Course& rhs) const{ 
		if(course_id_ < rhs.course_id_) return true;
		else return false;
	}
	string getId()const{ 
		return course_id_;
	}
};

//管理课程类
class ManageCourse
{ 
typedef set<Course>::iterator Ite;
private:
	set<Course>  contain_;  //存储课程set容器
public:
	//set<Course> getCon( )  { return contain_;}
	int addCourse(const string& , const string& , int, int) ;
	int changeCourse(const string&) ;
	int eraseCourse(const string&) ;
	Ite findCourse(const string& c_id) {return contain_.find(Course(c_id));}
	bool isValidCourse(const string& c_id){ 
		Ite it = findCourse(c_id);
		if(it == contain_.end( )) return false;
		else return true;
	}
	void showCourse();         //显示系统中所有课程信息

	void saveCourses(MYSQL& );

};

