#include<iostream>
using namespace std;

//����ģs=a^j mod p

/*�����㷨
��ʾa��b����Ȼ���cȡ��Ľ��*/
int power1(int a, int x, int p)
{
	int res = 1;
	for (int i = 0; i < x; i++)
	{
		res = res*a%p;
	}
	return res;
}


int power2(int a, int x, int p)
{
	int res = 1;
	a %= p;
	while (x){
		if (x & 1)//�ж�x�Ƿ�Ϊ����
			res = (res * a) % p;
		a = (a * a) % p;
		x >>= 1;//����һλ����ʾ����2
}
return res;
}



void main()
{
	cout << power2(3,3,7)<<endl;
	system("pause");

}