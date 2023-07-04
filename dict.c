#define _CRT_SECURE_NO_WARNINGS
#include "dict.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#define SIZE 10


int main() {
	//设置编码格式
	SetConsoleOutputCP(65001);
	getWord();

	/*for (int i = 0; i < SIZE; i++)
	{
		printf("%s", list[i].word);
		printf("%s", list[i].trans);
	}*/
	char* word = (char*)malloc(sizeof(char) * 1024);
	char* trans = (char*)malloc(sizeof(char) * 1024);
	int index = 0;
	while (1) {
		memset(word, 0, 1024);
		memset(trans, 0, 1024);
		scanf("%s", word);
		if (!strcmp(word, "comm=exit")) {
			break;
		}
		if (*word >= 'a' && *word <= 'z') {
			index = *word - 'a';
		}
		else {
			index = 26;
		}
		if (!searchWord(word, trans, index)) {
			printf("%s\n", trans);
		}
		else {
			printf("未找到单词");
		}


	}
	free(word);
	free(trans);
	destroy();
	return 0;
}

int getWord() {
	FILE* fp = fopen("D:/dict.txt", "r");
	if (!fp) {
		printf("读取文件失败！");
		return -1;
	}

	list = (dict*)malloc(sizeof(dict) * SIZE);
	char* temp = (char*)malloc(sizeof(char) * 1024);
	position = (pos*)malloc(sizeof(pos) * 27);
	int index = 0;

	position[0].start = 0; //记录a的索引
	position[0].end = 0;
	int idx = 0; //字符对应的索引下标
	char flag = 'a'; //记录当前索引标志位
	while (!feof(fp)) {

		memset(temp, 0, 1024);
		fgets(temp, 1024, fp);
		//去掉\n
		temp[strlen(temp) - 1] = 0;
		list[index].word = (char*)malloc(strlen(temp));
		//#a\n\0
		strcpy(list[index].word, &temp[1]);
		//创建索引
		if (idx != 26) { //判断单词首字母
			if (list[index].word[0] == flag) {
				position[idx].end++;
			}
			else {
				idx++;
				position[idx].start = position[idx - 1].end;
				position[idx].end = position[idx - 1].end+1;
				flag++;
			}
		}

		memset(temp, 0, 1024);
		fgets(temp, 1024, fp);
		//Trans:art. 一：字母A\n
		temp[strlen(temp) - 1] = 0;
		list[index].trans = (char*)malloc(strlen(temp)-5);
		strcpy(list[index].trans, &temp[6]);
		index++;
	}
	free(temp);
	fclose(fp);
	//记录中文的索引
	position[26].start = position[25].end;
	position[26].end = SIZE;
	return 0;
}

int searchWord(char* word, char* trans, int index) {
	if (!word || !trans) {
		return -1;
	}
	for (int i =position[index].start; i < position[index].end; i++)
	{
		//相等返回值是0
		if (!strcmp(list[i].word, word)) {
			strcpy(trans, list[i].trans);
			return 0;
		}
	}

	return 1;
}

void destroy()
{
	if (!list) {
		return;
	}
	if (position) {
		free(position);
		position = NULL;
	}

	for (int i = 0; i < SIZE; i++)
	{
		free(list[i].word);
		free(list[i].trans);
	}
	free(list);
	list = NULL;
}
