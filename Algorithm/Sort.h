#ifndef SORT_H
#define SORT_H
#include <Windows.h>
#include <assert.h>
#include <vector>
/*
template <class T>
void QuickSort(std::vector<T>& input, int32_t start, int32_t end)
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
	QuickSort<T>(input, start, l - 1);
	QuickSort<T>(input, l + 1, end);
}


// 改进swap，减少内存开销
template <class T>
void QuickSort(std::vector<T>& input, int32_t start, int32_t end)
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
	QuickSort<T>(input, start, l - 1);
	QuickSort<T>(input, l + 1, end);
}
*/

template <class T>
void QuickSort(std::vector<T>& input, int32_t start, int32_t end)
{
	assert(start >= 0);
	if (start >= end)
		return;
	T base = input[start]; // 必须用start作为坑位，否则循环内第一次交换会丢失input[start]的值 
	int32_t l = start, r = end;
	int t;
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
	QuickSort<T>(input, start, l - 1);
	QuickSort<T>(input, l + 1, end);
}

#endif//SORT_H