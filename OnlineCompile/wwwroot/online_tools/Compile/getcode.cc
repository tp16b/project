#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <string>

#include "common.h"

/*url编码方法*/
//static int URLEncode(const char* str, const int strSize,\
//char* result, const int resultSize)

/*url解码方法*/
//static int URLDecode(const char* str, const int strSize, \
//char* result, const int resultSize)
enum {BUFF_SIZE =1024*4 }; 

/*BUG    内存泄漏   待用智能指针处理*/
int GenerateEditFile( )
{ 
	char* buf = new char[BUFF_SIZE] ;//BUG 
	char* url_buf = new char[BUFF_SIZE] ; 
	if(GetQueryString(url_buf) < 0){ 
		std::cerr<<"GetQueryString failed\n";
		return 1;
	}

	std::cerr<<"[url:]"<<url_buf<<std::endl<<std::endl;
	//1. url_buf参数字符串 解码
	URLDecode(url_buf, strlen(url_buf), buf, BUFF_SIZE);  
	std::cerr<<"[url参数解码后, buf:]"<<buf<<std::endl<<std::endl;

	//2. 分割解完码的字符串参数,提取其中编辑正文，语言选项
	std::string handleStr(buf, strlen(buf));
	size_t opt_pos = handleStr.find("&program_option=");
	std::string option(handleStr, opt_pos+16);  //最后一参数默认到最后npos
	handleStr.erase(opt_pos);
	handleStr.erase(0,13);

	std::cerr<<"[分割后，code:]"<<handleStr<<std::endl;
	std::cerr<<"[分割后，option:]"<<option<<std::endl<<std::endl;

	//3. 创建临时编译文件
	int fd;
	if(option.compare("C") == 0){ 
		fd = open("/home/tp/project/web/wwwroot/online_tools/Compile/file/edit.c", \
				O_RDWR|O_CREAT|O_TRUNC, 0644);	

	}else if(option.compare("C++") == 0){ 
		fd = open("/home/tp/project/web/wwwroot/online_tools/Compile/file/edit.cc", \
				O_RDWR|O_CREAT|O_TRUNC, 0644);	

	}else if(option.compare("Python") == 0){ 
		fd = open("/home/tp/project/web/wwwroot/online_tools/Compile/file/edit.py", \
				O_RDWR|O_CREAT|O_TRUNC, 0644);	

	}else if(option.compare("Shell") == 0){ 
		fd = open("/home/tp/project/web/wwwroot/online_tools/Compile/edit.sh", \
				O_RDWR|O_CREAT|O_TRUNC, 0644);	

	}else{ 
		//...
	} 
	if( fd < 0) {
		std::cerr<<"[open code file failed]\n";
		return 1;
	}

	std::cerr<<"[this str will write to codefile:] "<<handleStr<<std::endl<<std::endl;
	//4. 写入临时编译文件
	ssize_t w = write(fd, handleStr.c_str( ), handleStr.size( ));
	if(w <= 0) { 
		std::cerr<<"[write to code file failed !]\n";
	}else{ 
		std::cerr<<"[write success!  w_size= "<<w<<"]"<<std::endl;
	}
	close(fd);
	delete[] url_buf;
	delete[] buf;

	return 0;
}

int main( )
{ 
	GenerateEditFile( );
//	test( );
	return 0;
}


