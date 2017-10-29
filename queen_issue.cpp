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

void init(int *array, int n)//��ʼ�����ϣ�ʹ֮Ϊ�ռ�.
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
//�ж��ٸ��ʺ�Σ�չ�ϵ������͸����ж��ٸ�ֵ��

int inArray(int i, int j)
//�жϵ�i���ʺ��λ��(i,j)�Ƿ���Σ��λ����
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


void insertArray(int i, int j)	//��i���ʺ��λ��(i,j)
{
	array135[i] = i + j;
	array45[i] = j - i;
	arrayCol[i] = j;
}

void popArray(int i)	//ɾ����i���ʺ��Σ�չ�ϵ
{
	array135[i] = EMPTY;
	array45[i] = EMPTY;
	arrayCol[i] = EMPTY;

}

int backtrace(int stepVegas)	//�Ѿ��ź���i-->stepVegas���ʺ�֮���stepVegas+1-->N���ʺ���
{
	int i = stepVegas + 1, j = 1;

	while (i <= N)   //��ǰ�к�С��N�����̴�С
	{
		sumNodeNum++;	//�����Ľ������
		for (; j <= N; j++)
		{
			if (!inArray(i, j))	//(i,j)�����С�45��135��ЩΣ��λ�ü�����-->safe j
			{
				insertArray(i, j);//���ûʺ�
				i++;	//Ѱ����һ���ʺ��λ��
				j = 1;
				break;
			}
		}

		if (j>N)	//��ǰ�Ļʺ�iû�а�ȫ��λ��
		{
			if (i <= 1) {	/*���˵�1�Żʺ�ʱҲû���ҵ�����λ�ã���ô�����ٻ����ˣ���ʱ���ݷ�ʧ�ܣ�����FAIL(���������LV�㷨����backtraceʱ��������Ϊ��ʱ�����Ҳ���һ���free(array45);)*/
				return FAIL;
			}
			else {
				failNodeNum++;	//���˵Ľڵ�����
				i--;		//��i-1��arrayCol[i]+1λ�ÿ�ʼ������i-1��λ�á�
				j = arrayCol[i] + 1;
				popArray(i);	//����Ӧ����ֵ��ΪEMPTY,ɾ��(i-1)th�ʺ��Σ��λ��
			}
		}
	}

	return SUCCESS;

}

int QueensLV(int stepVages)
{
	int row = 1, col, nb;
	int j;

	while (row <= stepVages) {   //�Ľ���LV�㷨��ֻ�������stepVages���ʺ�
		nb = 0;
		j = 1;
		srand((unsigned)time(0));
		sumNodeNum++;
		for (; j <= N; j++) {		//Ϊrow����һ�������λ��col(������openλ����ѡ��һ��)
			if (!inArray(row, j)) {
				nb++;
				if (((rand() % nb) + 1) == 1) {
					col = j;
				}
			}
		}
		if (nb>0) {	//���ں��ʵ�λ��
			insertArray(row, col);
			tryp[row] = col;
		}
		else {	//nb=0,�����ں��ʵ�λ�ã�����
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
	//�������Ľ�����������ŵ�stepVegas����Ϊ�������ܽ����������ִ��ʱ�䣩
	int best_sv = -1, tmp_sv;
	double tmp_rate, best_rate = -0.01;

	N = 12;
	for (; N <= 20; N++) {	//N-�ʺ������stepVages.

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

		printf("��N=%dʱ��stepVages=%d.\n", N, best_sv);
		free_array();
	}
	system("pause");
	return 0;
}
