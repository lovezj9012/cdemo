#pragma once
#include <stdlib.h>

typedef struct DICT {
	char* word; //����
	char* trans; //����
} dict;

typedef struct POSITION {
	int start;
	int end;
}pos;

dict* list=NULL;
pos* position = NULL;

//��ȡ����
extern int getWord();

//���ҵ���
extern int searchWord(char* word,char* trans,int index);

extern void destroy();
