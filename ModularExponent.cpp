#include<iostream>
using namespace std;

//求方幂模s=a^j mod p

/*朴素算法
表示a的b次幂然后对c取余的结果*/
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
		if (x & 1)//判断x是否为奇数
			res = (res * a) % p;
		a = (a * a) % p;
		x >>= 1;//右移一位，表示除以2
}
return res;
}



void main()
{
	cout << power2(3,3,7)<<endl;
	system("pause");

}