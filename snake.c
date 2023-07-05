#define _CRT_SECURE_NO_WARNINGS //解决c4996错误，这个宏定义放在文件第一行
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <Windows.h>
#include <conio.h> //用户接收无回显字符

#include "snake.h"


/*
* 1、定义蛇的结构体
* 2、初始化蛇和实物
* 3、开始游戏
*		蛇和墙碰撞
*		蛇和自身碰撞
*		蛇和食物碰撞
*			重新随机食物
*			蛇身体增长
*			分数增长
* 4、游戏结束
*/

int main() {
	srand((size_t)time(NULL));

	initWall();

	//去掉光标
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = sizeof(cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);

	initFood();
	
	initSanke();

	//showUI();
	playGame();

	getchar();

	return 0;
}

void initFood()
{
	
	food[0] = rand() % WIDTH;
	food[1] = rand() % HEIGHT;
}

void initSanke()
{
	snake.size = 2;
	snake.body[0].X = WIDTH / 2;
	snake.body[0].Y = HEIGHT / 2;

	snake.body[1].X = WIDTH / 2-1;
	snake.body[1].Y = HEIGHT / 2;

}

void showUI()
{

	COORD coord;

	//清空蛇尾
	coord.X = lx;
	coord.Y = ly;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	putchar(' ');

	for (int i = 0; i < snake.size; i++)
	{
		coord.X = snake.body[i].X;
		coord.Y = snake.body[i].Y; 
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		if (i == 0) {
			putchar('@');
		}
		else {
			putchar( '*');
		}
		
	}
	coord.X = food[0];
	coord.Y = food[1];
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	putchar('#');
	/*printf("@");
	printf("%d %d", coord.X, coord.Y);*/
}

void playGame()
{
	char key = 'D';
	char temp = ' ';

	//检查蛇头是否碰撞边界
	while (snake.body[0].X >= 0 && snake.body[0].X < WIDTH && snake.body[0].Y >= 0 && snake.body[0].Y < HEIGHT) {
		//显示界面
		showUI();
		//控制方向
		if (_kbhit()) {
			key = _getch();
		}

		switch (key)
		{
		case 'D': case 'd': dx = 1; dy = 0; break;
		case 'A': case 'a': dx = -1; dy = 0; break;
		case 'W': case 'w': dx = 0; dy = -1; break;
		case 'S': case 's': dx = 0; dy = 1; break;
		}

		for (int i = 1; i < snake.size; i++)
		{
			//蛇碰到自身
			if (snake.body[0].X == snake.body[i].X && snake.body[0].Y == snake.body[i].Y) {
				printf("咬到自己了！");
				return;
			}
		}

		if (snake.body[0].X == food[0] && snake.body[0].Y == food[1]) {
			snake.size++;
			initFood(); //吃掉食物后重新生成食物
		}

		//获取蛇尾的坐标
		lx = snake.body[snake.size - 1].X;
		ly = snake.body[snake.size - 1].Y;

		//更新蛇的坐标，蛇的后一节的坐标等于前一节的坐标
		for (int i = snake.size-1; i >0; i--)
		{
			snake.body[i] = snake.body[i - 1];
		}
		//更新蛇头的坐标
		snake.body[0].X += dx;
		snake.body[0].Y += dy;
		
		Sleep(200);
		//清除上一次的内容
		//system("cls");
		
	}
	printf("撞墙了！");
		
}

void initWall()
{
	for (int i = 0; i <= HEIGHT; i++)
	{
		for (int j = 0; j <= WIDTH; j++)
		{
			if (i == HEIGHT) {
				putchar('=');
			}else if (j == WIDTH) {
				putchar('=');
			}
			else {
				putchar(' ');
			}
		}
		putchar('\n');
	}
}
