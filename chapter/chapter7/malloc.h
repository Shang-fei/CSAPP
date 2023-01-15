#define malloc(size) mymalloc(size)
#define free(size) myfree(size)

void *mymalloc(size_t size);
void myfree(void *ptr);
