#include<iostream>
#include<stdio.h>
#include<stdlib.h> 
#include<string.h> 
#include<time.h> 
#include<math.h> 
using namespace std;

//迭代次数
#define M 50
int n = 20;
int _count, head = 3;
int val[] = { 2, 17, 11, 1, 7, 15, 20, 3, 19, 14, 8, 5, 18, 10, 13, 6, 4, 12, 16, 9 };
int ptr[] = { 7, 12, 17, 0, 10, 18, 100, 16, 6, 5, 19, 15, 8, 2, 9, 4, 11, 14, 1, 13 };
int x = 16;//查找的数值

//--------------------------搜索函数-------------------------------
int search(int x, int i)
{
	_count = 1;
	while (x>val[i])
	{//迭代查找不大于x的最大位置
		i = ptr[i];
		_count ++;
	}
	return i;
}

//----------------------------A(x)算法------------------------------
int A(int x)
{
	return search(x, head);
}

//----------------------------D(x)算法------------------------------
int D(int x)
{
	int i = rand() % n + 1;
	int y = val[i];
	if (x > y)return search(x, ptr[i]);
	if (x < y)return search(head, x);
	return i;
}

//----------------------------B(x)算法------------------------------
int B(int x)
{
	int y, i = head;
	int max = val[i];
	int num = int(sqrt(n));//取根号n
	for (int j = 0; j < num; j++)
	{//找不大于x的最大y
		y = val[j];
		if (max < y&&y <= x)
		{
			i = j; max = y;
		}
	}
	return search(x, i);
}

//----------------------------C(x)算法------------------------------
int C(int x)
{//sherwood算法
	int y, i = head;
	int max = val[i];
	int num = int(sqrt(n));//取根号n
	for (int j = 0; j < num; j++)
	{//找不大于x的最大y
		int k = rand() % n + 1;//在n个数中随机选那根号n个数
		y = val[k];
		if (max < y&&y <= x)
		{
			i = k; max = y;
		}
	}
	return search(x, i);
}


//----------------------------主函数--------------------------------
void main()
{
	srand((unsigned)time(NULL));
	int count_A = 0, count_B = 0, count_C = 0, count_D = 0;//查找总次数
	int p_A = 0, p_B = 0, p_C = 0, p_D = 0;//记录的位置
	//算法A,D,B,C都计算M次，最后取平均
	for (int i = 0; i < M; i++)
	{
		p_A = A(x);
		count_A += _count;
	}
	for (int i = 0; i < M; i++)
	{
		p_D = D(x);
		count_D += _count;
	}
	for (int i = 0; i < M; i++)
	{
		p_B = B(x);
		count_B += _count;
	}
	for (int i = 0; i < M; i++)
	{
		p_C = C(x);
		count_C += _count;
	}

	cout << "A(x)算法找到的位置：" << A(x) << "  查找次数:" << count_A/M << endl;
	cout << "D(x)算法找到的位置：" << D(x) << "  查找次数:" << count_D/M << endl;
	cout << "B(x)算法找到的位置：" << B(x) << "  查找次数:" << count_B/M << endl;
	cout << "C(x)算法找到的位置：" << C(x) << "  查找次数:" << count_C/M << endl;
	system("pause");
}