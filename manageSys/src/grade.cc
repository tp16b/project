/*=====================================================
 *   Copyright(C) 2019   All rights reserved.
 * 
 *   文件名称：grade.cc
 *   创 建 者：tp    tp_16b@163.com
 *   创建日期：2019年01月04日
 *   描    述：
 ====================================================*/
#include "grade.h"


int ManageGrade::addGrade(const string& g_id, const string& depart, int num)
{ 
	contain_.insert(Grade(g_id, depart, num));
	return SUCCESS;
}

int ManageGrade::eraseGrade(const string& g_id)
{ 
	Ite it = findGrade( g_id);
	if( it == contain_.end( ))  return -1;

	contain_.erase(it);
	return SUCCESS;
}
int ManageGrade::changeGrade(const string& g_id)
{ 
	Ite it = findGrade( g_id);
	if( it == contain_.end( ))  return -1;

	contain_.erase(it);
	string id,depart;                                 
	int cnt;                                
	cout<<"\n\t输入班级id     : " ; cin>>id;      
	cout<<"\n\t输入班级系别   : " ; cin>>depart;    
	cout<<"\n\t输入班级人数   : " ; cin>>cnt;     
	contain_.insert(Grade(id, depart, cnt));
	return SUCCESS;
}
void ManageGrade::showGrade( ) 
{ 
	Ite it = contain_.begin( );
	cout<<"\n\t--------------------------------------------------------";
	cout<<endl<<"\t班级代号\t所属系别\t班级人数"<<endl;
	while( it != contain_.end( )){ 
		cout<<"\t"<<it->grade_id_<<"\t\t"<<it->department_<<"\t\t"<<it->member_num_<<endl;
		++it;
	}
	cout<<"\n\t--------------------------------------------------------"<<endl;
}



void ManageGrade::saveGrades(MYSQL& mysql)
{ 
	char sql_buf[ 64];
	for( auto& e: contain_){ 
		sprintf(sql_buf, "insert into grade values('%s','%s',%d)", e.grade_id_.c_str(),e.department_.c_str(), e.member_num_);

		if(mysql_real_query(&mysql, sql_buf, (unsigned long)strlen(sql_buf))){
			cerr << "mysql_real_query failure！" << endl;
		}
	}
}
