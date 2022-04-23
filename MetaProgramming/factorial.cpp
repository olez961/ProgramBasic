#include <iostream>
using namespace std;

template <unsigned n>
struct Factorial {
    enum { value = n * Factorial<n-1>:: value};
};

template <>
struct Factorial<0> {
    enum { value = 1 };
};

int main() {
    cout << Factorial<30>::value << endl;
    cout << Factorial<9>::value << endl;
    cout << Factorial<7>::value << endl;
    cout << Factorial<4>::value << endl;
    return 0;
}