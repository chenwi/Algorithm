#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;

#define PI 3.1415926

int set_count(int n)
{
	const int MAX = 100000;
	int arr[10000];
	int flag = 1, i = 0;
	
	while (flag)
	{
		arr[i] = int(rand() % n);
		for (int j = 0; j < i; j++)
			if (arr[i] == arr[j])
				flag = 0;		
		i++;
	}
	return i;
}

int evaluate_n(int n)
{
	int count = 0, tem = 0;
	//ÿ�������������10�Σ���ƽ��ֵ
	for (int i = 0; i < 10; i++)
	{
		tem = set_count(n);
		count += 2 * tem*tem / PI;
	}
	count /= 10;
	return count;
}

void main1()
{
	srand((unsigned)time(NULL));
	//int n=1000, i = 0;
	//int count = 0,tem=0;

	//for (i=0; i < 10; i++)
	//{
	//	tem = set_count(n);
	//	count += 2 * tem*tem / PI;
	//}
	//count /= 10;
	//cout << count << endl;
	int n = 100;
	for (int i = 0; i < 3; i++)
	{
		cout << "��n=" << n << "ʱ�����Ƽ��ϵ��ƣ�" << evaluate_n(n) << endl;
		n = n * 10;
	}
	system("pause");

}