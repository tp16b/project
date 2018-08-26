#include "Allocator.h"

void Test_Alloc1()
{
	__MallocAllocTemplate<0>::SetMallocHandler(FreeMemory);
	void* p = __MallocAllocTemplate<0>::Allocate(128);
	__MallocAllocTemplate<0>::Deallocate(p, 128);
}
void Test_Alloc2()
{
	__MallocAllocTemplate<0>::SetMallocHandler(FreeMemory);

	void* p = __MallocAllocTemplate<0>::Allocate(0x7fffffff);
	__MallocAllocTemplate<0>::Deallocate(p, 40);
}
