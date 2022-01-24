#include <iostream>

using namespace std;

struct my_less {
    bool operator() (const int &a, const int &b) {
        return a < b;
    }
};

struct my_add {
    int operator()(const int &a, const int &b) {
        return a + b;
    }
};

int main() {
    int a, b;
    cin >> a >> b;
    if (my_less{}(a, b)){
        cout << "a lass than b" << endl;
    } else {
        cout << "b less than a" << endl;
    }

    cout << my_add{}(a, b) << endl;

    return 0;
}