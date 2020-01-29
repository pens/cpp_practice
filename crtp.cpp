#include <iostream>
using std::cout;

template<typename T>
class Base {
public:
    void Run() {
        static_cast<T*>(this)->RunImpl();
        cout << "Base\n";
    }
};

class Sub1 : public Base<Sub1> {
public:
    void RunImpl() {
        cout << "Sub1\n";
    }
};

class Sub2 : public Base<Sub2> {
public:
    void RunImpl() {
        cout << "Sub2\n";
    }
};

int main() {
    //Can't store Sub in Base* - Base<T> is different type
    Sub1 s1;
    Sub2 s2;

    s1.Run();
    s2.Run();

    return 0;
}