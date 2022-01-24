#include <iostream>
using namespace std;

class node {
    public:
        int x, y;
        node() : x(0), y(0) {}
        node(int a, int b) : x(a), y(b) {}
        node(const node &a) : x(a.x), y(a.y) {}

        node operator-(const node &a) {
            node t(*this);
            t.x -= a.x ;
            t.y -= a.y ;
            return t;
        }
};

node operator+(const node &a, const node &b) {
    node t;
    t.x = a.x + b.x;
    t.y = a.y + b.y;
    return t;
}

int main() {
    node a(3, 6);
    node b(4, 2);
    node c = a + b;
    node d = a - b;

    cout << c.x << " " << c.y << endl;
    cout << d.x << " " << d.y << endl;

    return 0;
}