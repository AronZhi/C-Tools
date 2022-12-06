#ifndef SORT_H
#define SORT_H
#include <Windows.h>
#include <assert.h>
#include <vector>
/*
template <class T>
void _QuickSortRecursive(std::vector<T>& input, int32_t start, int32_t end)
{
	assert(start >= 0);
	if (start >= end)
		return;
	int32_t base_index = (start+end)/2;
	T base = input[base_index];
	int32_t l = start, r = end;
	auto swap = [](T* v1, T* v2)->void {
		T t = *v1;
		*v1 = *v2;
		*v2 = t;
	};
	while (l < r)
	{
		while (l < r && input[r] >= base)
			r--;
		while (l < r && input[l] <= base)
			l++;
		swap(&(input[l]), &(input[r]));
	}
	// 退出循环时，必定l和r位置重叠，此时交换l和base_index的位置，就能保证左边时小于基准数，右边时大于基准数 
	swap(&(input[l]), &(input[base_index]));
	_QuickSortRecursive<T>(input, start, l - 1);
	_QuickSortRecursive<T>(input, l + 1, end);
}


// 改进swap，减少内存开销
template <class T>
void _QuickSortRecursive(std::vector<T>& input, int32_t start, int32_t end)
{
	assert(start >= 0);
	if (start >= end)
		return;
	int32_t base_index = (start+end)/2;
	T base = input[base_index];
	int32_t l = start, r = end;
	auto swap = [](T* left, T* right, T* t)->void {
		*t = *right;
		*right = *left;
		*left = *t;
	};
	while (l < r)
	{
		while (l < r && input[r] >= base)
			r--;
		while (l < r && input[l] <= base)
			l++;
		swap(&(input[l]), &(input[r]), &(input[base_index]));
	}
	// 退出循环时，必定l和r位置重叠，此时将l的位置放上base，就能保证右边的数大于base，左边的数小于base 
	// 放base前，把l位置上的数放在base_index上保证数据完整 
	input[base_index] = input[l];
	input[l] = base;
	_QuickSortRecursive<T>(input, start, l - 1);
	_QuickSortRecursive<T>(input, l + 1, end);
}
*/

template <class T>
void _quick_sort_recursive(std::vector<T>& input, int32_t start, int32_t end)
{
	assert(start >= 0);
	if (start >= end)
		return;
	T base = input[start]; // 必须用start作为坑位，否则循环内第一次交换会丢失input[start]的值 
	int32_t l = start, r = end;
	while (l < r)
	{
		while (input[r] >= base && r > l)
			r--;
		input[l] = input[r]; // l作为坑位开始，存放r位置上的数，然后r上的数据已经保存过，r位置成为坑位 
		while (input[l] <= base && l < r)
			l++;
		input[r] = input[l]; // r成为坑位存放l位置上的数，然后l因为数据已经保存成为坑位
	}
	input[l] = base; // 退出循环，l和r位置重合，这个位置是最后的坑位，放会base数，然后左边是小于base，右边是大于base 
	_quick_sort_recursive<T>(input, start, l - 1);
	_quick_sort_recursive<T>(input, l + 1, end);
}

template <class T>
void quick_sort(std::vector<T>& input)
{
	_quick_sort_recursive<T>(input, 0, input.size() - 1);
}

template<typename T>
void _merge_sort_recursive(std::vector<T>& input, std::vector<T>& temp, int start, int end)
{
	assert(start >= 0);
	if (start >= end)
		return;
	int mid = (start + end) / 2;
	// 将数组分割 
	_merge_sort_recursive<T>(input, temp, start, mid);
	_merge_sort_recursive<T>(input, temp, mid + 1, end);
	int i = start;
	int start1 = start, start2 = mid + 1, end1 = mid, end2 = end;
	// 合并分割后的单元 
	// 从左右两边不断选取小的数依次放入临时数组重 
	while (start1 <= end1 && start2 <= end2)
		temp[i++] = input[start1] < input[start2] ? input[start1++] : input[start2++];
	// 退出条件是start1 > end1 || start2 > end2 
	// 递归之后,左右部分是有序数组,将剩余的数放入数组中  
	while (start1 <= end1)
		temp[i++] = input[start1++];
	while (start2 <= end2)
		temp[i++] = input[start2++];
	for (i = start; i <= end; i++)
		input[i] = temp[i];
}

template <class T>
void merge_sort(std::vector<T>& input)
{
	std::vector<T> tmp;
	tmp.resize(input.size());
	_merge_sort_recursive(input, tmp, 0, input.size() - 1);
}

#endif//SORT_H