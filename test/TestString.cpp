#include <vector>
#include <map>
#include "../String/Print.hpp"

int main()
{
    wprint(1, 2, 'a', "hello");
    std::vector<int> v{1,2,3};
    wprint(v, "test v");
    std::map<char, int> m;
    m['a'] = 1;
    m['b'] = 2;
    wprint(m);
    return 0;
}