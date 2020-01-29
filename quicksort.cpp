#include <iostream>
#include <vector>
using namespace std;

template <typename T>
T median(T a, T b, T c) {
    return max(min(a, b), min(max(a, b), c));
}

template <typename T>
void quicksort(T start, T stop) {
    // Base case: One element
    auto len = stop - 1 - start;
    if (len == 0) return;

    // Pick pivot
    auto pivot = median(start[0], start[len / 2], start[len]);     

    // Less than pivot to left, greater to the right
    auto i = 0;
    auto j = len;
    while (i <= j) {
        if (start[i] < pivot) {
            ++i;
        } else if (start[j] > pivot) {
            --j;
        } else {
            swap(start[i], start[j]);
            ++i;
            --j;
        }
    }

    //TODO Three-way-partition with values == pivot in middle

    //Recurse to left and right
    quicksort(start, start + i);
    quicksort(start + i, stop);
}

int main() {
    vector<int> nums{4, 4, 3, 5, 1, 3, 1, 2, 6, 0, -10, 50};

    quicksort(nums.begin(), nums.end());
    for (auto n : nums)
        cout << n << " ";
    cout << endl;

    return 0;
}