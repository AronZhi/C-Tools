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
	// �˳�ѭ��ʱ���ض�l��rλ���ص�����ʱ����l��base_index��λ�ã����ܱ�֤���ʱС�ڻ�׼�����ұ�ʱ���ڻ�׼�� 
	swap(&(input[l]), &(input[base_index]));
	_QuickSortRecursive<T>(input, start, l - 1);
	_QuickSortRecursive<T>(input, l + 1, end);
}


// �Ľ�swap�������ڴ濪��
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
	// �˳�ѭ��ʱ���ض�l��rλ���ص�����ʱ��l��λ�÷���base�����ܱ�֤�ұߵ�������base����ߵ���С��base 
	// ��baseǰ����lλ���ϵ�������base_index�ϱ�֤�������� 
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
	T base = input[start]; // ������start��Ϊ��λ������ѭ���ڵ�һ�ν����ᶪʧinput[start]��ֵ 
	int32_t l = start, r = end;
	while (l < r)
	{
		while (input[r] >= base && r > l)
			r--;
		input[l] = input[r]; // l��Ϊ��λ��ʼ�����rλ���ϵ�����Ȼ��r�ϵ������Ѿ��������rλ�ó�Ϊ��λ 
		while (input[l] <= base && l < r)
			l++;
		input[r] = input[l]; // r��Ϊ��λ���lλ���ϵ�����Ȼ��l��Ϊ�����Ѿ������Ϊ��λ
	}
	input[l] = base; // �˳�ѭ����l��rλ���غϣ����λ�������Ŀ�λ���Ż�base����Ȼ�������С��base���ұ��Ǵ���base 
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
	// ������ָ� 
	_merge_sort_recursive<T>(input, temp, start, mid);
	_merge_sort_recursive<T>(input, temp, mid + 1, end);
	int i = start;
	int start1 = start, start2 = mid + 1, end1 = mid, end2 = end;
	// �ϲ��ָ��ĵ�Ԫ 
	// ���������߲���ѡȡС�������η�����ʱ������ 
	while (start1 <= end1 && start2 <= end2)
		temp[i++] = input[start1] < input[start2] ? input[start1++] : input[start2++];
	// �˳�������start1 > end1 || start2 > end2 
	// �ݹ�֮��,���Ҳ�������������,��ʣ���������������  
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