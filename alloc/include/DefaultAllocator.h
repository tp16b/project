#pragma once
#include "Allocator.h"
//#include "TraceLog.h"

///////////////////////////////////////////////////////////////////////
//二级空间配置器

template <bool threads, int inst>
class __DefaultAllocTemplate
{
public:
	// 65	72  -> index=8
	// 72	79
	static size_t FREELIST_INDEX(size_t n){
		return ((n + __ALIGN-1)/__ALIGN - 1);
	}

	// 65	72	-> 72
	// 72	79
	static size_t ROUND_UP(size_t bytes)  {
		return (((bytes) + __ALIGN-1) & ~(__ALIGN - 1));
	}
	
	static void* ChunkAlloc(size_t size, size_t& nobjs);//获取大块内存	
	static void* Refill(size_t bytes);                  //填充自由链表	
	static void* Allocate(size_t n);                    //分配返回小内存块	
	static void Deallocate(void* p, size_t n);          //管理回收内存

private:
	enum {__ALIGN = 8 };
	enum {__MAX_BYTES = 128 }; 
	enum {__NFREELISTS = __MAX_BYTES/__ALIGN };

	union Obj{
		union Obj* _freelistlink;
		char client_data[1];    /* The client sees this.  */
	};

	// 自由链表
	static Obj* _freelist[__NFREELISTS];

	// 内存池
	static char* _startfree;
	static char* _endfree;
	static size_t _heapsize;
};

//__DefaultAllocTemplate成员初始化
template <bool threads, int inst>
typename __DefaultAllocTemplate<threads, inst>::Obj*
__DefaultAllocTemplate<threads, inst>::_freelist[__NFREELISTS] = {0};

// 内存池
template <bool threads, int inst>
char* __DefaultAllocTemplate<threads, inst>::_startfree = NULL;

template <bool threads, int inst>
char* __DefaultAllocTemplate<threads, inst>::_endfree = NULL;

template <bool threads, int inst>
size_t __DefaultAllocTemplate<threads, inst>::_heapsize = 0;


void Test_Alloc3();