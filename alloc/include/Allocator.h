#pragma once

#include <iostream>
#include <unistd.h>
using namespace std;
//#include "TraceLog.h"
//一级空间配置器
typedef void(*HANDLE_FUNC)();
template <int inst> // inst为预留参数，方便以后扩展
class __MallocAllocTemplate 
{
private:
	/*定义函数指针类型成员，方便回调执行用户
	自定义的内存释放函数，该成员默认设置不执行*/
	static HANDLE_FUNC __malloc_alloc_oom_handler;

	static void* OOM_Malloc(size_t n){
		while (1){
			if (0 == __malloc_alloc_oom_handler){
				throw bad_alloc();
			}else{
				__malloc_alloc_oom_handler();  //释放内存
				usleep(3000);
				void* ret = malloc(n);
				if (ret)
					return ret;
			}
		}
	}
public:
	static void* Allocate(size_t n)
	{
		void *result = malloc(n);
		//malloc申请失败，执行OOM_Malloc再请求申请内存
		if (0 == result)
			result = OOM_Malloc(n);
		cout<<"申请成功!"<<endl;
		return result;
	}

	static void Deallocate(void *p, size_t /* n */)
	{
		free(p);
	}
	/*设置oom_malloc句柄函数，*/
	static HANDLE_FUNC SetMallocHandler(HANDLE_FUNC f)
	{
		HANDLE_FUNC old = f;
		__malloc_alloc_oom_handler = f;
		return old;
	}
};

template<int inst>
HANDLE_FUNC __MallocAllocTemplate<inst>::__malloc_alloc_oom_handler = 0;

//自定义的内存释放函数
static void FreeMemory()
{
	cout<<"执行用户自定义函数，开始释放内存..."<<endl;
}
void Test_Alloc1();

void Test_Alloc2();





