#include <iostream>
using namespace std;

struct node {
    int val;
    node* left;
    node* right;
};

class bst {
    node* root;

public:
    void insert(int val) {
        node** cur = &root;
        while (*cur != nullptr) {
            if ((*cur)->val == val) {
                return;
            } else if ((*cur)->val < val) {
                cur = &(*cur)->right;
            } else if ((*cur)->val > val) {
                cur = &(*cur)->left;
            }
        }
        *cur = new node{val, nullptr, nullptr};
    }

    node* find(int val) {
        node* cur = root;
        while (cur != nullptr) {
            if (cur->val == val) {
                return cur;
            } else if (cur->val < val) {
                cur = cur->right;
            } else if (cur->val > val) {
                cur = cur->left;
            }
        }
        return nullptr;
    }
};

int main() {
    bst b{};
    b.insert(4);

    cout << b.find(4)->val << "\n";

    b.insert(2);
    b.insert(5);

    cout << b.find(4)->val << " " << b.find(2)->val << " " << b.find(5)->val << " " << "\n";

    b.insert(1);
    b.insert(3);
    b.insert(6);

    cout << b.find(4)->val << " " << b.find(2)->val << " " << b.find(5)->val << " " << b.find(1)->val << " " << b.find(3)->val << " " << b.find(6)->val << " " << "\n";
    
    return 0;
}