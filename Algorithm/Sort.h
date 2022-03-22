#ifndef SORT_H
#define SORT_H
#include <Windows.h>
#include <assert.h>
#include <vector>
#include <iostream>
#include <sstream>

/*
template <class T>
void QuickSort(std::vector<T>& input, int32_t start, int32_t end)
{
	assert(start >= 0);
	if (start >= end)
		return;
	for (auto num : input)
		std::cout << num << ",";
	std::cout << " -> ";
	// T base = input[(start + end) / 2]; 
	int32_t base_index = start;
	T base = input[base_index]; // 以input[start]作为一基准值，选择其他会引起问题
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
		swap(&(input[l]), &(input[r]));
		while (l < r && input[l] <= base)
			l++;
		swap(&(input[l]), &(input[r]));
	}
	for (auto num : input)
		std::cout << num << ",";
	std::cout << std::endl;
	QuickSort<T>(input, start, l - 1);
	QuickSort<T>(input, l + 1, end);
}
*/

/*
// 改进swap，减少内存开销
template <class T>
void QuickSort(std::vector<T>& input, int32_t start, int32_t end)
{
	assert(start >= 0);
	if (start >= end)
		return;
	for (auto num : input)
		std::cout << num << ",";
	std::cout << " -> ";
	// T base = input[(start + end) / 2];
	int32_t base_index = start; // 以start作为一个存放临时变量的坑，用其他位置会引起问题 
	T base = input[base_index];
	int32_t l = start, r = end;
	auto swap = [](T* v1, T* v2, T* t)->void {
		*t = *v1;
		*v1 = *v2;
		*v2 = *t;
	};
	while (l < r)
	{
		while (l < r && input[r] >= base)
			r--;
		swap(&(input[l]), &(input[r]), &(input[base_index]));
		while (l < r && input[l] <= base)
			l++;
		swap(&(input[l]), &(input[r]), &(input[base_index]));
	}
	input[l] = base;
	for (auto num : input)
		std::cout << num << ",";
	std::cout << std::endl;
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
	for (auto num : input)
		std::cout << num << ",";
	std::cout << " -> ";
	T base = input[start]; // 用其他位置会引起问题
	int32_t l = start, r = end;
	int t;
	while (l < r)
	{
		while (input[r] >= base && r > l)
			r--;
		input[l] = input[r];
		while (input[l] <= base && l < r)
			l++;
		input[r] = input[l];
	}
	input[l] = base;
	for (auto num : input)
		std::cout << num << ",";
	std::cout << std::endl;
	QuickSort<T>(input, start, l - 1);
	QuickSort<T>(input, l + 1, end);
}

#endif SORT_H