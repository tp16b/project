#pragma once 

#include "common.h"

struct Teacher 
{
	string teacher_id_;
	string teacher_name_;
	string department_;
	string birth_;
	string email_;

	Teacher(const string& id="T00", const string& name="", 
			const string& depart="Computer And Science", 
			const string& birth="1997-1-1", 
			const string& email="tp_16b@163.com")
	:teacher_id_(id),teacher_name_(name),
		department_(depart),birth_( birth),
		email_( email)	{}
	//
	bool operator<(const Teacher& rhs) const{ 
		if(teacher_id_ < rhs.teacher_id_) return true;
		else return false;
	}
	void showProfile(); //
};

class ManageTeacher
{ 
typedef set<Teacher>::iterator Ite;
private:
	set<Teacher> contain_;
public:
	int addTeacher(const string&, const string&,const string&, const string&, const string&) ;
	int eraseTeacher(const string&);
	int changeTeacher(const string&);
	void showTeacher();
	void saveTeachers(MYSQL& );
	Ite findTeacher(const string& t_id){ return contain_.find(Teacher(t_id));}

};
