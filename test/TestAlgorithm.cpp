#include "../Algorithm/Sort.hpp"
#include "../String/Print.hpp"
#include <vector>

void testQuickSort()
{
    std::vector<int> vec;
    vec.push_back(11);
    vec.push_back(12);
    vec.push_back(3);
    vec.push_back(22);
    vec.push_back(10);
    quickSort<int>(vec);
    wprint(vec);
}

void testMergeSort()
{
    std::vector<int> vec;
    vec.push_back(11);
    vec.push_back(12);
    vec.push_back(3);
    vec.push_back(22);
    vec.push_back(10);
    mergeSort<int>(vec);
    wprint(vec);
}

int main()
{
    testMergeSort();
    return 0;
}