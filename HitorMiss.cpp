#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;

double rand_num()
{//�������������

	double ran_double = rand() / (double)(RAND_MAX);
	return ran_double;
	
}

double rand_a_b(double a, double b)
{//����a��b֮��������
	double rand_double = a + (b - a)*rand() / (RAND_MAX);
	return rand_double;

}

double fun(double x, double y)
{//����x*x+y*y��ֵ
	double temp;
	temp = x*x + y*y;
	return temp;
}

double fun1(double x)
{//����sqrt(1 - x*x)��ֵ
	double temp;
	temp = sqrt(1 - x*x);
	return temp;
}

double fun_sin(double x)
{
	return sin(x);
}

double HitorMiss(double a, double b, double c, double d, double (*fun)(double))
{//�ĸ�������a,b;c,d;�ͺ���ָ��fun
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
	//double M = 1e1;	//ѭ������
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
	//	cout << "��n=" << M << "ʱ�����Ϊ��" << 4 * m / (M + 0.0) << endl;
	//	M *= 10;
	//}
	//cout << rand_a_b(2.5, 4.3);
	
	for (int i = 0; i < 5; i++)
	{
		cout << "ͨ�����ʼ���sin��x����[0��1]�ϻ���ֵ��" << HitorMiss(0, 1.0, 0, 0.85, fun_sin) << endl;
	}
	system("pause");
}

//���ѭ����ֵ	//����x=yʱ���
//for (int j = 0; j < 10; j++)
//{
//	int m = 0;
//	for (int i = 0; i < M; i++)
//	{
//		x = rand() / double(RAND_MAX);//����0-1֮�������
//		y = x;	//��x��ֵ��y
//		if (x*x + y*y <= 1)
//			m++;
//	}
//	cout << "��n=" << M << "ʱ�����Ϊ��" << 4 * m / (M + 0.0) << endl;
//	M *= 10;
//}

/*cout << m << endl;
double Pi = 4 * m /( M + 0.0);
cout << "PI:" << Pi << endl;*/