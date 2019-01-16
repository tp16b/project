#include "admin.h"

void Admin::manageCourse()
{ 
	while( 1){ 
		clrscr();title( );
		cout<<"_______________________________________________________________________________"<<endl;
		cout<<"\t\t1 : 添加课程入教务系统\n\t\t2 : 修改课程\n\t\t3 : 删除课程\n\t\t4 : 查看所有课程\n\t\t5 : 退出"<<endl;
		cout<<"_______________________________________________________________________________"<<endl;
		cout<<"\n\t请选择 : ";
		int choice; cin>>choice;
		string id,name; 
		int cnt, credit;
		switch(choice){
			case 1:
				cout<<"\n\t输入课程id	: "; cin>>id;
				cout<<"\t输入课程名字	: "; cin>>name;
				cout<<"\t输入课程学时	: "; cin>>cnt;
				cout<<"\t输入课程学分	: "; cin>>credit;
				pMC_->addCourse(id, name, cnt, credit);
				cout<<"\t成功添加！"<<endl;
				break;
			case 2: //change course
				pMC_->showCourse();
				cout<<"\t输入要修改的课程id  ：";cin>>id;
				if(-1 == pMC_->changeCourse(id)) { 
					cout<<"\t无效的课程号..."<<endl;
				}else{ 
					cout<<"\t修改课程成功！";
				}
				break;
			case 3: //erase course
				pMC_->showCourse();
				cout<<"\t输入要删除课程id  ：";cin>>id;
				if(-1 == pMC_->eraseCourse(id)){ 
					cout<<"\t无效的课程号..."<<endl;
				}else{ 
					cout<<"\t成功取消课程!"<<endl;
				}
				break;
			case 4:
				pMC_->showCourse();
				break;
			case 5:
				return;
			default : 
				cout<<"Invalid choice..."<<endl;
		}
		cout<<"\tEnter any to continue...\n";
		setbuf(stdin, NULL);cin.get( );
	}

}
void Admin::manageTeacher( )
{ 
	while( 1){ 
		clrscr();title( );
		cout<<"_______________________________________________________________________________"<<endl;
		cout<<"\t\t1 : 添加教师入教务系统\n\t\t2 : 修改教师信息\n\t\t3 : 删除教师\n\t\t4 : 查看所有教师信息\n\t\t5 : 退出"<<endl;
		cout<<"_______________________________________________________________________________"<<endl;
		cout<<"\n\t请选择 : ";
		int choice; cin>>choice;
		string id,name,depart,day,email; 
		switch(choice){
			case 1:
				cout<<"\n\t输入教师id			: "; cin>>id;
				cout<<"\t输入教师名字			: "; cin>>name;
				cout<<"\t输入教师系别			: "; cin>>depart;
				cout<<"\t输入教师出生日期		: "; cin>>day;
				cout<<"\t输入教师email			: "; cin>>email;
				pMT_->addTeacher(id, name, depart,day, email);
				cout<<"\t成功添加！"<<endl;
				break;
			case 2: //change teacher 
				cout<<"\t输入要修改的教师id  ：";cin>>id;
				if(-1 == pMT_->changeTeacher(id)) { 
					cout<<"\t无效的教工号..."<<endl;
				}else{ 
					cout<<"\t修改成功！";
				}
				break;
			case 3: //erase teacher 
				cout<<"\t输入要删除教工id  ：";cin>>id;
				if(-1 == pMT_->eraseTeacher(id)){ 
					cout<<"\t无效的教工号..."<<endl;
				}else{ 
					cout<<"\t成功取消教工!"<<endl;
				}
				break;
			case 4:
				pMT_->showTeacher();
				break;
			case 5:
				return;
			default : cout<<"Select valid choice : ";
		}
		cout<<"\tEnter any to continue...\n";
		setbuf(stdin, NULL);cin.get( );
	}
}
void Admin::manageGrade( )
{ 
	while( 1){ 
		clrscr();title( );
		cout<<"_______________________________________________________________________________"<<endl;
		cout<<"\t\t1 : 添加班级入教务系统\n\t\t2 : 修改班级信息\n\t\t3 : 删除班级\n\t\t4 : 查看所有班级信息\n\t\t\n\t\t5 : 退出"<<endl;
		cout<<"_______________________________________________________________________________"<<endl;
		cout<<"\n\t请选择 : ";
		int cnt,choice; cin>>choice;
		string id,depart; 
		switch(choice){
			case 1:
				cout<<"\n\t输入班级id	: "; cin>>id;
				cout<<"\t输入班级系别	: "; cin>>depart;
				cout<<"\t输入班级人数	: "; cin>>cnt;
				pMG_->addGrade(id, depart,cnt);
				cout<<"\t成功添加！"<<endl;
				break;
			case 2: //change 
				cout<<"\t输入要修改的班级id  ：";cin>>id;
				if(-1 == pMG_->changeGrade(id)) { 
					cout<<"\t无效的班级号..."<<endl;
				}else{ 
					cout<<"\t修改成功！";
				}
				break;
			case 3: //erase 
				cout<<"\t输入要删除班级id  ：";cin>>id;
				if(-1 == pMG_->eraseGrade(id)){ 
					cout<<"\t无效的班级号..."<<endl;
				}else{ 
					cout<<"\t删除成功!"<<endl;
				}
				break;
			case 4:
				pMG_->showGrade();
				break;
			case 5:
				return;
			default : 
				cout<<"Invalid choice : ";
		}
		cout<<"\tEnter any to continue...\n";
		setbuf(stdin, NULL);cin.get( );
	}
}

void Admin::manageStudent( )
{ 
	while( 1){ 
		clrscr();title( );
		cout<<"\t\t1 : 添加学生入教务系统\n\t\t2 : 修改学生信息\n\t\t3 : 删除学生信息\n\t\t4 : 查看所有学生信息\n\t\t5: 退出"<<endl;
		cout<<"_______________________________________________________________________________"<<endl;
		cout<<"\n\t请选择 : ";
		int cnt,choice; cin>>choice;
		string id,name,email,sex,pro,birth,pwd; 
		switch(choice){
			case 1: //add stu to sys
				cout<<"\n\t输入学生id	: "; cin>>id;
				cout<<"\t输入学生姓名	: "; cin>>name;
				cout<<"\t输入学生性别	: "; cin>>sex;
				cout<<"\t输入学生专业	: "; cin>>pro;
				cout<<"\t输入学生生日	: "; cin>>birth;
				cout<<"\t输入学生email	: "; cin>>email;
				cout<<"\t输入学生密码	: "; cin>>pwd;
				pMS_->addStudent(pMC_, id, name, email, sex, pro, birth,pwd);
				cout<<"\t成功添加！"<<endl;
				break;
			case 2: //change stu in sys
				pMS_->showStudent();//提前显示student名单
				cout<<"\t输入要修改的学生id  ：";cin>>id;
				if(-1 == pMS_->changeStudent(id)) { 
					cout<<"\t无效的学生号..."<<endl;
				}else{ 
					cout<<"\t修改成功！";
				}
				break;
			case 3: //erase  stu from sys
				pMS_->showStudent(); //提前显示student名单
				cout<<"\t输入要删除学生id  ：";cin>>id;
				if(-1 == pMS_->eraseStudent(id)){ 
					cout<<"\t无效的学生号..."<<endl;
				}else{ 
					cout<<"\t删除成功!"<<endl;
				}
				break;
			case 4: //show all stu in sys 
				pMS_->showStudent();
				break;
			case 5:
				return;
			default : 
				cout<<"Invalid choice : ";
		}
		cout<<"\tEnter any to continue...\n";
		setbuf(stdin, NULL);cin.get( );
	}
}

/*************************************************************
 *   处理学生选课
 */
void Admin::handleChooseCourse( )
{ 
	while( 1){ 
		clrscr();title( );
		cout<<"\t\t1 : 为学生添加课程\n\t\t2 : 删除学生选修课程\n\t\t3 : 修改学生选修课程\n\t\t4 : 退出"<<endl;
		cout<<"_______________________________________________________________________________"<<endl;
		cout<<"\n\t请选择 : ";
		int choice; cin>>choice;
		switch(choice){
			case 1://add
				addCourseForStu();
				break;
			case 2://cancel 
				cancleCourseForStu();
				break;
			case 3://change 
				break;
			case 4:
				return;
			default : 
				cout<<"Invalid choice : ";
		}
		setbuf(stdin, NULL);cin.get( );
	}
}
void Admin::addCourseForStu()
{ 
	pMS_->showStudent( ) ;
	string s_id,c_id;
	cout<<"\n\t输入学生id: "; cin>>s_id;
	//找到学生
	int flag;
	list<STUDENT>::iterator it = pMS_->findStudent(s_id, flag);
	if(flag == false){ 
		cout<<"\t无效的学生号..."<<endl; 
		return;
	}
	cout<<"\n教务系统提供课程 :"<<endl;
	pMC_->showCourse( );//提前显示系统所有课程
	cout<<"\n\t输入课程id: "; cin>>c_id;
	if(-1 == it->addCourse(c_id)){ 
		cout<<"\t无效的课程号..."<<endl;
		return;
	}

	cout<<"\t添加成功! "<<endl;
}
void Admin::cancleCourseForStu()
{ 
	string s_id,c_id;
	cout<<"\t输入学生id: "; cin>>s_id;
	int flag;
	list<STUDENT>::iterator it = pMS_->findStudent(s_id, flag);
	if(flag == false){ 
		cout<<"\t无效的学生号..."<<endl;  return;
	}
	cout<<"-----------------------  学生已修课程  -----------------------------"<<endl;

	it->showCourseScore( );

	cout<<"\n\t输入删除课程id: "; cin>>c_id;
	if(-1 == it->cancleCourse(c_id)) { 
		cout<<"\t无效的课程号..."<<endl; return;
	}
	cout<<"\t删除成功!"<<endl;
}

/**********************************************************
 * 成绩管理：
 *   1.录入成绩
 *   2. a.据学号查询该生所有课程成绩
 *		b.据课程查询本门课程所有学生成绩
 *	 3.修改..学生..课程成绩
 */
void Admin::manageScore( )
{ 
	while( 1){ 
		clrscr();title( );
		cout<<"\t\t1 : 成绩录入\n\t\t2 : 成绩查询\n\t\t3 : 学生个人成绩修改\n\t\t4 : 退出"<<endl;
		cout<<"_______________________________________________________________________________"<<endl;
		cout<<"\n\t请选择 : ";
		int choice; cin>>choice;
		int fg;
		switch(choice){
			case 1://add
				EntryScore( );
				break;
			case 2://cancel 
				cout<<"\t[1] 按学号查看该生所有成绩     [2] 按课程号查看所有学生成绩"<<endl;
				cout<<"\t\t选择 ：";cin>>fg;
				if(fg == 1)	broseScoreOfStu( );
				else if(fg == 2) broseScoreOfCourse( );
				else cout<<"选择错误..."<<endl;
				break;
			case 3://change 
				changeScoreOfStu( );
				break;
			case 4:
				return;
			default : 
				cout<<"Invalid choice : ";
		}
		setbuf(stdin, NULL);cin.get( );
	}
}

/* 成绩录入。 方式1： stu( c1, c2,c3, ....)*/
/*            方式2:  cou( s1, s2,s3, ....)*/
void Admin::EntryScore( )
{ 
	clrscr();title( );
	pMS_->entryScore( );
}
void Admin::changeScoreOfStu()
{ 
	string s_id,c_id;
	int flag,score;
	cout<<"\n\t输入学生id  :";cin>>s_id;
	list<STUDENT>::iterator it = pMS_->findStudent( s_id, flag);
	if(flag == false){ 
		cout<<"\t无效的学生id..."<<endl; return;
	} 
	it->showCourseScore( ); //该生所有课程信息

	cout<<"\t选择修改成绩的课程id  :";cin>>c_id;
	if( !it->isValidCourse(c_id)){ 
		cout<<"\t无效课程id...\n"; return;
	}	
	cout<<"\t输入课程新成绩：";cin>>score;
	if(-1 == it->setScoreOfCourse(c_id, score)) { 
		cout<<"\t修改失败\n"; return;
	}
	cout<<"\t修改成功！\n";
}
void Admin::broseScoreOfStu( )
{ 
	cout<<"【系统所有学生】:\n";
	pMS_->showStudent( );
	string s_id;
	cout<<"\n输入学生id  :";cin>>s_id;
	int flag;
	list<STUDENT>::iterator it = pMS_->findStudent( s_id, flag);
	if(flag == false){ 
		cout<<"\t无效的学生id..."<<endl; return;
	} 
	it->showCourseScore( );
}
void Admin::broseScoreOfCourse( )
{ 
	cout<<"【系统所有课程 】：";
	pMC_->showCourse( );
	string c_id;
	cout<<"输入要查询的课程id:";cin>>c_id;
	pMS_->generateScoreTable(c_id );		
}


/*******************************************************
 * 加载与保存
 */
void Admin::loadData( )
{ 
	MYSQL mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	mysql_init (&mysql);

	if(!mysql_real_connect(&mysql, "127.0.0.1", "root", "tpbeat","manage", 3306,0,0)){
		cerr<< "mysql_real_connect failure！" << endl;
	}

	//load course
	if(mysql_real_query(&mysql,"select * from course", (unsigned long)strlen("select * from course"))){
		cerr<< "mysql_real_query failure！" << endl;
	}
	res = mysql_store_result(&mysql);
	if(NULL == res){
		cerr << "mysql_store_result failure！" << endl;
	}
	while (row = mysql_fetch_row(res))
	{
		string c_id(row[0]) ;
		string c_name(row[1]);
		int tm = atoi(row[2]) ;
		int ce = atoi(row[3]) ;
		pMC_->addCourse(c_id, c_name, tm, ce);
	}
	mysql_free_result(res);

	//load teacher 
	if(mysql_real_query(&mysql,"select * from teacher", (unsigned long)strlen("select * from teacher"))){
		cerr<< "mysql_real_query failure！" << endl;
	}
	res = mysql_store_result(&mysql);
	if(NULL == res){
		cerr<< "mysql_store_result failure！" << endl;
	}
	while (row = mysql_fetch_row(res)){
		string t_id(row[0]) ;
		string t_name(row[1]);
		string depart(row[2]) ;
		string birth(row[3]) ;
		string email(row[4]) ;
		pMT_->addTeacher(t_id, t_name, depart, birth, email);
	}
	mysql_free_result(res);

	//load grade  班级 
	if(mysql_real_query(&mysql,"select * from grade", (unsigned long)strlen("select * from grade"))){
		cerr<< "mysql_real_query failure！" << endl;
	}
	res = mysql_store_result(&mysql);
	if(NULL == res){
		cerr<< "mysql_store_result failure！" << endl;
	}
	while (row = mysql_fetch_row(res)){
		string g_id(row[0]) ;
		string depart(row[1]) ;
		int n = atoi(row[2]);
		pMG_->addGrade(g_id, depart, n);
	}
	mysql_free_result(res);


	//load student
	if(mysql_real_query(&mysql,"select * from student", (unsigned long)strlen("select * from student"))){
		cerr<< "mysql_real_query failure！" << endl;
	}
	res = mysql_store_result(&mysql);
	if(NULL == res){
		cerr<< "mysql_store_result failure！" << endl;
	}
	while (row = mysql_fetch_row(res)){
		string id(row[0]) ;
		string name(row[1]) ;
		string prof(row[2]) ;
		string email(row[3]) ;
		string birth(row[4]) ;
		string sex( row[ 5]);
		string pass(row[6] );
		pMS_->addStudent(pMC_, id, name, email, sex, prof, birth, pass);
	}
	mysql_free_result(res);

	//load score
	if(mysql_real_query(&mysql,"select * from score", 
			(unsigned long)strlen("select * from score"))){
		cerr<< "mysql_real_query failure！" << endl;
	}
	res = mysql_store_result(&mysql);
	if(NULL == res){
		cerr<< "mysql_store_result failure！" << endl;
	}
	while (row = mysql_fetch_row(res)){
		string s_id(row[0]) ;
		string s_name(row[1]) ;
		string c_id(row[2]) ;
		string c_name(row[3]) ;
		int n = atoi(row[4]);

		int flag;
		list<STUDENT>::iterator it = pMS_->findStudent(s_id, flag);
		it->addCourse(c_id);
		it->setScoreOfCourse(c_id, n);
	}
	mysql_free_result(res);

//	cout<<"load course teacher grade ok!\n"	;
	mysql_close(&mysql);
}


//保存到mysql
void Admin::saveData( )
{ 
	MYSQL mysql;
	mysql_init(&mysql);
	if(!mysql_real_connect(&mysql, "127.0.0.1", "root", "tpbeat","manage", 3306,0,0)){
		cerr<< "mysql_real_connect failure！" << endl;
	}

	//清空数据库中表信息
	if(mysql_real_query(&mysql,"delete from course", (unsigned long)strlen("delete from course"))){
		cerr<< "mysql_real_query failure！" << endl;
	}
	if(mysql_real_query(&mysql,"delete from teacher", (unsigned long)strlen("delete from teacher"))){
		cerr<< "mysql_real_query failure！" << endl;
	}
	if(mysql_real_query(&mysql,"delete from grade", (unsigned long)strlen("delete from grade"))){
		cerr<< "mysql_real_query failure！" << endl;
	}
	if(mysql_real_query(&mysql,"delete from student", (unsigned long)strlen("delete from student"))){
		cerr<< "mysql_real_query failure！" << endl;
	}
	if(mysql_real_query(&mysql,"delete from score", (unsigned long)strlen("delete from score"))){
		cerr<< "mysql_real_query failure！" << endl;
	}
	//将数据保存至mysql
	pMC_->saveCourses(mysql );
	pMT_->saveTeachers(mysql );
	pMG_->saveGrades(mysql)	;
	pMS_->saveStudents(mysql )	;
	//pMS_->saveScores(mysql);//not need

	mysql_close( &mysql);
}
