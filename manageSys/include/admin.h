#pragma once

#include "common.h"
#include "student.h"
#include "course.h"
#include "teacher.h"
#include "grade.h"

class Admin
{
private:
	int admin_id_;
	string admin_name_;	
	string admin_pass_;
	
	ManageCourse* pMC_;  //管理课程句柄
	ManageTeacher* pMT_; //管理教师句柄
	ManageGrade* pMG_;   //管理班级句柄
	ManageStudent* pMS_; //管理学生句柄
public :
	Admin(ManageCourse* pMC, int id=0, const string& name="admin", const string& pass="123")
		:admin_id_(id),admin_name_( name),admin_pass_(pass),
		pMC_(pMC),pMT_(new ManageTeacher),
		pMG_(new ManageGrade), pMS_(new ManageStudent) { }

	~Admin( ) {
		delete pMT_; pMT_ = NULL;
		delete pMG_; pMG_ = NULL;
		delete pMS_; pMS_ = NULL;
	}
	ManageStudent* getStuHandle( )  { return pMS_;}
	
	//manage course member function
	void manageCourse();

	//manage teachers member function
	void manageTeacher();

	//manage grade member function   班级管理
	void manageGrade( );

	//manage students member function
	void manageStudent( );

	//manage score member function 学生成绩管理
	void manageScore( );
	void EntryScore( );        //成绩录入
	void broseScoreOfStu( );   //学生的所有课程成绩
	void broseScoreOfCourse( );//课程下所有学生成绩
	void changeScoreOfStu( ); //为相关学生修改课程成绩


	//handle student choose course
	void handleChooseCourse( );
	void addCourseForStu();
	void cancleCourseForStu();
	
	void showProfile();
	//int complaint(); //no need

	//加载
	void loadData( );
	//保存
	void saveData( );
};

