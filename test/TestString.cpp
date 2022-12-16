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

void testStartWith()
{
    std::string s1("abc123");
    std::string s2("abc");
    std::string s3("adc");
    wprint(startWith(s1, s2));
    wprint(startWith(s1, s3));

    std::string s4("123");
    wprint(endWith(s1, s4));
    wprint(endWith(s1, s3));
}


int main()
{
    testStartWith();
    return 0;
}