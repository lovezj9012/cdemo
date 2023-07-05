#define _CRT_SECURE_NO_WARNINGS //���c4996��������궨������ļ���һ��
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <Windows.h>
#include <conio.h> //�û������޻����ַ�

#include "snake.h"


/*
* 1�������ߵĽṹ��
* 2����ʼ���ߺ�ʵ��
* 3����ʼ��Ϸ
*		�ߺ�ǽ��ײ
*		�ߺ�������ײ
*		�ߺ�ʳ����ײ
*			�������ʳ��
*			����������
*			��������
* 4����Ϸ����
*/

int main() {
	srand((size_t)time(NULL));

	initWall();

	//ȥ�����
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

	//�����β
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

	//�����ͷ�Ƿ���ײ�߽�
	while (snake.body[0].X >= 0 && snake.body[0].X < WIDTH && snake.body[0].Y >= 0 && snake.body[0].Y < HEIGHT) {
		//��ʾ����
		showUI();
		//���Ʒ���
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
			//����������
			if (snake.body[0].X == snake.body[i].X && snake.body[0].Y == snake.body[i].Y) {
				printf("ҧ���Լ��ˣ�");
				return;
			}
		}

		if (snake.body[0].X == food[0] && snake.body[0].Y == food[1]) {
			snake.size++;
			initFood(); //�Ե�ʳ�����������ʳ��
		}

		//��ȡ��β������
		lx = snake.body[snake.size - 1].X;
		ly = snake.body[snake.size - 1].Y;

		//�����ߵ����꣬�ߵĺ�һ�ڵ��������ǰһ�ڵ�����
		for (int i = snake.size-1; i >0; i--)
		{
			snake.body[i] = snake.body[i - 1];
		}
		//������ͷ������
		snake.body[0].X += dx;
		snake.body[0].Y += dy;
		
		Sleep(200);
		//�����һ�ε�����
		//system("cls");
		
	}
	printf("ײǽ�ˣ�");
		
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
