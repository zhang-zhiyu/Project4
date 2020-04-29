#define _CRT_SECURE_NO_WARNINGS；
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include<random>
using namespace std;
int num;//需要题目数量；
int symbol_type[4] = { 0,0,0,0 };//需要符号类型标志；
int maxnum;//希望题目中出现的最大值；
int brackets;//题目中是否需要括号的标志；
int decimal;//题目是整数还是小数的标志；
int style;//输出形式标志；
int number_int[3];//题目中出现的整数；
float number_float[3];//题目中出现的小数；
char symbol[2];//题目中出现的运算符；
FILE *fp;//需要输出的文件；
/*用户设置函数*/
void start() {
	cout << "请输入需要多少道题目：\n";
	cin >> num;
	cout << "需要+请输入1，否则2\n";
	cin >> symbol_type[0];
	cout << "需要-请输入1，否则2\n";
	cin >> symbol_type[1];
	cout << "需要*请输入1，否则2\n";
	cin >> symbol_type[2];
	cout << "需要/请输入1，否则2\n";
	cin >> symbol_type[3];
	cout << "希望算式中出现的最大数值\n";
	cin >> maxnum;
	cout << "需要括号请输入1，否则2\n";
	cin >> brackets;
	cout << "需要整数请输入1，小数输入2\n";
	cin >> decimal;
	cout << "需要输出到文件请输入1，打印输入2\n";
	cin >> style;
}

/*取随机整数或小数函数*/
void randnumber() {
	if (decimal == 1) {
		for (int i = 0; i < 3; i++) {
			number_int[i] = rand() % (maxnum)+1;
		}
	}
	if (decimal == 2) {
		for (int i = 0; i < 3; i++) {
			number_float[i] = rand() / (double)(RAND_MAX / maxnum);
		}
	}
}
/*取随机运算符函数*/
void randsymbol() {
	int j = 0;
	int flge;
	while (j < 2) {
		 flge= rand() %4;
		switch (flge) {
		case 0:
			if (symbol_type[0] == 1) {
				symbol[j] = '+';
				j++;
			}
			break;
		case 1:
			if (symbol_type[1] == 1) {
				symbol[j] = '-';
				j++;
			}
			break;
		case 2:
			if (symbol_type[2] == 1) {
				symbol[j] = '*';
				j++;
			}
			break;
		case 3:
			if (symbol_type[3] == 1) {
				symbol[j] = '/';
				j++;
			}
			break;
		}
	}
}

/*不含括号的题目生成函数*/
void create_expression1(int i) {
	if (decimal == 1) {
		printf("%d. ", i);
		printf("%d %c %d %c %d= ", number_int[0], symbol[0], number_int[1], symbol[1], number_int[2]);
	}
	if (decimal == 2) {
		printf("%d. ", i);
		printf("%.2f %c %.2f %c %.2f= ", number_float[0], symbol[0], number_float[1], symbol[1], number_float[1]);
	}
}

/*含括号的题目生成函数*/
void create_expression2(int i) {
	int brackets_place = rand() % 2;
	if (brackets_place == 0) {
		if (decimal == 1) {
			printf("%d. ", i);
			printf("( %d %c %d ) %c %d = ", number_int[0], symbol[0], number_int[1], symbol[1], number_int[2]);
		}
		if (decimal == 2) {
			printf("%d. ", i);
			printf("( %.2f %c %.2f ) %c %.2f = ", number_float[0], symbol[0], number_float[1], symbol[1], number_float[1]);
		}
	}
	if (brackets_place == 1) {
		if (decimal == 1) {
			printf("%d. ", i);
			printf("%d %c ( %d %c %d ) = ", number_int[0], symbol[0], number_int[1], symbol[1], number_int[2]);
		}
		if (decimal == 2) {
			printf("%d. ", i);
			printf("%.2f %c ( %.2f %c %.2f ) = ", number_float[0], symbol[0], number_float[1], symbol[1], number_float[1]);
		}
	}
}

/*文件里生成题目函数*/
void create_expression3(int i) {
	fprintf(fp, "%d. ", i);
	if (brackets == 1) {
		int brackets_place = rand() % 2;
		if (brackets_place == 0) {
			if (decimal == 1) {
				fprintf(fp, "( %d %c %d ) %c %d = ", number_int[0], symbol[0], number_int[1], symbol[1], number_int[2]);
			}
			if (decimal == 2) {
				fprintf(fp, "( %.2f %c %.2f ) %c %.2f = ", number_float[0], symbol[0], number_float[1], symbol[1], number_float[1]);
			}
		}
		if (brackets_place == 1) {
			if (decimal == 1) {
				fprintf(fp, "%d %c ( %d %c %d ) = ", number_int[0], symbol[0], number_int[1], symbol[1], number_int[2]);
			}
			if (decimal == 2) {
				fprintf(fp, "%.2f %c ( %.2f %c %.2f ) = ", number_float[0], symbol[0], number_float[1], symbol[1], number_float[1]);
			}
		}
	}
	else {
		if (decimal == 1) {
			fprintf(fp, "%d %c %d %c %d= ", number_int[0], symbol[0], number_int[1], symbol[1], number_int[2]);
		}
		if (decimal == 2) {
			fprintf(fp, "%.2f %c %.2f %c %.2f= ", number_float[0], symbol[0], number_float[1], symbol[1], number_float[1]);
		}
	}
	fprintf(fp, "\n");
}
/*图形界面函数*/
void menu() {
	printf("                                       *****************************************               \n");
	printf("                                       **                                     **               \n");
	printf("                                       **       小学生四则运算题目生成器      **               \n");
	printf("                                       **                                     **               \n");
	printf("                                       **     下面请按照提示进行初始化设置    **               \n");
	printf("                                       **                                     **               \n");
	printf("                                       *****************************************               \n");
	printf("\n");
}
/*主函数*/
int main() {
	menu();
	start();
	if ((fp = fopen("D:\\zuoye.txt", "w")) == NULL)
	{
		printf("不能打开文件！\n");
		exit(0);
	}
	srand((unsigned)time(NULL));
	for (int j = 1; j <= num; j++) {
		randnumber();
		randsymbol();
		if (brackets == 1 && style == 2) {
			create_expression1(j);
			printf("\n");
		}
		if (brackets == 2 && style == 2) {
			create_expression2(j);
			printf("\n");
		}
		if (style == 1) {
			create_expression3(j);
		}
	}
	fclose(fp);
	return 0;
}