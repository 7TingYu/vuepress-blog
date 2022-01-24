#include <iostream>
using namespace std;

class node {
    public: 
        int x, y;
        node() : x(-5), y(0){
            cout << "dc" << endl;
        }
        node(int a, int b) : x(a), y(b) {
            cout << "c" << endl;
        }

        node(const node &a) : x(a.x), y(a.y) {
            cout << "cc" << endl;
            this->x++;
            this->y++;
        }
};

int main() {
    node t(100, 700);
    cout << t.x << " " << t.y << endl;

    node tt(t);
    cout << tt.x << " " << tt.y << endl;

    return 0;
}
