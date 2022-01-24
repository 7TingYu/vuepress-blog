#include <iostream>
#include <set>

using namespace std;

struct node {
    int a, b;
    bool operator<(const node &b) const{
        return this->a < b.a;
    }
};

int main() {
    set<node> s;
    s.insert((node){0, 4});
    s.insert((node){5, 6});
    s.insert((node){7, 3});
    s.insert((node){9, 8});
    s.insert((node){6, 5});
    node t = (node){9, 8};
    if (s.count(t) == 1) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }
    for (auto x : s) {
        cout << x.a << " " << x.b << endl;
    }

    // set<int> s;s
    // s.insert(6);
    // s.insert(5);
    // s.insert(2);
    // s.insert(97);
    // s.insert(36);

    // cout << s.size() << endl;
    // s.insert(6);
    // cout << s.size() << endl;

    // if (s.count(5) == 1) {
    //     cout << "5 yes" << endl;
    // } else {
    //     cout << "5 no" << endl;
    // }

    // s.erase(5);
    // s.erase(5);
    // cout << s.size() << endl;

    // if (s.count(5) == 1) {
    //     cout << "5 yes" << endl;
    // } else {
    //     cout << "5 no" << endl;
    // }

    // for (auto x : s) {
    //     cout << x << " ";
    // }
    // cout << endl;

    // for (auto it = s.begin(); it != s.end(); it++) {
    //     cout << *it << " ";
    // }
    // cout << endl;

    return 0;
}



