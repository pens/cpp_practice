#include <iostream>
using std::cout;

void ext_fn_decl();
extern void ext_fn_decl_2();
static void int_fn_decl();

void ext_fn_def() {
    // This is why function can't be defined in header
    // w/o static, inline, etc.
    cout << "ext_fn_def\n";
}

extern void ext_fn_def_2() {
    cout << "ext_fn_def_2\n";
}

void int_fn_decl() {
    cout << "int_fn_decl\n";
}

static void int_fn_def() {
    cout << "int_fn_def: a\n";
}

int ext_val_def;
extern int ext_val_decl;
extern int ext_val_def_2 = 1; // Will warn
static int int_val_def;

void print(int v) {
    cout << v << "\n";
}

int main() {
    ext_fn_decl();
    ext_fn_def();

    ext_fn_decl_2();
    ext_fn_def_2();

    int_fn_def();
    int_fn_decl();

    print(ext_val_def);
    print(ext_val_def_2);

    print(ext_val_decl);

    print(int_val_def);

    return 0;
}