#include <iostream>
#include <unordered_set>
#include <string>

using namespace std;

struct node {
    int a, b;
    bool operator==(const node &b) const {
        return this->a == b.a && this->b == b.b;
    }
};

struct myhash {
    size_t operator() (const node &t) const{
        return hash<int>{}(t.a);
    }
};

int main() {
    unordered_set<node, myhash> s;
    s.insert((node){5, 6});
    s.insert((node){15, 9});
    s.insert((node){-2, -4});

    // unordered_set<string> s;
    // s.insert("haha");
    // s.insert("123");
    // s.insert("????");
    // s.insert("^-^");

    // cout << s.size() << endl;

    // if (s.count("????")) {
    //     cout << "???? yes" << endl;
    // } else {
    //     cout << "???? no" << endl;
    // }

    // s.erase("????");
    // cout << s.size() << endl;

    // for (auto x : s) {
    //     cout << x << " ";
    // }
    // cout << endl;

    return 0;
}
