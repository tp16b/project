#ifndef __EXECCGI_H__
#define __EXECCGI_H__

#include "http.h"

enum {BUFF_SIZE=1024*4};

int ExecCgi(int sock, const char* method, char* path, const char* query_string); 

#endif   //__EXECCGI_H__
