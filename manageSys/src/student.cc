#include "student.h"

void STUDENT::showProfile(){
	clrscr();title();

	cout<<"我的个人信息...."<<endl;
	cout<<endl<<"_______________________________________________________________________________"<<endl;
	cout<<" 姓名\t\t: "<<name_<<endl;
	cout<<" 学号\t\t: "<<usn_<<endl;
	cout<<" 性别\t\t: "<<sex_<<endl;
	cout<<" 专业\t\t: "<<profession_<<endl;
	cout<<" 出生日期\t: "<<birth_<<endl;
	cout<<" Email\t\t: "<<email_<<endl;
	cout<<" 密码\t\t: "<<password_<<endl;
	cout<<endl<<"_______________________________________________________________________________"<<endl;

}

int STUDENT::changePWD( )
{ 
	clrscr(); title( ); setbuf(stdin, NULL);

	cout<<"\t输入旧密码：";
	string old_pwd,new_pwd; cin>>old_pwd;

	if(old_pwd == password_){
		cout<<"\t输入新密码：";
		cin>>new_pwd;
		int i=0;
		for(; i<3; ++i){ 
			cout<<"\t再次输入密码：";
			string pwd; cin>>pwd;
			if(pwd == new_pwd){ 
				//BUG  pwd应当保存到student文件人员上
				password_ = pwd;	break;
			} 
		}
		if( i >= 3) { 
			cout<<endl<<"\t\t密码修改失败"<<endl;
		}
		cout<<endl<<"\t\t修改成功..."<<endl;
	}else{ 
		cout<<"\t原始密码输入不正确！"<<endl;
	}
}

void STUDENT::manageCourse(const string& usr)
{ 
	while( 1){ 
		clrscr(); title( );
		cout<<"\t\t1 : 查看已修课程\n\t\t2 : 增添课程\n\t\t3 : 取消选修课程\n\t\t4 : 退出"<<endl;
		cout<<endl<<"_______________________________________________________________________________"<<endl;
		string id;
		cout<<"\t请选择 : ";
		int choice;	cin>>choice;
		switch(choice){
			case 1 ://显示course
				showCourseScore();
				break;
			case 2 ://add course 
				pMC_->showCourse(); //显示教务处所有课程
				cout<<"\t选择要修课程id  ：";cin>>id;
				if(-1 == addCourse(id))
					cout<<"\t无效的课程号..."<<endl;
				else	
					cout<<"\t成功选课！"<<endl;
				break;
			case 3 : //cancle course
				showCourseScore( );
				cout<<"\t输入取消选修课程id  ：";cin>>id;
				if(-1 == cancleCourse(id)) 
					cout<<"\t无效的课程号..."<<endl;
				else	cout<<"\t成功取消课程!"<<endl;
				break;        
			case 4 :
				cout<<"Logging out...["<<usn_<<"]";
				return ;
			default : cout<<"Select valid choice : ";
		}
		setbuf(stdin, NULL);cin.get();
	}
}

void STUDENT::showCourseScore() //显示学生的所有课程和分数 
{ 
	cout<<"\n\t--------------------------------------------------------";
	cout<<endl<<"\t课程id\t\t课程名\t\t分数"<<endl;
	for( auto& e: con_score_){ 
		cout<<"\t"<<e.first.course_id_<<"\t\t"<<e.first.course_name_<<"\t\t"<<e.second<<endl;
	}
	cout<<"\n\t--------------------------------------------------------"<<endl;
}

int STUDENT::addCourse(const string& c_id)//添加课程至con_score_容器
{ 
	set<Course>::iterator it = pMC_->findCourse(c_id);
	if(!pMC_->isValidCourse(c_id)) return -1;
	else{ 
		//元素为Course: score键值对
		Course c(c_id, it->course_name_, it->times_, it->credit_);
		con_score_.insert(make_pair(c, 0));//课程分数默认为0
	}
	return SUCCESS;
}
int STUDENT::cancleCourse(const string& c_id) 
{ 
	Ite it = con_score_.find(Course(c_id)) ;
	if(it == con_score_.end( )){ 	
		return -1;
	}else{ 
		con_score_.erase(it);
	}
	return SUCCESS;
}
int STUDENT::setScoreOfCourse(const string& c_id, int score)
{ 
	Ite it = con_score_.find(Course(c_id)) ;
	if(it == con_score_.end())	return -1; 

	it->second =  score;
	return SUCCESS;

}

/*********************************************
 * 管理学生：增、删、改、查
 *
 */
void ManageStudent::addStudent(ManageCourse* pMC, const string& u, 
		const string& name, const string& email, const string& s, 
		const string& pro, const string& birth,const string& pwd)
{
	int fg;
	findStudent(u, fg);
	if( fg == true) { cout<<"该生学号已使用，请重启添加...\n"; return;}
	contain_.push_back(STUDENT(pMC, u, name, email, s, pro, birth, pwd));
}
int ManageStudent::eraseStudent(const string& usn)
{ 
	Ite it = findStudent(usn);
	if(it == contain_.end( )) return -1;
	contain_.erase(it);
	return SUCCESS;
}

int ManageStudent::changeStudent(const string& usn)
{ 
	Ite it = findStudent(usn);
	if(it == contain_.end( )) return -1;

	string id,name,sex,depart,birth,email,pass; 
	cout<<"\n\t输入学生新id	: "; cin>>id;
	cout<<"\t输入学生新名字	: "; cin>>name;
	cout<<"\t输入学生新性别	: "; cin>>sex;
	cout<<"\t输入学生新系别	: "; cin>>depart;
	cout<<"\t输入学生新生日	: "; cin>>birth;
	cout<<"\t输入学生新email	: "; cin>>email;
	cout<<"\t输入学生新密码	: "; cin>>pass;
	it->usn_= id;
	it->name_= name;
	it->profession_= depart;
	it->email_ = email;
	it->birth_= birth;
	it->sex_ = sex;
	it->password_ = pass;
}
//show all students
void ManageStudent::showStudent( )
{ 
	cout<<"\n\t-------------------------------------------------------------";
	cout<<endl<<"\t学号\t学生名字\t性别\t专业\t联系方式\t密码"<<endl;
	for( auto& e: contain_){ 
		cout<<"\t"<<e.usn_<<"\t"<<e.name_<<"\t\t"<<e.sex_<<"\t"<<e.profession_<<"\t"<<e.email_<<"\t\t"<<e.password_<<endl;
	}
	cout<<"\n\t-------------------------------------------------------------"<<endl;
}


void ManageStudent::entryScore( )
{ 
	int s;
	cout<<"[[成绩录入]] \n\n";
	Ite it = contain_.begin( );
	if( contain_.empty( )) {cout<<"系统暂无学生信息...\n"; return;}
	while( it != contain_.end( )){ 
		cout<<"学生["<<it->usn_<<", "<<it->name_<<"]:\n";

		STUDENT::Ite in_it = it->con_score_.begin();
		if(it->con_score_.empty()) {cout<<"该生未选任何课程,请先为其添加课程...\n"; return;} 

		while(in_it != it->con_score_.end()){ 
			cout<<"\t录入课程["<<in_it->first.course_id_<<" ,"<<in_it->first.course_name_<<"]分数:";
			cin>>s; in_it->second = s;
			++in_it;
		}
		++it;
	}
	cout<<"_______________________________________________________________\n";
	cout<<"录入完毕！\n";
}

void ManageStudent::generateScoreTable( const string& c_id)
{ 
	score_table_.clear( );
	Ite it = contain_.begin( );
	while( it != contain_.end( )){ 
		//in_it 类型： map<Course, int>::iterator
		STUDENT::Ite in_it = it->con_score_.begin( );
		while(in_it != it->con_score_.end( )){ 
			if(in_it->first.course_id_ == c_id){ 
				ScoreTable st(in_it->first.course_id_, in_it->first.course_name_, it->name_, in_it->second);
				score_table_.insert(st);
			}	
			++in_it;
		}
		++it;
	}

	cout<<"\t_____________________________________________________________\n";
	cout<<"\t课程id\t\t课程名字\t学生名字\t分数"<<endl;
	TableIte table_it = score_table_.begin( );
	while(table_it != score_table_.end( )){ 
		cout<<"\t"<<table_it->c_id<<"\t\t"<<table_it->c_name<<"\t\t"<<table_it->s_name<<"\t\t"<<table_it->score<<endl;
		++table_it;
	}
	cout<<"\t_____________________________________________________________\n";
}


void ManageStudent::saveStudents(MYSQL& mysql)
{ 
	char sql_buf[ 128];
	for( auto& e: contain_){ 
		sprintf(sql_buf, "insert into student values('%s','%s','%s','%s','%s','%s','%s')", 
				e.usn_.c_str(),e.name_.c_str(),  e.profession_.c_str(), e.email_.c_str(),
				e.birth_.c_str(), e.sex_.c_str(), e.password_.c_str( ));

		if(mysql_real_query(&mysql, sql_buf, (unsigned long)strlen(sql_buf))){
			cerr << "mysql_real_query failure！" << endl;
		}

		//save score to mysql
		for( auto& in_e : e.con_score_){ 
			sprintf(sql_buf, "insert into score values('%s','%s','%s','%s','%d')", 
					e.usn_.c_str(), e.name_.c_str(),  in_e.first.course_id_.c_str(), 
					in_e.first.course_name_.c_str( ), in_e.second);

			if(mysql_real_query(&mysql, sql_buf, (unsigned long)strlen(sql_buf))){
				cerr << "mysql_real_query failure！" << endl;
			}
		} 
	}
}

