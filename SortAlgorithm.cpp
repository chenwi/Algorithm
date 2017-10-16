#include<iostream>
using namespace std;

//快速排序
// 分类 ------------ 内部比较排序
// 数据结构 --------- 数组
// 最差时间复杂度 ---- 每次选取的基准都是最大（或最小）的元素，导致每次只划分出了一个分区，需要进行n-1次划分才能结束递归，时间复杂度为O(n^2)
// 最优时间复杂度 ---- 每次选取的基准都是中位数，这样每次都均匀的划分出两个分区，只需要logn次划分就能结束递归，时间复杂度为O(nlogn)
// 平均时间复杂度 ---- O(nlogn)
// 所需辅助空间 ------ 主要是递归造成的栈空间的使用(用来保存left和right等局部变量)，取决于递归树的深度，一般为O(logn)，最差为O(n)       
// 稳定性 ---------- 不稳定
void QuickSort(int arr[], int l, int r)
{
	if (l < r)
	{
		int temp = arr[l];
		int i, j, k;
		i = l, j = r;

		while (i < j)
		{
			while (i < j&&temp <= arr[j])//先找到右边第一个比temp小的元素，然后将它向左移动
				j--;
			arr[i++] = arr[j];
			while (i < j&&temp >= arr[i])//找到左边第一个比temp大的元素，然后将它向右移
				i++;
			arr[j--] = arr[i];
		}
		arr[i] = temp;//中间（指左边的数小于temp，右边的数大于temp）这个空用temp补上
		//递归调用
		QuickSort(arr, l, i-1);
		QuickSort(arr, j+1, r);
	}
}

//插入排序
// 分类 ------------- 内部比较排序
// 数据结构 ---------- 数组
// 最差时间复杂度 ---- 最坏情况为输入序列是降序排列的,此时时间复杂度O(n^2)
// 最优时间复杂度 ---- 最好情况为输入序列是升序排列的,此时时间复杂度O(n)
// 平均时间复杂度 ---- O(n^2)
// 所需辅助空间 ------ O(1)
// 稳定性 ------------ 稳定
void InsertSort(int arr[], int n)
{
	int i, j;
	
	for (i = 1; i < n; i++)
	{
		int temp = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j] > temp)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j+1] = temp;
	}
}

//冒泡排序
// 分类 -------------- 内部比较排序
// 数据结构 ---------- 数组
// 最差时间复杂度 ---- O(n^2)
// 最优时间复杂度 ---- 如果能在内部循环第一次运行时,使用一个旗标来表示有无需要交换的可能,可以把最优时间复杂度降低到O(n)
// 平均时间复杂度 ---- O(n^2)
// 所需辅助空间 ------ O(1)
// 稳定性 ------------ 稳定
void BubbleSort(int arr[], int n)
{
	int i, j, temp;
	for(i=0;i<n-1;i++)
		for(j=0;j<n-1-i;j++)//每次最大元素往后移动，则比较次数n-1-i
			if (arr[j] > arr[j+1])
			{
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}

}

//选择排序
// 分类 -------------- 内部比较排序
// 数据结构 ---------- 数组
// 最差时间复杂度 ---- O(n^2)
// 最优时间复杂度 ---- O(n^2)
// 平均时间复杂度 ---- O(n^2)
// 所需辅助空间 ------ O(1)
// 稳定性 ------------ 不稳定
void SelectSort(int arr[], int n)
{
	int i, j,temp;
	for (i = 0; i < n - 1; i++)         // i为已排序序列的末尾
	{
		int min = i;
		for (j = i + 1; j < n; j++)     // 未排序序列,相当于每次从未排序的部分选出最小的添加到排过序的末尾
		{
			if (arr[j] < arr[min])              // 找出未排序序列中的最小值
			{
				min = j;
			}
		}
		if (min != i)
		{
			temp = arr[i];
			arr[i] = arr[min];
			arr[min] = temp;
		}
	}
}

//希尔排序
// 分类 -------------- 内部比较排序
// 数据结构 ---------- 数组
// 最差时间复杂度 ---- 根据步长序列的不同而不同。已知最好的为O(n(logn)^2)
// 最优时间复杂度 ---- O(n)
// 平均时间复杂度 ---- 根据步长序列的不同而不同。
// 所需辅助空间 ------ O(1)
// 稳定性 ------------ 不稳定

void ShellSort(int arr[], int n)
{
	int h = 0;
	while (h <= n)                          // 生成初始增量
	{
		h = 3 * h + 1;
	}
	while (h >= 1)
	{
		for (int i = h; i < n; i++)
		{
			int j = i - h;
			int get = arr[i];
			while (j >= 0 && arr[j] > get)
			{
				arr[j + h] = arr[j];
				j = j - h;
			}
			arr[j + h] = get;
		}
		h = (h - 1) / 3;                    // 递减增量
	}
}


// 分类 -------------- 内部比较排序
// 数据结构 ---------- 数组
// 最差时间复杂度 ---- O(nlogn)
// 最优时间复杂度 ---- O(nlogn)
// 平均时间复杂度 ---- O(nlogn)
// 所需辅助空间 ------ O(n)
// 稳定性 ------------ 稳定
void Merge(int arr[], int left, int mid, int right)// 合并两个已排好序的数组arr[left...mid]和arr[mid+1...right]
{
	int len = right - left + 1;
	int *temp = new int[len];       // 辅助空间O(n)
	int index = 0;
	int i = left;                   // 前一数组的起始元素
	int j = mid + 1;                // 后一数组的起始元素
	while (i <= mid && j <= right)
	{
		temp[index++] = arr[i] <= arr[j] ? arr[i++] : arr[j++];  // 带等号保证归并排序的稳定性
	}
	while (i <= mid)
	{
		temp[index++] = arr[i++];
	}
	while (j <= right)
	{
		temp[index++] = arr[j++];
	}
	for (int k = 0; k < len; k++)
	{
		arr[left++] = temp[k];
	}
}

void MergeSortRecursion(int arr[], int left, int right)    // 递归实现的归并排序(自顶向下)
{
	if (left == right)    // 当待排序的序列长度为1时，递归开始回溯，进行merge操作
		return;
	int mid = (left + right) / 2;
	MergeSortRecursion(arr, left, mid);
	MergeSortRecursion(arr, mid + 1, right);
	Merge(arr, left, mid, right);
}

void MergeSortIteration(int arr[], int len)    // 非递归(迭代)实现的归并排序(自底向上)
{
	int left, mid, right;// 子数组索引,前一个为arr[left...mid]，后一个子数组为arr[mid+1...right]
	for (int i = 1; i < len; i *= 2)        // 子数组的大小i初始为1，每轮翻倍
	{
		left = 0;
		while (left + i < len)              // 后一个子数组存在(需要归并)
		{
			mid = left + i - 1;
			right = mid + i < len ? mid + i : len - 1;// 后一个子数组大小可能不够
			Merge(arr, left, mid, right);
			left = right + 1;               // 前一个子数组索引向后移动
		}
	}
}

//堆排序
// 分类 -------------- 内部比较排序
// 数据结构 ---------- 数组
// 最差时间复杂度 ---- O(nlogn)
// 最优时间复杂度 ---- O(nlogn)
// 平均时间复杂度 ---- O(nlogn)
// 所需辅助空间 ------ O(1)
// 稳定性 ------------ 不稳定


void Swap(int arr[], int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void Heapify(int arr[], int i, int size)  // 从arr[i]向下进行堆调整
{
	int left_child = 2 * i + 1;         // 左孩子索引
	int right_child = 2 * i + 2;        // 右孩子索引
	int max = i;                        // 选出当前结点与其左右孩子三者之中的最大值
	if (left_child < size && arr[left_child] > arr[max])
		max = left_child;
	if (right_child < size && arr[right_child] > arr[max])
		max = right_child;
	if (max != i)
	{
		Swap(arr, i, max);                // 把当前结点和它的最大(直接)子节点进行交换
		Heapify(arr, max, size);          // 递归调用，继续从当前结点向下进行堆调整
	}
}

int BuildHeap(int arr[], int n)           // 建堆，时间复杂度O(n)
{
	int heap_size = n;
	for (int i = heap_size / 2 - 1; i >= 0; i--) // 从每一个非叶结点开始向下进行堆调整
		Heapify(arr, i, heap_size);
	return heap_size;
}

void HeapSort(int arr[], int n)
{
	int heap_size = BuildHeap(arr, n);    // 建立一个最大堆
	while (heap_size > 1)   
	{	// 堆（无序区）元素个数大于1，未完成排序
		// 将堆顶元素与堆的最后一个元素互换，并从堆中去掉最后一个元素
		// 此处交换操作很有可能把后面元素的稳定性打乱，所以堆排序是不稳定的排序算法
		Swap(arr, 0, --heap_size);
		Heapify(arr, 0, heap_size);     // 从新的堆顶元素开始向下进行堆调整，时间复杂度O(logn)
	}
}



void main()
{
	int a[5] = { 16,13,55,1,67 }; 
	//QuickSort(a, 0, size(a) - 1);//减一的原因是要定位到最后一个元素
	//InsertSort(a, size(a));
	//BubbleSort(a, size(a));
	//SelectSort(a, size(a));
	//ShellSort(a, size(a));
	//MergeSortIteration(a, size(a));
	//HeapSort(a, size(a));
	for (int i = 0; i < size(a); i++)
		cout << a[i]<<"  ";
	system("pause");
}


