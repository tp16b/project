#include "common.h"
#include "admin.h"
#include "course.h"
#include <termio.h>

int Getch(){
	struct termios tm, tm_old;
	int fd = 0, ch;
	//保存现在的终端设置
	if (tcgetattr(fd, &tm) < 0)  return -1;

	tm_old = tm;
	cfmakeraw(&tm);//更改终端设置为原始模式，该模式下所有的输入数据以字节为单位被处理

	//设置上更改之后的设置
	if(tcsetattr(fd, TCSANOW, &tm) < 0)  return -1;

	ch = getchar();
	//更改设置为最初的样子
	if(tcsetattr(fd, TCSANOW, &tm_old) < 0) return -1;
	return ch;
}

int student( Admin& ad)
{
	clrscr();title();
	string s_id;
	int i=0, fg;	
	char pass[15],c;
	//学号密码验证
	cout<<"\n\t\t学 工 号："; cin>>s_id;
	cout<<"\n\t\t密    码："; 
	list<STUDENT>::iterator it = ad.getStuHandle()->findStudent(s_id, fg);
	setbuf(stdin, NULL);
	while((c=Getch()) != 13){ //13 回车ascii码
		pass[i]=c; i++; cout<<'*';
	}
	pass[i]='\0';

	if( fg == false) { cout<<"\n\t\t无效的学工号...\n"; return -1;}
	string pwd(pass);
	if(pwd != it->password_) { cout<<"\n\t\t密码错误!"; return -1;}

	int choice;
	while(1) {
		clrscr(); title();
		cout<<"\t登录类型: 学生["<<it->usn_<<"]"<<endl<<endl;
		cout<<"\t\t1 : 查看个人信息\n\t\t2 : 修改个人密码\n\t\t3 : 成绩查询\n\t\t4 : 选课管理\n\t\t5 : 反    馈\n\t\t6 : 退    出"<<endl;
		cout<<"_______________________________________________________________________________"<<endl;
		cout<<"\t请选择 : ";
		cin>>choice;
		switch(choice){
			case 1 : //show profile
				it->showProfile();
				break;
			case 2 :  //change pwd
				clrscr();
				it->changePWD( );
				break;
			case 3 : //show all course score
				it->showCourseScore( );
				break;
			case 4 : 
				it->manageCourse("tp");
				break;        
			case 5 : 
				it->Complaint( );
				break;      
			case 6 : 
				cout<<"["<<it->usn_<<"]退出..."; 
				return SUCCESS;
			default : cout<<"Select valid choice : ";
		}
		setbuf(stdin, NULL); cin.get();
	}
	return -1;
}


int admin(Admin& ad)
{
	while(1){
		clrscr(); title();
		cout<<"\t【登录类型】: 管理员[admin"<<"]"<<endl;
		cout<<"_______________________________________________________________________________"<<endl;
		cout<<"\t\t1 : 学生管理\n\t\t2 : 教师管理\n\t\t3 : 班级管理\n\t\t4 : 课程管理\n\t\t5 : 学生成绩管理\n\t\t6 : 学生选课管理";
		cout<<"\n\t\t7 : 查看学生反馈\n\t\t8 : 退        出"<<endl;
		cout<<"_______________________________________________________________________________"<<endl;
		cout<<"\t请选择 : ";
		int choice; cin>>choice;
		switch(choice){
			case 1:
				ad.manageStudent( );
				break;
			case 2:
				ad.manageTeacher( );
				break;
			case 3:
				ad.manageGrade( );
				break;
			case 4:
				ad.manageCourse();
				break;
			case 5:
				ad.manageScore( );
				break;
			case 6:
				ad.handleChooseCourse( );
				break;
			case 7:
				ad.broseComplaint();
				break;		   	
			case 8:
				cout<<"Logging out...[admin]";
				return 0;
			default : cout<<"Select valid choice : ";
		}
		cout<<"\tEnter any to continue...\n";
		setbuf(stdin, NULL);cin.get( );
	}
	return 0;
}
//main函数入口
int main(){

	ManageCourse mc;
	Admin ad(&mc);
	ad.loadData();
	//  测试构造
	//STUDENT s(&mc, "s001");
	while(1){
		clrscr();title();
		cout<<"\n\t\t 1 : 学生端登录 "<<endl;
		cout<<"\t\t 2 : 管理员登录"<<endl;
		cout<<"\t\t 3 : 对操作保存"<<endl;
		cout<<"\t\t 4 : 退      出"<<endl;
		cout<<"\n\n\t\t请选择您的登录方式: ";

		int logChoice; cin>>logChoice;
		switch(logChoice){
			case 1: //student login
				student(ad);
				setbuf(stdin, NULL); cin.get( );
				break;
			case 2 : //admin login
				{ 
					int c,i=0,error=0;
					char pass[15];
					for(;error<3; ++error) {  
						cout<<"\n\t\t管理员密码：";
						setbuf(stdin, NULL);
						while((c=Getch()) != 13){ //13 回车ascii码
							pass[i]=c; i++; cout<<'*';
						}
						pass[i]='\0';

						string pwd(pass);
						if(pwd != ADMIN_PASS){ 
							i=0; memset(pass, 0x00, sizeof(pass));
						}else{
							admin(ad); break;
						} 
					}
					if(error>=3) cerr<<"\n登录失败...";
					setbuf( stdin, NULL);cin.get();
				} 
				break;
			case 3 :
				ad.saveData( );
				break;
			case 4 :
				cout<<"Terminating...\n"; usleep(1000); exit(0);
			default:
				cout <<"Invalid choice : "; cin.get();
		}
	}
	return 0;
}

