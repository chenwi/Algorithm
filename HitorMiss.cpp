#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;

double rand_num()
{//产生随机数函数

	double ran_double = rand() / (double)(RAND_MAX);
	return ran_double;
	
}

double rand_a_b(double a, double b)
{//产生a，b之间的随机数
	double rand_double = a + (b - a)*rand() / (RAND_MAX);
	return rand_double;

}

double fun(double x, double y)
{//函数x*x+y*y的值
	double temp;
	temp = x*x + y*y;
	return temp;
}

double fun1(double x)
{//求函数sqrt(1 - x*x)的值
	double temp;
	temp = sqrt(1 - x*x);
	return temp;
}

double fun_sin(double x)
{
	return sin(x);
}

double HitorMiss(double a, double b, double c, double d, double (*fun)(double))
{//四个参数，a,b;c,d;和函数指针fun
	double x, y;
	double M = 1e1;
	int m = 0;
		for (int i = 0; i < M; i++)
		{
			x = rand_a_b(a, b);
			y = rand_a_b(c, d);
			if (y <= fun(x))
				m++;
		}
	return (m / (M + 0.0)*(b - a)*(d - c));
}

void main()
{
	srand((unsigned)time(NULL));
	//double M = 1e1;	//循环次数
	//cout << M<<endl;
	//double x, y;
	//for (int j = 0; j < 8; j++)
	//{
	//	int m = 0;
	//	for (int i = 0; i < M; i++)
	//	{
	//		x = rand_num();
	//		y = rand_num();
	//		//y = x;
	//		if (y <= fun1(x))
	//			m++;
	//	}
	//	cout << "当n=" << M << "时，结果为：" << 4 * m / (M + 0.0) << endl;
	//	M *= 10;
	//}
	//cout << rand_a_b(2.5, 4.3);
	
	for (int i = 0; i < 5; i++)
	{
		cout << "通过概率计算sin（x）在[0，1]上积分值：" << HitorMiss(0, 1.0, 0, 0.85, fun_sin) << endl;
	}
	system("pause");
}

//多次循环的值	//计算x=y时结果
//for (int j = 0; j < 10; j++)
//{
//	int m = 0;
//	for (int i = 0; i < M; i++)
//	{
//		x = rand() / double(RAND_MAX);//产生0-1之间随机数
//		y = x;	//将x赋值给y
//		if (x*x + y*y <= 1)
//			m++;
//	}
//	cout << "当n=" << M << "时，结果为：" << 4 * m / (M + 0.0) << endl;
//	M *= 10;
//}

/*cout << m << endl;
double Pi = 4 * m /( M + 0.0);
cout << "PI:" << Pi << endl;*/