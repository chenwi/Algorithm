#include<iostream>
#include<set>
#include<cmath>
#include<ctime>
using namespace std;
#define PI 3.1415926
#define Size 1000
int uniform(set<int> X)//�Ӽ��������ѡһ����
{
	int m = rand() % X.size();
	set<int>::iterator iter = X.begin();
	for (int i = 0; i < m; iter++, i++);
	return *iter;
}
int SetCount(set<int> X)
{
	set<int> S;
	int a;
	while (S.find(a = uniform(X)) == S.end())//�Ҳ�����û���ظ�����
	{
		S.insert(a);
	}
	return (int)(2 * S.size()*S.size() / PI);
}

int main()
{
	set<int> X;
	srand((unsigned)time(NULL));
	//��ʼ�������Լ� sizeΪ1000
	for (int i = 0; i < Size; i++) {
		X.insert(i);
	}
	int n;
	for (n = 10; n <= 10000; n *= 10) {
		int Sum = 0;
		for (int i = 0; i < n; i++) {
			Sum += SetCount(X);
		}
		printf("n=%d%t �����Ӽ��Ĵ�С = %d\n", n, (Sum / n));
	}
	system("pause");
	return 0;
}
