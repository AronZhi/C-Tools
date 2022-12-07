#include "../String/print.hpp"
#include <chrono>

void testTime()
{
    std::chrono::system_clock::duration current = std::chrono::system_clock::now().time_since_epoch();
    std::chrono::seconds time_stamp = std::chrono::duration_cast<std::chrono::seconds>(current);
    wprint(time_stamp.count());
}

int main()
{
    testTime();
    return 0;
}