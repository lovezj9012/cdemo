#define _CRT_SECURE_NO_WARNINGS //解决c4996错误，这个宏定义放在文件第一行
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable:4996) //解决c4996错误
#pragma warning(disable:6031)

//宏定义常量
#define PI 3.1415926


void circle() {
	//常量 PI
	//const float PI = 3.1415926;

	//在定义局部变量时可以在数据类型前面加auto，也可以不加
	auto float r = 3;
	float s = PI * r * r; //圆的面积
	float l = 2 * PI * r; //圆的周长
	//占位符 %f 表示输出一个浮点型 float，默认保留六位小数
	printf("π：%f\n", PI);
	printf("圆的面积：%f\n", s);
	printf("圆的面积(保留2位小数)：%.2f\n", s);
	printf("圆的周长：%f\n", l);
}

void binaryData() {
	//在计算机定义数据类型，不能直接定义二进制
	//定义8进制数据 以0开头
	int a = 0123;
	//定义十六数据 以0x开头
	int b = 0x123;
	printf("十进制数据：%d\n", a);
	printf("八进制数据：%o\n", a); 
	printf("十六进制数据：%x\n", a);
	printf("十进制数据：%d\n", b);
	printf("八进制数据： %o\n", b);
	printf("十六进制数据：%x\n", b);

}

void buyVegetable() {
	//蔬菜价格
	const int price = 3;
	int weight;
	printf("请输入购买蔬菜重量：");
	scanf("%d", &weight);
	int sum = price * weight;
	printf("购买蔬菜共花费：%d\n", sum);
}

void printChar() {
	char a = 'a';
	char b[11] = "hello world"; //字符默认会以\0结尾，hello world占11个字符将\0的位置挤掉会输出乱码“烫烫****“
	
	printf("%c\n", a);
	printf("%s\n", b);

	//占位符 表示输出一个字符遇到\0停止
	char* c = "hello\0 world";
	printf("%s\n", c); //输出结果是hello

	int d = 10;
	//左对齐
	printf("====%-5d=====\n", d);
	//左边补零
	printf("====%05d=====\n", d);


	printf("%d\n", 10 / 20);

	/*int e, f;
	scanf("%3d%d", &e, &f);
	printf("%d\t%d\n", e, f);*/

	/*char ch;
	ch = getchar();
	putchar(ch);*/

	
}


void operatorNum() {
	int a = 10;
	/*
	a++ 后自增
	++a 前自增
	前自增是在表达式之前进行++操作后在进行表达式计算
	后自增是先进行表达式计算，在进行++操作
	*/

	//int b = ++a * 10;
	int b = a++ * 10;
	printf("%d\n", b);
	printf("%d\n", a);

	int c = 10;
	printf("%d\n", c = ++a < b * 10);
	printf("a=%d\n", a);
	printf("b=%d\n", b);
	printf("c=%d\n", c);
	
}

void gotomain() {
	printf("hello world1\n");
	printf("hello world2\n");
	goto FLAG;
	printf("hello world3\n");
	printf("hello world4\n"); 
	FLAG:
	printf("hello world5\n");
	printf("hello world6\n");



FLAGERR:
	printf("hello goto\n");
	goto FLAGERR;
}

void towArray() {
	//int arr[2][3] = {{1,2,3},{4,5,6}};
	//int arr[2][3] = { 1,2,3,4,5,6 };
	int arr[][3] = { 1,2,3,4,5,6 };

	for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++)
	{
		for (int j = 0; j < sizeof(arr[0])/sizeof(arr[0][0]); j++)
		{
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}


	int arrStudent[5][3] = {
		{60,80,90},
		{90,100,80},
		{60,80,70},
		{60,60,60},
		{50,90,30}
	};

	

	int row = sizeof(arrStudent) / sizeof(arrStudent[0]);
	int col = sizeof(arrStudent[0]) / sizeof(arrStudent[0][0]);
	for (int i = 0; i < row; i++)
	{
		int sum = 0;
		for (int j = 0; j < col; j++)
		{
			sum += arrStudent[i][j];
			
		}
		printf("第%d名学生总成绩:%d 平均成绩:%d\n", (i + 1), sum, sum / col);
		
	}

	for (int i = 0; i < col; i++)
	{
		int subSum = 0;
		for (int j = 0; j < row; j++)
		{
			subSum += arrStudent[i][j];
		}
		printf("学生学科总成绩:%d \n",  subSum);
	}

}

void threeArr() {
	//三维数组 数组名 [层][行][列]

	int arr[2][3][4] = {
		{
			{1,2,3,4},
			{2,3,4,5},
			{3,4,5,6}
		},
		{
			{4,5,6,7},
			{5,6,7,8},
			{6,7,8,9}
		}
	};

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int m = 0; m < 4; m++)
			{
				printf("%d\t", arr[i][j][m]);
			}
			printf("\n");
		}
		printf("\n");
	}
}


void getsMethod() {
	char ch[10];
	//gets接受字符串可以带空格
	//gets(ch);

	//scanf通过正则表达式也可以获取带空格字符串
	//scanf("%[^\n]", ch);

	//fgets可以接收空格
	fgets(ch, sizeof(ch), stdin);

	printf("%s\n", ch);
}

void putsMethod() {
	char ch[] = "hello world";
	//puts可以输出空格,自带换行,遇到\0结束
	//puts(ch);
	//puts("hello\0 world");

	//fputs 不会自动换行
	fputs(ch, stdout);
}


void twoColor() {

	//随机数种子
	srand((unsigned int)time(NULL));

	int arr[6] = { 0 };
	int len = sizeof(arr) / sizeof(arr[0]);

	
	int j;

	//双色球 红球6 蓝球1 红球1-32 蓝球 1-16
	for (int m = 0; m < 10; m++)
	{
		int flag = 0;

		for (int i = 0; i < len; i++)
		{
			int value = rand() % 32 + 1; //取值范围1-32

			//去重
			for (j = 0; j < flag; j++)
			{
				if (value == arr[j]) {
					i--;
					break;
				}
			}

			if (j == flag) {
				arr[i] = value;
				flag++;
			}

		}

		for (int k = 0; k < len; k++)
		{
			printf("%d \t", arr[k]);
		}
		int blue = rand() % 16 + 1;
		printf("%d \n", blue);

		
	}
	printf("sizeof(char*): %lld", sizeof(char*));
}

//移除字符串空格
void remove_space(char* ch) {
	printf("%lld\n", sizeof(ch)); //数组作为函数参数，退化为指针丢失精度、
	char* front = ch; 
	char* record = ch;

	while (*front) {
		if (*front != ' ') {
			*record = *front;
			record++;
		}
		front++;
	}
	*record = 0;
}

void my_strcpy01(char* dest, char* ch)
{
	int i = 0;
	//while (ch[i] != '\0');
	//while (ch[i] != 0);
	while (ch[i])
	{
		dest[i] = ch[i];
		i++;
	}
	dest[i] = 0;
}
void my_strcpy02(char* dest, char* ch)
{
	int i = 0;
	while (*(ch + i))
	{
		*(dest + i) = *(ch + i);
		i++;
	}
	*(dest + i) = 0;
}
void my_strcpy03(char* dest, char* ch)
{
	while (*ch)
	{
		*dest = *ch;
		dest++;//指针+1  相当于指向数组下一个元素  内存地址变化了sizeof(char)
		ch++;
	}
	*dest = 0;
}
void my_strcpy(char* dest, char* ch)
{
	while (*dest++ = *ch++);
}


void copyStr() {
	//字符串拷贝
	char ch[] = "hello world";
	char dest[100];

	my_strcpy(dest, ch);
	printf("%s\n", dest);
}

char* findStrByChar(char* str, char* ch) {
	char* src = str; //用于循环遍历的指针
	char* rsrc = str;//记录每次相同的首地址
	char* find = ch;
	
	while (*src) {
		rsrc = src;
		while (*src == *find && *src != '\0') {
			src++;
			find++;
		}
		if (*find == '\0') {
			return rsrc;
		}
		//回滚
		src = rsrc;
		find = ch;
		src++;
	}
	return NULL;
}

//查找字符串
void findStr() {
	char str[] = "hello world";
	char* p = findStrByChar(str, "llo");
	printf("%s\n", p);
}

//查找字符串出现次数
void findStrCount() {

	char* str = "abcd13423131abcd13412342abcd";
	char* ch = "abcd";
	char* p =findStrByChar(str, ch);
	int count = 0;
	while (p != NULL) {
		count++;
		p += strlen(ch);
		p = findStrByChar(p, ch);
	}
	printf("%s出现的次数:%d\n", ch, count);
}


void countStrLen() {
	char ch[] = "      hello world    ";
	char* p = ch;
	int count = 0;
	char result[100] = { '\0'};
	int i = 0;
	int j = 0;
	while (*p!='\0') {
		if (*p != ' ') {
			count++;
			result[j] = ch[i];
			j++;
		}
		p++;
		i++;
	}
	printf("%s去除空格后：%s,字符个数：%d\n", ch, result, count);
}

//统计字符出现的次数
void countStrCount() {
	char* ch = "abdskjfkduiudiuaihddjhdgabadfadborioweiewoioe";
	int arr[26] = {0}; //用于统计26个字符出现的个数

	for (int i = 0; i < strlen(ch); i++)
	{
		arr[ch[i] - 'a']++;
	}

	for (int j = 0; j < sizeof(arr)/sizeof(arr[0]); j++)
	{
		if (arr[j] != 0) {
			printf("字母%c出现次数：%d\n", (j+'a'), arr[j]);
		}
	}
}

void printatoi() {
	char ch[] = "   -1232 456abc";
	int i = atoi(ch);
	printf("%d\n", i);
}


struct student {
	char* name;
	int age;
	int* scores;
	char* addr;
};

void structPoint() {
	struct student stu;

	stu.name = (char*)malloc(sizeof(char) * 21);
	if (stu.name) {
		strcpy(stu.name, "张三");
	}
	stu.age = 25;
	stu.scores = (int*)malloc(sizeof(int) * 3);
	stu.scores[0] = 70;
	stu.scores[1] = 80;
	stu.scores[2] = 90;
	stu.addr = (char*)malloc(sizeof(char) * 51);
	if (stu.addr) {
		strcpy(stu.addr, "北京市");
	}

	printf("%s\n", stu.name);
	printf("%d\n", stu.age);
	printf("%d\n", stu.scores[0]);
	printf("%d\n", stu.scores[1]);
	printf("%d\n", stu.scores[2]);
	printf("%s\n", stu.addr);

	free(stu.name);
	free(stu.scores);
	free(stu.addr);

}

void structPoint2() {
	struct student* p = (struct student*)malloc(sizeof(struct student) * 3);

	//给结构体成员开辟空间
	for (int i = 0; i < 3; i++)
	{
		
		if (p) {
			//指针操作方式
			//(p+i)->name = (char*)malloc(sizeof(char) * 21);
			p[i].name = (char*)malloc(sizeof(char) * 21);
			(p + i)->scores = (int*)malloc(sizeof(int) * 3);
			p[i].addr= (char*)malloc(sizeof(char) * 51);
		}
		
	}

	for (int i = 0; i < 3; i++)
	{
		if (p)
			scanf("%s%d%d%d%d%s", p[i].name, &p[i].age, &p[i].scores[0], &p[i].scores[1], &p[i].scores[2], p[i].addr);
	}

	for (int i = 0; i < 3; i++)
	{
		if (p)
			printf("%s %d %d %d %d %s\n", (p + i)->name, p[i].age, p[i].scores[0], p[i].scores[1], p[i].scores[2], p[i].addr);
	}
	//释放空间
	for (int i = 0; i < 3; i++)
	{
		free(p[i].name);
		free(p[i].scores);
		free(p[i].addr);
	}
	free(p);

}

int readFile() {
	FILE* fp = fopen("D:/writer.txt", "r");
	if (fp == NULL) {
		printf("打开文件失败！");
		return -1;
	}
	char c;
	while ((c = fgetc(fp))!= EOF){
		printf("%c", c);
	}
	return 0;
}

//读取中文必须设置文本为ansi
int readFiles() {
	FILE* fp = fopen("D:/writer.txt", "r");
	if (fp == NULL) {
		printf("打开文件失败！");
		return -1;
	}
	char* p = (char*)malloc(sizeof(char) * 100);
	
	while (!feof(fp)) {
		memset(p, 0, 100);
		fgets(p, 100, fp);
		printf("%s", p);
	}
	return 0;
}

int writerFile() {
	FILE* fp = fopen("D:/a.txt", "w");

	if (fp==NULL) {
		printf("打开文件失败！");
		return -1;
	}
	char c;
	while (1) {
		scanf("%c", &c);
		if (c == "@") {
			break;
		}
		int result = fputc(c, fp);
		printf("%c", result);
	}

	/*for (int i = 'a'; i < 'z'; i++)
	{
		fputc(i, fp);
	}*/

	fflush(fp);
	fclose(fp);
	return 0;
}

int writerFiles() {
	FILE* fp = fopen("D:/writer.txt", "w");
	if (!fp) {
		printf("打开文件失败！");
		return -1;
	}

	/*char ch[] = "你是谁！";

	fputs(ch, fp);*/
	char  ch[100];
	while (1) {
		scanf("%s", ch);
		
		if (!strcmp(ch, "comm=exit")) {
			break;
		}
		strcat(ch, "\n");
		fputs(ch, fp);
	}

	fclose(fp);

	return 0;

}

int writerFiles2() {
	FILE* fp = fopen("D:/writer.txt", "w");
	if (!fp) {
		printf("打开文件失败！");
		return -1;
	}

	char* p = (char*)malloc(sizeof(char) * 1024);
	while (1) {
		memset(p, 0, 1024);
		//scanf("%s", p);
		scanf("%[^\n]", p);
		getchar(); //接受回车换行符号
		if (!strcmp(p, "comm=exit")) {
			break;
		}
		strcat(p, "\n");
		fputs(p, fp);
	}
	free(p);
	fclose(fp);
	return 0;
}

enum opt {
	add,
	sub,
	mult,
	dive
};

int writerOper() {
	FILE* fp = fopen("D:/opr.txt", "w");
	if (!fp) {
		printf("打开文件失败！");
		return -1;
	}

	srand((unsigned int)time(NULL));
	int a, b;
	char c;
	char* p = (char*)malloc(sizeof(char) * 20);
	for (int i = 0; i < 20; i++)
	{
		a = rand() % 10 + 1;
		b = rand() % 10 + 1;
		switch (rand() % 4)
		{
		case add:
			c = '+';
			break;
		case sub:
			c = '-';
			break;
		case mult:
			c = '*';
			break;
		case dive:
			c = '/';
			break;
		default:
			break;
		}
		memset(p, 0, 20);
		sprintf(p,"%d%c%d=\n", a, c, b);
		fputs(p, fp);

	}
	free(p);
	fclose(fp);

	

	return 0;
}

int calcOprResult() {
	FILE* fp = fopen("D:/opr.txt", "r");
	FILE* fp1 = fopen("D:/oprResult.txt", "w");
	if (!fp || !fp1) {
		printf("操作文件失败！");
		return -1;
	}
	char* ch = (char*)malloc(sizeof(char) * 20);
	int a, b,sum=0;
	char c;
	while (!feof(fp)) {
		memset(ch, 0, 20);
		fgets(ch, 20, fp);
		sscanf(ch, "%d%c%d=", &a, &c, &b);
		switch (c)
		{
		case '+':
			sum = a + b;
			break;
		case '-':
			sum = a - b;
			break;
		case '*':
			sum = a * b;
			break;
		case '/':
			sum = a / b;
			break;
		default:
			break;
		}
		memset(ch, 0, 20);
		sprintf(ch, "%d%c%d=%d\n", a, c, b, sum);
		fputs(ch, fp1);
	}
	free(ch);
	fclose(fp);
	fclose(fp1);
	return 0;
}

int main01(int argc, char* argv[]) {
	if (argc < 3) {
		printf("参数错误！");
		return -1;
	}
	FILE* fp = fopen(argv[1], "rb");
	FILE* fp1 = fopen(argv[2], "wb");
	if (!fp || !fp1) {
		return -1;
	}
	char* p = (char*)malloc(sizeof(char) * 1024);
	int count = 0;
	while (!feof(fp)) {
		memset(p, 0, sizeof(char) * 1024);
		
		count =fread(p, sizeof(char), 1024, fp);
		fwrite(p, sizeof(char), count, fp1);
	}
	free(p);
	fclose(fp);
	fclose(fp1);
	return 0;
}

int main02() {

	//circle();
	//binaryData();
	//buyVegetable();
	//printChar();
	//operatorNum();
	//gotomain();
	//towArray();
	//threeArr();
	//getsMethod();

	//putsMethod();
	//twoColor();
	/*char ch [] = "   h e ll o w or    ld   ";
	remove_space(ch);
	printf("%s\n", ch);*/

	//copyStr();
	
	//findStr();

	//findStrCount();

	//countStrLen();

	//countStrCount();

	//printatoi();

	//structPoint();

	//structPoint2();
	//readFile();
	writerFile(); //error

	//readFiles();

	//writerFiles();
	//writerFiles2();

	//writerOper();

	//calcOprResult();


	system("pause");
	return 0;
}