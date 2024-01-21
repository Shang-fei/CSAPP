#include "cachelab.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <getopt.h>
#include <string.h>
#include <stdbool.h>

bool verbose;
static size_t s, S, E, b;
static char t[100];
static size_t hit_count, miss_count, eviction_count;

typedef struct {
	bool valid;
	int flag;
	int stamp;
}cache_line;

cache_line **cache = NULL;

void init_cache()
{
	cache = (cache_line **)malloc(sizeof(cache_line *) * S);
	for(int i=0 ; i<S ; i++){
		cache[i] = (cache_line *)malloc(sizeof(cache_line) * E);
		for(int line=0 ; line<E ; line++){
			cache[i][line].valid = false;
			cache[i][line].flag = -1;
			cache[i][line].stamp = -1;
		}
	}
}

void update_stamp()
{
	for(int i=0 ; i<S ; i++){
		for(int line=0 ; line<E ; line++){
			if(cache[i][line].valid == true){
				cache[i][line].stamp++;
			}
		}
	}
}

void update_cache(size_t address)
{
	size_t group = (address >> b) & ((-1U) >> (64-s));
	size_t tag = (address >> (b+s));
	ssize_t maxstamp = INT_MIN;
	size_t maxindex = 0;

	for(int i=0 ; i<E ; i++){
		if(cache[group][i].flag == tag){
			cache[group][i].stamp = 0;
			hit_count++;
			if(verbose)
				printf("hit ");
			return;
		}
	}
	for(int i=0 ; i<E ; i++){
		if(cache[group][i].valid == false){
			cache[group][i].valid = true;
			cache[group][i].stamp = 0;
			cache[group][i].flag = tag;
			miss_count++;
			if(verbose)
				printf("miss ");
			return;
		}
	}
	miss_count++;
	eviction_count++;
	for(int i=0 ; i<E ; i++){
		if(cache[group][i].stamp > maxstamp){
			maxstamp = cache[group][i].stamp;
			maxindex = i;
		}
	}
	cache[group][maxindex].flag = tag;
	cache[group][maxindex].stamp = 0;
	if(verbose)
		printf("miss eviction ");
	return;
}

void parse_trace()
{
	init_cache();
	
	FILE *fp = fopen(t, "r");
	if(fp == NULL){
		printf("fopen error");
		exit(-1);
	}
	char operation[2];
	size_t address;
	size_t size;
	while(fscanf(fp, "%s %lx,%ld", operation, &address, &size) >0){
		if(verbose)
			printf("%s %lx,%ld ", operation, address, size);
		switch(*operation){
			case 'M':
				update_cache(address);
				update_cache(address);
				break;
			case 'L':
				update_cache(address);
				break;
			case 'S':
				update_cache(address);
				break;
		}
		if(verbose)
			printf("\n");
		update_stamp();
	}
	fclose(fp);
	for(int i=0 ; i<S ; i++){
		free(cache[i]);
	}
	free(cache);
}
					
int main(int argc, char *argv[])
{
	int opt;
	hit_count = miss_count = eviction_count = 0;
	while((opt = (getopt(argc, argv, "vs:E:b:t:"))) != -1)
	{
		switch(opt)
		{
			case 'v':
				verbose = true;
				break;
			case 's':
				s = atoi(optarg);
				break;
			case 'E':
				E = atoi(optarg);
				break;
			case 'b':
				b = atoi(optarg);
				break;
			case 't':
				strcpy(t, optarg);
				break;
		}
	}
	
	if(s<=0 || E<=0 || b<=0 || t==NULL)
	        return -1;
	S = 1 << s;
	
	parse_trace();
    printSummary(hit_count, miss_count, eviction_count);
    
    return 0;
}
