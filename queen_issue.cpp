#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define SUCCESS 1
#define FAIL 0
#define EMPTY -65536

int failNodeNum, sumNodeNum, N;
int *tryp, *array135, *array45, *arrayCol;

void alloc_array(int n)
{
	tryp = (int *)malloc(sizeof(int)*(n + 1));
	array135 = (int *)malloc(sizeof(int)*(n + 1));
	array45 = (int *)malloc(sizeof(int)*(n + 1));
	arrayCol = (int *)malloc(sizeof(int)*(n + 1));
}

void free_array()
{
	free(tryp);
	free(array135);
	free(array45);
	free(arrayCol);
}

void init(int *array, int n)//初始化集合，使之为空集.
{
	int i = 0;
	for (; i <= n; i++) {
		array[i] = EMPTY;
	}
}
void init_all(int n)
{
	init(tryp, n);
	init(array135, n);
	init(array45, n);
	init(arrayCol, n);
	failNodeNum = 0, sumNodeNum = 0;
}
//有多少个皇后，危险关系数组里就各自有多少个值。

int inArray(int i, int j)
//判断第i个皇后的位置(i,j)是否在危险位置里
{
	int i1 = 1;
	for (; i1 <= N; i1++)	//for(;i1<=i-1;i1++)
	{
		if (array135[i1] == (i + j) || array45[i1] == (j - i) || arrayCol[i1] == j) {
			return 1;
		}

		if (array135[i1] == EMPTY) 
		{
			return 0;
		}
	}
	return 0;
}


void insertArray(int i, int j)	//第i个皇后的位置(i,j)
{
	array135[i] = i + j;
	array45[i] = j - i;
	arrayCol[i] = j;
}

void popArray(int i)	//删除第i个皇后的危险关系
{
	array135[i] = EMPTY;
	array45[i] = EMPTY;
	arrayCol[i] = EMPTY;

}

int backtrace(int stepVegas)	//已经放好了i-->stepVegas个皇后，之后放stepVegas+1-->N个皇后。行
{
	int i = stepVegas + 1, j = 1;

	while (i <= N)   //当前行号小于N，棋盘大小
	{
		sumNodeNum++;	//搜索的结点总数
		for (; j <= N; j++)
		{
			if (!inArray(i, j))	//(i,j)不在列、45、135这些危险位置集合里-->safe j
			{
				insertArray(i, j);//放置皇后
				i++;	//寻找下一个皇后的位置
				j = 1;
				break;
			}
		}

		if (j>N)	//当前的皇后i没有安全的位置
		{
			if (i <= 1) {	/*回退到1号皇后时也没有找到合适位置，那么不能再回退了，此时回溯法失败，返回FAIL(这种情况在LV算法调用backtrace时发生，因为此时可能找不到一组解free(array45);)*/
				return FAIL;
			}
			else {
				failNodeNum++;	//回退的节点总数
				i--;		//从i-1的arrayCol[i]+1位置开始重新找i-1的位置。
				j = arrayCol[i] + 1;
				popArray(i);	//将对应数组值置为EMPTY,删除(i-1)th皇后的危险位置
			}
		}
	}

	return SUCCESS;

}

int QueensLV(int stepVages)
{
	int row = 1, col, nb;
	int j;

	while (row <= stepVages) {   //改进的LV算法，只随机放置stepVages个皇后
		nb = 0;
		j = 1;
		srand((unsigned)time(0));
		sumNodeNum++;
		for (; j <= N; j++) {		//为row行找一个随机的位置col(在所有open位置中选择一个)
			if (!inArray(row, j)) {
				nb++;
				if (((rand() % nb) + 1) == 1) {
					col = j;
				}
			}
		}
		if (nb>0) {	//存在合适的位置
			insertArray(row, col);
			tryp[row] = col;
		}
		else {	//nb=0,不存在合适的位置，返回
			return FAIL;
		}
		row++;
	}
	if (stepVages == N) {
		return SUCCESS;
	}

	int flag = backtrace(stepVages);
	return flag;

}


void Obstinate(int stepVages, int n)
{
	int flag = -1, m_stepVages = stepVages;
	do {
		init(tryp, n);
		init(array135, n);
		init(array45, n);
		init(arrayCol, n);
		flag = QueensLV(m_stepVages);
	} while (flag == 0);

}

int main()
{
	//用搜索的结点数来找最优的stepVegas（因为搜索的总结点数正比于执行时间）
	int best_sv = -1, tmp_sv;
	double tmp_rate, best_rate = -0.01;

	N = 12;
	for (; N <= 20; N++) {	//N-皇后的最优stepVages.

		alloc_array(N);
		best_sv = -1, best_rate = -0.01;

		tmp_sv = 1;
		for (; tmp_sv <= N; tmp_sv++) {
			init_all(N);
			Obstinate(tmp_sv, N);
			tmp_rate = (double)sumNodeNum;

			if (tmp_rate<best_rate || best_rate<0.0) {
				best_sv = tmp_sv;
				best_rate = tmp_rate;
			}
		}

		printf("当N=%d时，stepVages=%d.\n", N, best_sv);
		free_array();
	}
	system("pause");
	return 0;
}
