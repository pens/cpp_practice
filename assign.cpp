#include <iostream>
using std::cout, std::move;

struct example {
    example() {
        cout << "Constructor\n";
    }

    ~example() {
        //cout << "Destructor\n";
    }

    // All arguments can be const and/or volatile
    // Canonical: const for copy

    example(const example& ex) {
        cout << "Copy Constructor\n";
    }

    example(example&& ex) {
        cout << "Move Constructor\n";
    }

    example& operator=(const example& rhs) {
        cout << "Copy Assignment\n";
        return *this;
    }

    example& operator=(example&& rhs) {
        cout << "Move Assignment\n";
        return *this;
    }
};

int main() {
    //construct
    example a;
    {
        example m = {};
        //example l() - fn decl
        example l{};
        example();
        example{};
        //copy elision
        example n = example();
        example o = example{};

        new example;
        new example();
        new example{};
    }
    cout << "\n";


    //copy construct
    {
        example c(a);
        example e{a};
        example b = a;
        example f = {a};
        example&& ar = move(a);
        example s = ar;
    }
    cout << "\n";

    //move construct
    {
        example d(move(a));
        example i{move(a)};
        example g = move(a);
        example h = {move(a)};
    }
    cout << "\n";

    //copy assign
    {
        example j;
        j = a;
        example& al = a;
        example p;
        p = al;
        example&& ar = move(a);
        example q;
        q = ar; //not move because not temporary
    }
    cout << "\n";

    //move assign
    {
        example k;
        k = move(a);
        example&& ar = move(a);
        example r;
        r = move(ar);
    }
    cout << "\n";
    
    return 0;
}