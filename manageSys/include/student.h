#pragma once

#include "common.h"
#include "course.h"


struct STUDENT
{
typedef map<Course, int>::iterator Ite;
//private:
		string usn_;
		string name_;
		string profession_; //专业
		string email_;
		string birth_;		//出生日期
		string sex_;			//性别
		string password_;

		ManageCourse* pMC_;       //ManageCourse进行交互,从系统选得课程	
		map<Course, int> con_score_;//存储课程及其对应分数的map容器
//public:
		STUDENT(ManageCourse* pMC, const string& u="S00",const string& name="", const string& email="", 
				const string& sex="", const string& pro="计算机科学与技术", 
				const string& birth="1970-1-1",	const string& pwd="123") 
			: usn_(u),name_(name),profession_(pro), 
			  email_(email),birth_(birth),sex_(sex), 
			  password_(pwd),pMC_(pMC) {}

		//STUDENT& operator=(const STUDENT& s);   //赋值运算重载
		bool operator==(const STUDENT& s) const{ 
			if(usn_ == s.usn_) return true;
			else return false;
		}

		bool isValidCourse(const string& c_id){ 
			Ite it = con_score_.find(Course(c_id)) ;
			if( it == con_score_.end( )) return false;
			return true;
		}
		//设置学生某门课程分数
		int setScoreOfCourse(const string& c_id, int);
			
		//个人信息操作
		int init(char*);
		void showProfile(); //显示学生个人信息
		int changePWD();

		//选课管理
		void manageCourse(const string& admin_id); 
		int addCourse(const string& c_id) ;    //添加课程至con_score_容器
		int cancleCourse(const string& c_id) ;

		//成绩查询
		void showCourseScore() ; //显示学生所有课程与分数 
	//	int complaint();
};
struct ScoreTable{ 
	string c_id;
	string c_name;
	string s_name;
	int score;
	ScoreTable(const string& id, const string& c_n, const string& s_n, int s)
		:c_id( id),c_name( c_n),s_name( s_n),score(s) { }

	bool operator<(const ScoreTable& rhs) const{ 
		if(score  < rhs.score) return false;
		else return true;;
	}
};

class ManageStudent
{ 
typedef list<STUDENT>::iterator Ite; 
typedef multiset<ScoreTable>::iterator TableIte; 
private:
	list<STUDENT> contain_;
	multiset<ScoreTable> score_table_;	//成绩表  根据课程从高到低查看学生分数
public:
	//add student
	void addStudent(ManageCourse* pMC, const string&, const string&, const string&, 
			const string&, const string&, const string& ,const string&);
	//erase  student
	int eraseStudent(const string& usn);	
	//change student information
	int changeStudent(const string& usn);
	//show all students
	void showStudent( );
	void saveStudents(MYSQL&);

	//entry Score to sys
	void entryScore( );
	//generate score table
	void generateScoreTable(const string& c_id);
	//void saveScores(MYSQL&);

	Ite findStudent(const string& usn){ 
		Ite it = contain_.begin( );
		while( it != contain_.end()){ 
			if( it->usn_ == usn) return it;
			++it;
		}
		return it;
	}
	//提供给外部使用确定findStudent是否成功
	Ite findStudent(const string& usn, int& flag){ 
		Ite it = contain_.begin( );
		while( it != contain_.end()){ 
			if( it->usn_ == usn) {flag = true;return it;}		
			++it;
		}
		flag = false; return it;
	}
};
