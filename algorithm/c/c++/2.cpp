#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

class node {
public:
    int n;
    char *s;
    node() {
        cout << 'c' << endl;
        this->n = 5;
        this->s = (char *)calloc(5, 1);
        s[0] = 'N';
    }
    node(int n, const char *s) {
        cout << "cwp" << endl;
        this->n = n;
        this->s = (char *)calloc(strlen(s) + 1, 1);
        memcpy(this->s, s, strlen(s));
    }
    node(const node &a) {
        cout << "cc" << endl;
        this->n = a.n;
        // 深拷贝
        this->s = (char *)calloc(strlen(a.s) + 1, sizeof(char));
        memcpy(this->s, a.s, strlen(a.s));

        // 浅拷贝
        this->s = a.s;
    }
    ~node() {
        cout << "d" << endl;
        free(this->s);
    }
};

node add(node &a, node &b) {
    node t(a);
    t.n += b.n;
    return t;
}

int main() {
    node *a = new node(5, "haha");
    cout << a->n << " " << a->s << endl;
    delete a;

    // node a;
    // node b(a);
    // node c = add(a, b);

    // node t;
    // t.n = 10;
    // t.s = (char *)calloc(8, 1);
    // t.s[0] = 'A', t.s[1] = 'B', t.s[2] = 'a';
    // cout << t.s << endl;

    // node tt(t);
    // tt.n = 20;
    // cout << tt.n << " " << tt.s << endl;
    // tt.s[0] = 'B';
    // cout << tt.s << endl;
    // cout << t.s << endl;

    return 0;
}