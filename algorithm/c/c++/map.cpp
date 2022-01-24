#include <iostream>
#include <map>

using namespace std;

struct node {
    int a, b;
    bool operator< (const node &b) {
        return this->a < b.a;
    }
};

int main() {
    map<int, node> m;
    m[5] = (node){10, 4};
    m[99] = (node){12, 72};
    m[68] = (node){-5, -10};

    for (auto &x : m) {
        cout << x.first << " " << x.second.a << " " << x.second.b << endl;
    }

    // map<int, char> m;
    // m.insert({55, '?'});
    // m[12] = '+';
    // m[77] = 'A';
    // m[49] = 'a';
    // m[2] = '&';

    // if (m.count(49)) {
    //     cout << "49 yes value = " << m[49] << endl;
    // }
    // cout << m.size() << endl;

    // m[49] = '>';
    // cout << "key = 49 value = " << m[49] << endl;

    // m.erase(12);
    // if (!m.count(12)) {
    //     cout << "12 no " << endl;
    // }

    // for (auto &x : m) {
    //     cout << x.first << " " << x.second << endl;
    // }

    return 0;
}