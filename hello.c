#include <stdio.h>

//�궨�峣��
#define PI 3.1415926


void circle() {
	//���� PI
	//const float PI = 3.1415926;

	//�ڶ���ֲ�����ʱ��������������ǰ���auto��Ҳ���Բ���
	auto float r = 3;
	float s = PI * r * r; //Բ�����
	float l = 2 * PI * r; //Բ���ܳ�
	//ռλ�� %f ��ʾ���һ�������� float��Ĭ�ϱ�����λС��
	printf("�У�%f\n", PI);
	printf("Բ�������%f\n", s);
	printf("Բ�����(����2λС��)��%.2f\n", s);
	printf("Բ���ܳ���%f\n", l);
}

void binaryData() {
	//�ڼ���������������ͣ�����ֱ�Ӷ��������
	//����8�������� ��0��ͷ
	int a = 0123;
	//����ʮ������ ��0x��ͷ
	int b = 0x123;
	printf("ʮ�������ݣ�%d\n", a);
	printf("�˽������ݣ�%o\n", a); 
	printf("ʮ���������ݣ�%x\n", a);
	printf("ʮ�������ݣ�%d\n", b);
	printf("�˽������ݣ�%o\n", b);
	printf("ʮ���������ݣ�%x\n", b);

}

int main() {

	//circle();
	binaryData();
	
	return 0;
}