#include <iostream>
using namespace std;

class A {
public:
    A() {
        cout << "A" << endl;
    }
    A(int v) {
        cout << "A " << v << endl;
    }
};

class B: public A {
    using A::A;
};

int main() {
    B b{};
    B b2(5);

    return 0;
}