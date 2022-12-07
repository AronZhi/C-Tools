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

#ifdef _WIN32

void testDosPathNtPath()
{
    WCHAR nt[250] = L"\\Device\\HarddiskVolume2\\Users\\Public";
    WCHAR dos[250] = { 0 };
    ntPath2DosPath(nt, dos);
    wprint(dos);

    WCHAR nt2[250] = { 0 };
    dosPath2NtPath(dos, nt2);
    wprint(nt2);
}

#endif

int main()
{
    #ifdef _WIN32
    testDosPathNtPath();
    #endif
    return 0;
}