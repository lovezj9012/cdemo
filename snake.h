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

int food[2] = { 0 }; //food[0] Ϊx���꣬food[1]Ϊy����

int dx = 0; //����ƫ�Ƴ���
int dy = 0;

//��¼��β����
int lx = 0;
int ly = 0;

void initFood();

void initSanke();

void showUI();

void playGame();

//����ǽ
void initWall();