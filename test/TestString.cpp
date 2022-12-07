#include <vector>
#include <map>
#include "../String/Print.hpp"
#include "../String/Data.hpp"

void testPrint()
{
    wprint(1, 2, 'a', "hello");
    std::vector<int> v{1,2,3};
    wprint(v, "test v");
    std::map<char, int> m;
    m['a'] = 1;
    m['b'] = 2;
    wprint(m);
}

void testReplace()
{
    std::string s("C:\\users\\test\\downloads\\test.txt");
    replace(s, '\\', '/');
    wprint(s);
    replace(s, "test", "what");
    wprint(s);
    replace(s, "what", "AA");
    wprint(s);
}


int main()
{
    testReplace();
    return 0;
}