#include<iostream>
#include<time.h>
using namespace std;


//求方幂模，求解res，计算res=g^x mod p
int ModularExponent(int g, int x, int p)
{//计算g^x mod p
	int res = 1;
	for (int i = 0; i < x; i++)
	{
		res = res*g%p;
	}
	return res;
}

//计算离散对数，求x，条件：a=g^x mod p
int dlog(int a, int g, int p) 
{//a为余数，g为底数，模p
	int x = 1, y = 1;
	y = y*g%p;
	while (a!=y&&x<p)
	{
		x++;
		y = y*g%p;
	}
	return x;
}

//sherwood算法变换，求a的离散对数x，先转换为求c的离散对数，最后变换成求a的离散对数
//好处：当要求第三方计算时，能够不使原始数据信息泄露
int dlogRH(int a, int g, int p)
{
	srand((unsigned)time(NULL));
	int r = 0 + rand() % (p - 2);
	int b = ModularExponent(g, r, p);	//求指数为r时的模
	int c = b*a%p;	//变换求c的离散对数
	int y = dlog(c, g, p);

	return (y - r) % (p - 1);	//因为离散对数是循环群，需要模（p-1）
}

void main()
{
	cout << dlog(3, 2, 5) << endl;
	cout << ModularExponent(3, 2, 5) << endl;
	cout << dlogRH(3, 2, 5)<<endl;	//sherwood算法计算，结果和dlog计算一样
	system("pause");
}
