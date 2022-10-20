#include <iostream>
#include <vector>

void fn(std::vector<int>&& vals) {
    std::cout << "auto& -> int&\n";
    for (auto& v : vals) {
        static_assert(std::is_same<decltype(v), int&>::value);
        std::cout << v << " ";
    }
    std::cout << "\n";

    std::cout << "auto&& -> int&\n";
    for (auto&& v : vals) {
        // auto&& can become rvalue or lvalue
        static_assert(std::is_same<decltype(v), int&>::value);
        std::cout << v << " ";
    }
    std::cout << "\n";

    std::cout << "int&\n";
    for (int& v : vals) {
        static_assert(std::is_same<decltype(v), int&>::value);
        std::cout << v << " ";
    }
    std::cout << "\n";

    /* Won't compile, as int&& is always rvalue
    for (int&& v : vals) {
        std::cout << v << " ";
    }
    */

    std::cout << std::endl;
}

int main() {
    std::vector<int> vals{1, 2, 3, 4};

    // Move & auto&&

    //fn(vals); Bad, can't create rvalue ref
    fn(std::move(vals)); // Doesn't guarantee moved from
    vals.push_back(5);
    fn(std::move(vals));
    fn({5, 4, 3, 2, 1});

    typedef int& intlref;
    typedef int&& intrref;

    // Reference collapsing: ref to ref lvalue unless rref to rref

    static_assert(std::is_same<int&,  intlref& >::value);
    static_assert(std::is_same<int&,  intlref&&>::value);
    static_assert(std::is_same<int&,  intrref& >::value);
    static_assert(std::is_same<int&&, intrref&&>::value);

    // Forwarding
    // static_cast<T&&>(t_ref) keeps t_ref's type 
    // (std::forward<T>(t_ref) == static_cast<T&&>(t_ref))

    int i = 0;
    intlref il = i;
    intrref ir = std::move(i);

    static_assert(std::is_same<int&,  decltype(static_cast<intlref&&>(i))>::value);
    static_assert(std::is_same<int&&, decltype(static_cast<intrref&&>(i))>::value);
    static_assert(std::is_same<int&,  decltype(static_cast<intlref&&>(il))>::value);
    static_assert(std::is_same<int&&, decltype(static_cast<intrref&&>(il))>::value);
    static_assert(std::is_same<int&,  decltype(static_cast<intlref&&>(ir))>::value);
    static_assert(std::is_same<int&&, decltype(static_cast<intrref&&>(ir))>::value);

    return 0;
}
