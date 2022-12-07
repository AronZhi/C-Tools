#include "../String/print.hpp"
#include "../Time/Time.hpp"

void testGetTimeStamp()
{
    time_t time_stamp = GetCurrentTimeStamp();
    wprint(time_stamp);
}

int main()
{
    testGetTimeStamp();
    return 0;
}