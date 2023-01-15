#ifdef RUNTIME
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

void *malloc(size_t size)
{
	void *(*mallocp)(size_t size) = NULL;
	mallocp = dlsym(RTLD_NEXT, "malloc");
	char *ptr = mallocp(size);
	printf("malloc(%d) = %p\n", (int)size, ptr);
	return ptr;
}
void free(void *ptr)
{
	void (*freep)(void *) = NULL;
	freep = dlsym(RTLD_NEXT, "free");
	ir(!ptr)
		return;
	freep(ptr);
	printf("free(%p)\n", ptr);
}
#endif
