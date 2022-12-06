#include "../String/print.hpp"
#include <chrono>

void test_time()
{
    std::chrono::system_clock::duration current = std::chrono::system_clock::now().time_since_epoch();
    std::chrono::seconds time_stamp = std::chrono::duration_cast<std::chrono::seconds>(current);
    wprint(time_stamp.count());
}

int main()
{
    test_time();
    return 0;
}