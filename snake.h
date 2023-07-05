#pragma once

#define WIDTH 60
#define HEIGHT 20


struct BODY {
	int X;
	int Y;
};

struct SNAKE {
	int size;
	struct BODY body[WIDTH*HEIGHT];
}snake;

int food[2] = { 0 }; //food[0] 为x坐标，food[1]为y坐标

int dx = 0; //坐标偏移长度
int dy = 0;

//记录蛇尾坐标
int lx = 0;
int ly = 0;

void initFood();

void initSanke();

void showUI();

void playGame();

//创建墙
void initWall();