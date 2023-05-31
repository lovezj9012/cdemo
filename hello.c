#include <stdio.h>

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
	printf("八进制数据：%o\n", b);
	printf("十六进制数据：%x\n", b);

}

int main() {

	//circle();
	binaryData();
	
	return 0;
}