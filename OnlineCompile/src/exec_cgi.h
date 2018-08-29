#ifndef __EXECCGI_H__
#define __EXECCGI_H__

#include "http.h"

//保存用户代码的缓存区大小. 应尽量大，保证一次保存代码
enum {BUFF_SIZE=1024*4}; 

int ExecCgi(int sock, const char* method, char* path, const char* query_string); 

#endif   //__EXECCGI_H__
