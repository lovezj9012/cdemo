#pragma once
#include <stdlib.h>

typedef struct DICT {
	char* word; //单词
	char* trans; //翻译
} dict;

typedef struct POSITION {
	int start;
	int end;
}pos;

dict* list=NULL;
pos* position = NULL;

//读取单词
extern int getWord();

//查找单词
extern int searchWord(char* word,char* trans,int index);

extern void destroy();
