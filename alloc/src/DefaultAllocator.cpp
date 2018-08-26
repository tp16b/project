#include "DefaultAllocator.h"

#include <stdio.h>

//function：从内存池申请一大块内存
template <bool threads, int inst>
void* __DefaultAllocTemplate<threads, inst>::ChunkAlloc(size_t size, size_t& nobjs)
{
	size_t totalbytes = nobjs*size;
	size_t leftbytes = _endfree - _startfree;

	//a) 内存池中有足够内存
	if (leftbytes >= totalbytes){
		printf("内存池有足够的%lu个对象的内存块\n", nobjs);
		void* ret = _startfree;
		_startfree += totalbytes;
		return ret;

		//b) 内存池仅剩部分对象内存块
	}else if (leftbytes > size){
		nobjs = leftbytes/size;  /*保存能够使用对象块数*/
		totalbytes = size*nobjs;
		printf("内存池只有%lu个对象的内存块\n", nobjs);

		void* ret = _startfree;
		_startfree += totalbytes;
		return ret;

		//c) 内存池中剩余内存不足一个对象块大小
	}else{
		// 1.先处理掉内存池剩余的小块内存，将其头插到对应自由链表上
		if(leftbytes > 0){
			size_t index = FREELIST_INDEX(leftbytes);
			((Obj*)_startfree)->_freelistlink = _freelist[index];
			_freelist[index] = (Obj*)_startfree;
		}

		// 2.调用malloc申请更大的一块内存放入内存池
		size_t bytesToGet = totalbytes*2 + ROUND_UP(_heapsize>>4);
		_startfree = (char*)malloc(bytesToGet);

		printf("内存池没有内存，到系统申请%lubytes\n", bytesToGet);

		if (_startfree == NULL){	
			//3. malloc申请内存失败，内存池没有内存补给，到更大的自由链表中找
			size_t index = FREELIST_INDEX(size);
			for (; index < __NFREELISTS; ++index){
				//自由链表拿出一块放到内存池？？
				if (_freelist[index]){				
					_startfree = (char*)_freelist[index]; //BUG ??
					Obj* obj = _freelist[index];
					_freelist[index] = obj->_freelistlink;
					return ChunkAlloc(size, nobjs);  
				}
			}
			//逼上梁山，最后一搏. 若内存实在吃紧，则一级配置器抛异常结束
			_startfree = (char*)__MallocAllocTemplate<0>::Allocate(bytesToGet);
		}
		_endfree = NULL;  /*in case of exception.  ！！保证异常安全*/

		_heapsize += bytesToGet;
		_endfree = _startfree + bytesToGet;

		return ChunkAlloc(size, nobjs);
	}
}

template <bool threads, int inst>
void* __DefaultAllocTemplate<threads, inst>::Refill(size_t bytes)
{
	size_t nobjs = 20;   /*默认从内存池取20块对象，填充*/
	//从内存池中拿到一大块内存
	char* chunk = (char*)ChunkAlloc(bytes, nobjs);
	if (nobjs == 1)      /*只取到了一块*/
		return chunk;

	size_t index = FREELIST_INDEX(bytes);
	printf("返回一个对象，将剩余%lu个对象挂到freelist[%lu]下面\n", nobjs-1, index);

	Obj* cur = (Obj*)(chunk + bytes);
	_freelist[index] = cur;
	for (size_t i = 0; i < nobjs-2; ++i){
		Obj* next = (Obj*)((char*)cur + bytes);
		cur->_freelistlink = next;

		cur = next;
	}

	cur->_freelistlink = NULL;

	return chunk;
}

template <bool threads, int inst>
void* __DefaultAllocTemplate<threads, inst>::Allocate(size_t n)
{ 
	printf("二级空间配置器申请%lubytes\n", n);

	if (n > __MAX_BYTES)//调用一级空间配置器
		return __MallocAllocTemplate<0>::Allocate(n); 

	size_t index = FREELIST_INDEX(n);
	if (_freelist[index] == NULL){
		printf("freelist[%lu]下面没有内存块对象,需要到内存池申请\n", index);

		return Refill(ROUND_UP(n));//填充自由列表,向上取整

	}else{
		printf("freelist[%lu]取一个对象返回\n", index);

		Obj* ret = _freelist[index];
		_freelist[index] = ret->_freelistlink;
		return ret;
	}
}

//需要第二个参数，以此计算链表在freelist列表中对应下标
	template <bool threads, int inst>
void __DefaultAllocTemplate<threads, inst>::Deallocate(void* p, size_t n)
{
	if (n > __MAX_BYTES){
		__MallocAllocTemplate<0>::Deallocate(p, n);
	}else{
		size_t index = FREELIST_INDEX(n);
		printf("二级空间配置器释放对象，挂到freelist[%lu]下\n", index);
		//头插到链表上
		((Obj*)p)->_freelistlink = _freelist[index];
		_freelist[index] = (Obj*)p;
	}
}


//test函数
void Test_Alloc3()
{
	for(size_t i = 0; i < 20; ++i)
	{
		void* p = __DefaultAllocTemplate<false, 0>::Allocate(6);
		__DefaultAllocTemplate<false, 0>::Deallocate(p, 6);
	}

	__DefaultAllocTemplate<false, 0>::Allocate(6);
}

//////////////////////////////////////////////////////////////////
#ifdef __USE_MALLOC
typedef __MallocAllocTemplate<0> alloc;
#else
typedef __DefaultAllocTemplate<false, 0> alloc;
#endif


template<class T, class Alloc>
class SimpleAlloc 
{
	public:
		static T* Allocate(size_t n){ 
			return 0 == n? 0 : (T*) Alloc::Allocate(n * sizeof (T));
		}

		static T* Allocate(void){ 
			return (T*) Alloc::Allocate(sizeof (T));
		}

		static void Deallocate(T *p, size_t n){ 
			if (0 != n)
				Alloc::Deallocate(p, n * sizeof (T));
		}

		static void Deallocate(T *p){ 
			Alloc::Deallocate(p, sizeof (T));
		}
};
