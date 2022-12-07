#include "../String/print.hpp"
#include "../System/Time.hpp"
#include "../System/Path.hpp"

void testGetTimeStamp()
{
    time_t time_stamp = GetCurrentTimeStamp();
    wprint(time_stamp);
}

void testComparePath()
{
    std::string p1("C:\\Users\\Public\\Documents");
    std::string p2("C:\\Users\\Public\\Documents\\test");
    std::string p3("C:\\Users\\Public");
    std::string p4("C:\\Users\\Public");
    std::string p5("C:\\Users\\Test");
    std::string p6("C:\\Proce\\Test");
    int ret = comparePath(p1, p2);
    wprint(ret);
    ret = comparePath(p1, p3);
    wprint(ret);
    ret = comparePath(p4, p3);
    wprint(ret);
    ret = comparePath(p4, p5);
    wprint(ret);
    ret = comparePath(p6, p5);
    wprint(ret);
}

int main()
{
    testComparePath();
    return 0;
}