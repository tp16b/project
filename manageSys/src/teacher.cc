#include "teacher.h"
//#include "student.h"

void Teacher::showProfile() //查看教师个人信息
{
	clrscr(); title();

	cout<<"Proifile...."<<endl;
	cout<<"_______________________________________________________________________________"<<endl; cout<<" Teacher Name      \t :"<<teacher_name_<<endl;
	cout<<" Teacher Id        \t :"<<teacher_id_<<endl;
	cout<<" Department      \t :"<<birth_; 
	cout<<" Email id        \t :"<<email_<<endl;
	cout<<"_______________________________________________________________________________"<<endl;
	cout<<" Enter any to exit...\n";
	setbuf( stdin, NULL);cin.get();
}

int ManageTeacher::addTeacher(const string& t_id, const string& name, const string& depart, const string& birth, const string& email) 
{ 
	contain_.insert(Teacher(t_id, name, depart, birth, email));
	return SUCCESS;
}
int ManageTeacher::eraseTeacher(const string& t_id)
{ 
	Ite it = findTeacher(t_id);
	if( it == contain_.end( )) return -1;
	
	contain_.erase(it);
	return SUCCESS;
}
int ManageTeacher::changeTeacher(const string& t_id)
{ 
	Ite it = findTeacher(t_id);
	if( it == contain_.end( )) return -1;

	contain_.erase(it);

	string id,name,depart,birth,email; 
	cout<<"\n\t输入教工id	: "; cin>>id;
	cout<<"\t输入教工名字	: "; cin>>name;
	cout<<"\t输入教工系别   : "; cin>>depart;
	cout<<"\t输入教工生日	: "; cin>>birth;
	cout<<"\t输入教工email  : "; cin>>email;
	contain_.insert(Teacher(id, name, depart,birth, email));

	return SUCCESS;
}


void ManageTeacher::showTeacher()
{ 
	Ite it = contain_.begin( );
	cout<<"\n\t--------------------------------------------------------";
	cout<<endl<<"\t教工号\t教工名字\t所属系别\t联系方式"<<endl;
	while(it != contain_.end( )){ 
		cout<<"\t"<<it->teacher_id_<<"\t\t"<<it->teacher_name_<<"\t\t"<<it->department_<<"\t\t"<<it->email_<<endl;
		++it;
	}
	cout<<"\n\t--------------------------------------------------------"<<endl;
}

void ManageTeacher::saveTeachers(MYSQL& mysql)
{ 
	char sql_buf[ 128];
	for( auto& e: contain_){ 
		sprintf(sql_buf, "insert into teacher values('%s','%s','%s','%s','%s')", e.teacher_id_.c_str(),e.teacher_name_.c_str(), e.department_.c_str(), e.birth_.c_str( ), e.email_.c_str( ));

		if(mysql_real_query(&mysql, sql_buf, (unsigned long)strlen(sql_buf))){
			cerr << "mysql_real_query failure！" << endl;
			sleep( 4);
		}
	}
}
