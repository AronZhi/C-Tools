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

void testMessUpOrder()
{
    std::vector<int> a {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
    messUpOrder<int>(a);
    wprint(a);
}


int main()
{
    testMessUpOrder();
    return 0;
}