#include "../String/Print.hpp"
#include "../DesignPatterns/SingleInst.hpp"

class A
{
public:
    A() { wprint("construct A"); }
    ~A() { wprint("destruct A"); }
};

int main()
{
    A& p = Singleton<A>::getInstance();
    return 0;
}